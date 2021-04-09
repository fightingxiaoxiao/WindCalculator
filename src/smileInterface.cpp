/*
 *   Copyright (c) 2020 Chen Xiaoxiao
 *   All rights reserved.

 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at

 *   http://www.apache.org/licenses/LICENSE-2.0

 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */
#include "mesh.h"


int main()
{
    std::cout << "----------------------------\n\n"
              << "smileInterfaceForWindTunnel\n\n"
              << "----------------------------\n"
              << std::endl;

    std::ifstream jsonFile("config.json");
    json jsonArgs;
    jsonFile >> jsonArgs;

    auto model = SmileGL::Surface(); //读取obj建立表面模型
    if (model.readOBJ(jsonArgs["partitionFilename"]))
    {
        std::cerr << "error\n" << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "done\n" << std::endl;
    }
    auto moveVector =  jsonArgs["partitionObjectTransformVector"];
    model.transform(moveVector[0], moveVector[1], moveVector[2]);

    model.calcFaceCenter();
    model.calcAABB(true);
    Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols,
                                 ", ", ", ", "", "", " (", ")");
    Eigen::IOFormat CSVWriteFmt(Eigen::StreamPrecision, Eigen::DontAlignCols,
                                ", ", ", ", "", "");
    std::cout << "Box A Point: " << model.AA.format(CommaInitFmt) << std::endl;
    std::cout << "Box B Point: " << model.BB.format(CommaInitFmt) << std::endl;

    std::cout << "\n";
    Vector rPoint = model.AA - Vector(1., 1., 1.);
    Vector blockLength = model.BB - model.AA + 2 * Vector(1., 1., 1.);
    Scalar blockSize = 1;
    label sizeI = (label)(blockLength(0) / blockSize) + 1;
    label sizeJ = (label)(blockLength(1) / blockSize) + 1;
    label sizeK = (label)(blockLength(2) / blockSize) + 1;

    std::cout << "Block start point: " << rPoint.format(CommaInitFmt) << "\n"
              << "Block element size: " << blockSize << std::endl;
    SmileGL::Block* bkgMesh = new SmileGL::Block(rPoint, sizeI, sizeJ, sizeK, blockSize);

    std::cout << "Final block size:  "
              << "I = " << bkgMesh->I << ", J = " << bkgMesh->J
              << ", K = " << bkgMesh->K << std::endl;
    bkgMesh->linkRelatedFaces(&model);

    auto index = jsonArgs["dataIndex"];
    SmileGL::PointCloud cloud; // 建立数据点云模型
    int coordLocation[3] = {index[0], index[1], index[2]};
    Map<String, label> valueLocation;
    valueLocation.insert(std::pair<String, label>("normalX(Area)", index[3]));
    valueLocation.insert(std::pair<String, label>("normalY(Area)", index[4]));
    valueLocation.insert(std::pair<String, label>("normalZ(Area)", index[5]));
    valueLocation.insert(std::pair<String, label>("p", index[6]));
    std::cout << "\n";
    cloud.readData(jsonArgs["dataFilename"], coordLocation, valueLocation,
                   true); // 读取外部点云数据
    std::cout << "Point cloud get " << cloud.storage.size()
              << " points from this .csv file." << std::endl;

    cloud.convertScalarToVector("normalX(Area)", "normalY(Area)",
                                "normalZ(Area)", "normal(Area)");
    std::cout << "Rotate Angle: " << (Scalar)jsonArgs["pointCloudRotateAngle"]
              << std::endl;
    cloud.rotate(M_PI * (Scalar)jsonArgs["pointCloudRotateAngle"] / 180.,
                 Vector(0., 0., 1.));
    cloud.calcAABB();

    std::cout << "Cloud A Point: " << cloud.AA.format(CommaInitFmt)
              << std::endl;
    std::cout << "Cloud B Point: " << cloud.BB.format(CommaInitFmt)
              << std::endl;

    std::cout << "map surface from cloud." << std::endl;
    bkgMesh->mapSurfaceFromPointCloud(&cloud, &model, jsonArgs["tolerance"]);
    delete bkgMesh;
    
    cloud.convertDataToSurface(&model);

    model.splitSubZone();

    std::cout << "\n**********CALCULATION RESULT**********\n" << std::endl;

    std::ofstream pressCoeffFile((String)jsonArgs["pressureCoeffFilename"]);


    Scalar rhoAir = jsonArgs["rhoAir"];
    // Force
    Vector F = cloud.integralVector("p", "normal(Area)");
    std::cout << "F = " << (F / 1e3).format(CommaInitFmt) << std::endl; // OpenFAOM处理时要*rhoAir
    // Force write
    pressCoeffFile << "Fx, Fy, Fz (kN)" << std::endl;
    pressCoeffFile << (F / 1e3).format(CSVWriteFmt) << "\n"
                   << std::endl;

    // Moment
    Vector ref = (cloud.AA + cloud.BB) / 2.;
    ref(2) = 0.;
    Vector M = cloud.integralVectorWithCoord("p", "normal(Area)", ref);
    std::cout << "M = " << (M / 1e3).format(CommaInitFmt) << std::endl;
    // Moment write
    pressCoeffFile << "Mx, My, Mz (kN*m)" << std::endl;
    pressCoeffFile << (M / 1e3).format(CSVWriteFmt) << "\n"
                   << std::endl;

    Scalar windVelocity = jsonArgs["windVelocity"];
    // pressCoeff write
    pressCoeffFile << "Region, pCoeff" << std::endl;
    for (auto zone : model.subZone)
    {
        zone.second.calculateValueFromFace("p", "normal(Area)");
        pressCoeffFile << zone.first << ", "
                       << zone.second.averageValue["p"] / 0.5 /rhoAir / windVelocity / windVelocity
                       << std::endl;
    }
    std::cout << "The pressure coefficient has been writen to "
              << jsonArgs["pressureCoeffFilename"] << std::endl;

    return 0;
}
