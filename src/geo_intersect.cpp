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

#include "geo_intersect.h"

bool triIntersectWithHex(Triangle tri, Hex hex)
{
    // 至少一个三角形顶点在六面体内
    for (int i = 0; i < 3; i++)
    {
        if ((tri(i, 0) >= hex(0, 0)) &&
            (tri(i, 0) <= hex(6, 0)) &&

            (tri(i, 1) >= hex(0, 1)) &&
            (tri(i, 1) <= hex(6, 1)) &&

            (tri(i, 2) >= hex(0, 2)) &&
            (tri(i, 2) <= hex(6, 2)))
        {
            //std::cout << "至少一个三角形顶点在六面体内." << std::endl;
            return true;
        }
    }

    // 三角形与六面体相交
    for (int i = 1; i < 8; i++)
    {
        Line ray;
        ray << hex.row(0), hex.row(i);
        if (lineCrossTri(ray, tri))
        {
            //std::cout << "三角形与六面体相交." << std::endl;
            return true;
        }
    }

    // 不存在关联
    //std::cout << "不存在关联." << std::endl;
    return false;
}

// 参考
bool lineCrossTri(Line line, Triangle tri)
{
    auto e1 = plucker(tri.row(0), tri.row(1));
    auto e2 = plucker(tri.row(1), tri.row(2));
    auto e3 = plucker(tri.row(2), tri.row(0));
    auto L1 = plucker(line.row(0), line.row(1));
    Scalar s1 = side_operator(L1, e1);
    Scalar s2 = side_operator(L1, e2);
    Scalar s3 = side_operator(L1, e3);
    if (fabs(s1) < __DBL_EPSILON__ && fabs(s2) < __DBL_EPSILON__ && fabs(s3) < __DBL_EPSILON__)
        return true;
    if ((s1 > 0 && s2 > 0 && s3 > 0) || (s1 < 0 && s2 < 0 && s3 < 0))
    {
        auto L2 = plucker(tri.row(0), line.row(1));
        auto L3 = plucker(line.row(2), tri.row(0));
        auto L4 = e2;
        Scalar s4 = side_operator(L4, L3);
        Scalar s5 = side_operator(L4, L2);
        if (fabs(s4) < __DBL_EPSILON__ || fabs(s5) < __DBL_EPSILON__)
            return true;
        if ((s4 > 0 && s5 > 0) || (s4 < 0 && s5 < 0))
            return true;
        else
            return false;
    }
    else
        return false;
}

Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> plucker(Vector a, Vector b)
{
    Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> res;
    res << a(0) * b(1) - b(0) * a(1),
        a(0) * b(2) - b(0) * a(2),
        a(0) - b(0),
        a(1) * b(2) - b(1) * a(2),
        a(2) - b(2),
        b(1) - a(1);
    return res;
}

inline Scalar side_operator(
    Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> a,
    Eigen::Matrix<Scalar, 1, 6, Eigen::RowMajor> b)
{
    return a(0) * b(4) + a(1) * b(5) + a(2) * b(3) + a(3) * b(2) + a(4) * b(0) + a(5) * b(1);
}