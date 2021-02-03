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

#ifndef fluent_IO_h
#define fluent_IO_h

#include "fluent_value.h"
#include "mesh.h"
#include <fstream>
#include <iostream>
#include <string>
namespace FLUENT
{
    MESH::Mesh readFluentMesh(string filename);
    void readFluentNode(List<MESH::Node> *nodes);
    void readFluentFace(List<MESH::Face> *faces);
    void readFluentCell(List<MESH::Cell> *cells);

    void readNodeHeader(int info_index, string info, MESH::Mesh *mesh,
                        MESH::Zone *zone);
    void readFaceHeader(int info_index, string info, MESH::Mesh *mesh,
                        MESH::Zone *zone);
    void readCellHeader(int info_index, string info, MESH::Mesh *mesh,
                        MESH::Zone *zone);

    void readNodeData(int ND, string info, MESH::Mesh *mesh, MESH::Zone *zone,
                      label data_index);

    void readFaceData(string info, MESH::Mesh *mesh, MESH::Zone *zone, int *n_node,
                      label *n_face);

    long long hextoll(string s);
    // Module index in Fluent Mesh file

} // namespace FLUENT
#endif