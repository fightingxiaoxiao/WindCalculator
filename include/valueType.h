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

#ifndef valueType_h
#define valueType_h

#define EIGEN_VECTORIZE
#define USE_INTEL_MKL_ALL
#define _USE_MATH_DEFINES
#include <Eigen/Dense>
#include <map>
#include <math.h>
#include <nlohmann/json.hpp>
#include <omp.h>
#include <vector>

typedef size_t label;

typedef double Scalar;
typedef std::string String;

typedef Eigen::Matrix<double, 1, 3, Eigen::RowMajor> Vector;
typedef Eigen::Matrix<Scalar, 2, 3, Eigen::RowMajor> Line;
typedef Eigen::Matrix<Scalar, 3, 3, Eigen::RowMajor> Triangle;
// 六面体的八个顶点依次为x-y-z-,x+y-z-,x+y+z-,x-y+z-,x-y-z+,x+y-z+,x+y+z+,x-y+z+
typedef Eigen::Matrix<Scalar, 8, 3, Eigen::RowMajor> Hex;

template <class T> using List = std::vector<T>;

template <class Key, class Value> using Map = std::map<Key, Value>;

using json = nlohmann::json;

#ifndef __DBL_EPSILON__
#define __DBL_EPSILON__ DBL_EPSILON
#endif
/*
template <class T> class List : public vector<T>
{
};
*/
#endif