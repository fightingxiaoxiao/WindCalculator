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
#include "csvparser.h"
#include "string_split.h"
#include <boost/geometry.hpp>

namespace SmileGL
{

inline void Face::convertScalarToVector(String scalar_0, String scalar_1,
                                        String scalar_2, String vector)
{
    vectors[vector] =
        Vector(scalars[scalar_0], scalars[scalar_1], scalars[scalar_2]);
}
// Zone::Zone(int n) {}
void Mesh::createZone(int num)
{
    if (zones.find(num) == zones.end())
    {
        zones[num] = Zone();
        zones[num].id = num;
    }
}

void Mesh::transform(Scalar x, Scalar y, Scalar z)
{
    Vector move(x, y, z);
    for (auto &n : nodes)
        n.coord += move;
}

bool Surface::readOBJ(String filename)
{
    std::cerr << "Read .obj file from " << filename << "...";

    String filePath = filename;
    std::ifstream file;
    file.open(filePath, std::ios::in);
    if (!file)
    {
        std::cerr << "File no Found." << std::endl;
        return EXIT_FAILURE;
    }
    String strLine;
    String zone_name = (String) "";
    // 逐行读取
    label lineCount = 0;
    label faceCount = 0;
    while (getline(file, strLine))
    {
        lineCount++;
        std::istringstream out(strLine);
        String split_str;
        Node node_temp;
        Face face_temp;

        if (strLine.size() < 1)
            continue;

        auto line_list = splitStr(strLine, (String) " ");

        if (line_list[0] == (String) "g")
        {
            if (line_list.size() > 1)
            {
                zone_name = line_list[1];
                // zone_name.resize(zone_name.size() - 1);
                // std::cout << zone_name << std::endl;
            }
            else
            {
                std::cerr << "Cannot get object name in .obj file."
                          << std::endl;
                return EXIT_FAILURE;
            }
        }

        if (line_list[0] == (String) "v")
            if (line_list.size() > 3)
            {
                Scalar x, y, z;
                std::stringstream x_str(line_list[1]), y_str(line_list[2]),
                    z_str(line_list[3]);
                x_str >> x;
                y_str >> y;
                z_str >> z;

                node_temp.coord << x, y, z;
                node_temp.id = nodes.size();
                nodes.push_back(node_temp);
                node_temp = Node();
            }
            else
            {
                std::cerr << "illegal vertice info in .obj file." << std::endl;
                return EXIT_FAILURE;
            }

        if (line_list[0] == (String) "f")
        {
            size_t index;
            for (size_t i = 1; i < line_list.size(); i++)
            {
                if ((int)line_list[i][0] < 48 || (int)line_list[i][0] > 57)
                    continue;
                auto temp = splitStr(line_list[i], (String) "/");
                std::stringstream sin(temp[0]);
                sin >> index;
                if (index > nodes.size() + 1)
                {
                    std::cerr << "exceed node number: " << index << " at line "
                              << lineCount << std::endl;
                    return EXIT_FAILURE;
                }
                face_temp.nodes.push_back(index - 1);
                if (index == 0)
                    std::cout << "Zero index: " << lineCount << std::endl;
            }

            face_temp.zone_name = zone_name;
            face_temp.id = faceCount;
            faces.push_back(face_temp);
            faceCount++;
            face_temp = Face();
        }
    }
    return EXIT_SUCCESS;
}

void Surface::transform(Scalar x, Scalar y, Scalar z)
{
    Vector move(x, y, z);
    for (auto &n : nodes)
        n.coord += move;
}

void Surface::calcFaceCenter()
{
    for (auto &f : faces)
    {
        f.centroid = Vector(0., 0., 0.);
        for (auto n_i : f.nodes)
        {
            f.centroid += nodes[n_i].coord;
        }
        f.centroid /= (Scalar)f.nodes.size();
    }
}

void Surface::calcAABB(bool ifSetFace)
{
    if (ifSetFace)
        for (auto &f : faces)
        {
            label length = f.nodes.size();
            Eigen::Matrix<Scalar, -1, -1, Eigen::RowMajor> poly(length, 3);

            for (size_t i = 0; i < length; i++)
                poly.row(i) << nodes[f.nodes[i]].coord;

            f.AA << poly.col(0).minCoeff(), poly.col(1).minCoeff(),
                poly.col(2).minCoeff();

            f.BB << poly.col(0).maxCoeff(), poly.col(1).maxCoeff(),
                poly.col(2).maxCoeff();
            // f.centroid /= f.nodes.size();
        }

    // 此处的内存性能可能需要优化
    Eigen::Matrix<Scalar, -1, -1, Eigen::RowMajor> nodeCollect(nodes.size(), 3);
    for (size_t i = 0; i < nodes.size(); i++)
    {
        nodeCollect.row(i) << nodes[i].coord;
    }

    AA << nodeCollect.col(0).minCoeff(), nodeCollect.col(1).minCoeff(),
        nodeCollect.col(2).minCoeff();

    BB << nodeCollect.col(0).maxCoeff(), nodeCollect.col(1).maxCoeff(),
        nodeCollect.col(2).maxCoeff();
}

void Surface::splitSubZone()
{
    for (auto &f : faces)
    {
        if (subZone.find(f.zone_name) == subZone.end())
        {
            subZone[f.zone_name] = Surface();
            subZone[f.zone_name].title = f.zone_name;
        }
        subZone[f.zone_name].faces.push_back(f);
    }
}

void Surface::mapDataFromPointCloud(PointCloud *cloud) {}

void Surface::calculateValueFromFace(String valueName, String weight)
{
    // maxValue[valueName] = -DBL_MAX;
    // minValue[valueName] = DBL_MAX;
    averageValue[valueName] = 0.;
    Scalar count = 0;
    for (auto f : faces)
    {
        if (f.scalars.find(valueName) != f.scalars.end())
        {
            averageValue[valueName] +=
                f.scalars[valueName] * f.vectors[weight].norm();
            count += f.vectors[weight].norm();
        }
    }

    if (count)
        averageValue[valueName] /= count;
}

void Surface::convertScalarToVector(String scalar_0, String scalar_1,
                                    String scalar_2, String vector)
{
    for (auto &face : faces)
        face.convertScalarToVector(scalar_0, scalar_1, scalar_2, vector);
}

Block::Block(Vector referencePoint, label i, label j, label k, Scalar size_in)
{
    min = referencePoint;
    I = i;
    J = j;
    K = k;
    size = size_in;
    max = min + Vector(I * size, J * size, K * size);

    faceLink = List<List<Face *>>(I * J * K);
}

void Block::linkRelatedFaces(Surface *sf)
{
    for (auto &f : sf->faces)
    {
        label i_min = (label)((f.AA(0) - min(0)) / size);
        label j_min = (label)((f.AA(1) - min(1)) / size);
        label k_min = (label)((f.AA(2) - min(2)) / size);

        label i_max = (label)((f.BB(0) - min(0)) / size);
        label j_max = (label)((f.BB(1) - min(1)) / size);
        label k_max = (label)((f.BB(2) - min(2)) / size);

        for (label i = i_min; i <= i_max; i++)
            for (label j = j_min; j <= j_max; j++)
                for (label k = k_min; k <= k_max; k++)
                    faceLink[k * I * J + j * I + i].push_back(&f);
    }
}

void Block::mapSurfaceFromPointCloud(PointCloud *cloud, Surface *sf,
                                     Scalar tolerance)
{
    typedef boost::geometry::model::point<Scalar, 3,
                                          boost::geometry::cs::cartesian>
        point_type;
    typedef boost::geometry::model::polygon<point_type> polygon_type;

    label lost = 0;
    label finish = 0;
    label percent = 0;
    label length = cloud->storage.size();
#pragma omp parallel for
    // for (auto &dataPoint : cloud->storage)
    for (long p_i = 0; p_i < cloud->storage.size(); p_i++)
    {
        auto dataPoint = cloud->storage[p_i];
        Scalar min_d = boost::numeric::bounds<double>::highest();
        label min_f;

        point_type dataPointCoord(dataPoint.coord(0), dataPoint.coord(1),
                                  dataPoint.coord(2));

        label i_mid = (label)((dataPoint.coord(0) - min(0)) / size);
        label j_mid = (label)((dataPoint.coord(1) - min(1)) / size);
        label k_mid = (label)((dataPoint.coord(2) - min(2)) / size);

        label i_min = ((i_mid - 1) < 0) ? 0 : i_mid - 1;
        label j_min = ((j_mid - 1) < 0) ? 0 : j_mid - 1;
        label k_min = ((k_mid - 1) < 0) ? 0 : k_mid - 1;

        label i_max = ((i_mid + 1) > I) ? I - 1 : i_mid + 1;
        label j_max = ((j_mid + 1) > J) ? J - 1 : j_mid + 1;
        label k_max = ((k_mid + 1) > K) ? K - 1 : k_mid + 1;

        for (label i = i_min; i <= i_max; i++)
            for (label j = j_min; j <= j_max; j++)
                for (label k = k_min; k <= k_max; k++)
                    for (auto &f : faceLink[k * I * J + j * I + i])
                    {
                        polygon_type poly;
                        for (auto n : f->nodes)
                        {

                            boost::geometry::append(
                                poly.outer(),
                                point_type(sf->nodes[n].coord(0),
                                           sf->nodes[n].coord(1),
                                           sf->nodes[n].coord(2)));
                        }
                        Scalar d =
                            boost::geometry::distance(dataPointCoord, poly);
                        if (d < min_d)
                        {
                            min_d = d;
                            min_f = f->id;
                        }
                    }
#pragma omp critical
        {
            if (min_d > tolerance)
            {
                lost++;
            }
            else
            {
                dataPoint.linkFace = min_f;
                dataPoint.linked = true;
                // std::cout << min_f << std::endl;
                finish++;
            }

            if (((label)((Scalar)finish / length * 100)) > percent)
            {
                percent = (label)((Scalar)finish / length * 100);
                std::cerr << "Finsh point: " << percent << "%"
                          << "\r";
            }
        }
    }
    std::cerr << std::endl;
    std::cerr << "Warning: " << lost << "(" << (Scalar)lost / length * 100
              << "%"
              << ") points lost by tolerance " << tolerance << "." << std::endl;
}

bool PointCloud::readData(String filename, int *coordIndex,
                          Map<String, label> field_index, bool hasHeader)
{
    std::cout << "Read .csv file from " << filename << "." << std::endl;
    std::fstream _file;
    _file.open(filename.c_str(), std::ios::in);
    if (!_file)
        return EXIT_FAILURE;

    CsvParser *csvparser = CsvParser_new(filename.c_str(), ",", hasHeader);
    CsvRow *row;

    label idCount = 0;
    while ((row = CsvParser_getRow(csvparser)))
    {
        const char **rowFields = CsvParser_getFields(row);

        Point p_temp;
        p_temp.name = rowFields[0];
        p_temp.coord << std::stod(rowFields[coordIndex[0]]),
            std::stod(rowFields[coordIndex[1]]),
            std::stod(rowFields[coordIndex[2]]);
        p_temp.id = idCount;
        for (auto field : field_index)
            p_temp.scalars[field.first] = std::stod(rowFields[field.second]);

        storage.push_back(p_temp);
        idCount++;
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);

    return EXIT_SUCCESS;
}

void PointCloud::convertDataToSurface(Surface *sf)
{
    label i = 0;
    // std::cout << storage.size() << std::endl;
    for (auto &p : storage)
    {
        if (!p.linked)
            continue;
        // std::cout << i++ << std::endl;
        // std::cerr << p.linkFace << std::endl;
        for (auto _value : p.scalars)
        {
            sf->faces[p.linkFace].scalars[_value.first] = _value.second;
        }

        for (auto _value : p.vectors)
        {
            sf->faces[p.linkFace].vectors[_value.first] = _value.second;
        }
    }
}

void PointCloud::calcAABB()
{
    // 此处的内存性能可能需要优化
    Eigen::Matrix<Scalar, -1, -1, Eigen::RowMajor> nodeCollect(storage.size(),
                                                               3);
    for (size_t i = 0; i < storage.size(); i++)
    {
        nodeCollect.row(i) << storage[i].coord;
    }

    AA << nodeCollect.col(0).minCoeff(), nodeCollect.col(1).minCoeff(),
        nodeCollect.col(2).minCoeff();

    BB << nodeCollect.col(0).maxCoeff(), nodeCollect.col(1).maxCoeff(),
        nodeCollect.col(2).maxCoeff();
}

void PointCloud::convertScalarToVector(String scalar_0, String scalar_1,
                                       String scalar_2, String vector)
{
    for (auto &p : storage)
        p.vectors[vector] = Vector(p.scalars[scalar_0], p.scalars[scalar_1],
                                   p.scalars[scalar_2]);
}

void PointCloud::rotate(Scalar theta, Vector axis)
{
    Eigen::AngleAxis<Scalar> t_V(theta, axis);
    Eigen::Matrix3d t_R = t_V.matrix();
    // std::cout << t_R << std::endl;

    for (auto &n : storage)
    {
        n.coord *= t_R;
        for (auto vectorKey : n.vectors)
        {
            n.vectors[vectorKey.first] *= t_R;
        }
    }
}

Scalar PointCloud::integral(String x, String y)
{
    Scalar result = 0.;
    for (auto p : storage)
        result += p.scalars[x] * p.scalars[y];
    return result;
}

Vector PointCloud::integralVector(String scalar, String vector)
{
    Vector result(0., 0., 0.);
    for (auto p : storage)
        result += p.scalars[scalar] * p.vectors[vector];
    return result;
}

Vector PointCloud::integralVectorWithCoord(String scalar, String vector,
                                           Vector refPoint)
{
    Vector result(0., 0., 0.);
    for (auto p : storage)
        result +=
            (p.coord - refPoint).cross(p.scalars[scalar] * p.vectors[vector]);
    return result;
}

/*
Scalar PointCloud::integral(String x, String y)
{
    Scalar result = 0.;
    for (auto p : storage)
        result += p.scalar[x] * p.scalar[y];
    return result;
}
*/
} // namespace SmileGL