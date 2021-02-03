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
#ifndef GEO_INTERSECT_H
#define GEO_INTERSECT_H
#include "mesh.h"

bool triIntersectWithHex(Triangle triVertex, Hex hexVertex);
bool lineCrossTri(Line line, Triangle tri);
Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> plucker(Vector a, Vector b);
inline Scalar side_operator(Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> a, Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> b);
#endif