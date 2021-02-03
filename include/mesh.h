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

#ifndef mesh_h
#define mesh_h

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "valueType.h"
#include "geo_intersect.h"
namespace SmileGL
{
    class Node;
    class Face;
    class Cell;
    class Zone;
    class Mesh;
    class PointCloud;
    // 网格·节点类
    class Node
    {
    public:
        label id;
        int zone_id;

        Vector coord;

        Map<label, Scalar> scalars;
        Map<label, Vector> vectors;

        void get_id(label node_id);
        void get_coord(Vector node_coord);
    };

    // 网格·面类
    class Face
    {
    public:
        //编号
        label id;
        int zone_id;
        String zone_name = "N/A"; // 所属域名称

        //法线
        Vector n0;
        Vector n1;

        Vector centroid = Vector(0., 0., 0.);

        // 包围盒
        Vector AA;
        Vector BB;

        Map<String, Scalar> scalars;
        Map<String, Vector> vectors;

        List<label> nodes;
        List<label> cells;

        void add_node(label node_id);
        void convertScalarToVector(String scalar_0, String scalar_1, String scalar_2, String vector);
    };

    // 网格·单元类
    class Cell
    {
    public:
        label id;
        int zone_id;
        Vector center;
        Vector normal;
        String zone_name = "N/A";

        Map<label, Scalar> scalars;
        Map<label, Vector> vectors;

        List<label> nodes;
        List<Face *> faces;
    };

    class Zone
    {
    public:
        int id;
        String name = "";
        label start = -1;
        label end = -1;
        String type; // node, face or cell
        //FLUENT::CELL_TYPE cell_type;
        int face_type;
    };

    class Mesh
    {
    public:
        String title;

        List<Node> nodes;
        List<Face> faces;
        List<Cell> cells;

        Map<label, Zone> zones;
        Map<String, label> zones_by_name;

        void createZone(int num);
        void transform(Scalar, Scalar, Scalar);
        // Mesh();
    };

    class Surface
    {
    public:
        String title;
        List<Node> nodes;
        List<Face> faces;

        Vector AA;
        Vector BB;

        Map<String, Surface> subZone;

        Map<String, Scalar> averageValue;
        Map<String, Scalar> maxValue;
        Map<String, Scalar> minValue;

        bool readOBJ(String);
        void transform(Scalar, Scalar, Scalar);
        void calcFaceCenter();
        void calcAABB(bool);
        void splitSubZone();
        void convertScalarToVector(String scalar_0, String scalar_1, String scalar_2, String vector);

        void calculateValueFromFace(String, String); //统计面数据

        void mapDataFromPointCloud(PointCloud *);
    };

    class Point
    {
    public:
        label id;
        String name;
        Vector coord;
        Vector normal;
        String zone_name;

        label linkFace;
        bool linked = false;
        Map<String, Scalar> scalars = {};
        Map<String, Vector> vectors = {};
    };

    class PointCloud
    {
    public:
        List<Point> storage;
        Vector AA;
        Vector BB;
        bool readData(String filename, int *coordIndex, Map<String, size_t> field_index, bool hasHeader);
        void convertDataToSurface(Surface *);

        void calcAABB();
        void convertScalarToVector(String scalar_0, String scalar_1, String scalar_2, String vector);
        Scalar integral(String x, String y);
        Vector integralVector(String scalar, String vector);
        Vector integralVectorWithCoord(String scalar, String vector, Vector refPoint);
        void rotate(Scalar theta, Vector axis);
    };

    class Block
    {
    public:
        Vector max;
        Vector min;

        label I, J, K;
        Scalar size;

        List<List<Face *>> faceLink;
        Block(Vector min, label I, label J, label K, Scalar size);
        void linkRelatedFaces(Surface *);
        void mapSurfaceFromPointCloud(PointCloud *, Surface *, Scalar);
    };
} // namespace SmileGL
#endif
