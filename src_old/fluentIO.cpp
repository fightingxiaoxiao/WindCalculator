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


#include "fluentIO.h"
namespace FLUENT
{
long long hextoll(string s)
{
    long long num = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num += (s[i] - '0') * (long)pow(16, s.size() - 1 - i);
        else
            num += (s[i] - 'a' + 10) * (long)pow(16, s.size() - 1 - i);
    }

    return num;
}

// read mesh file from fluent
MESH::Mesh readFluentMesh(string filename)
{
    ifstream file;
    file.open(filename.data());
    assert(file.is_open());

    char word;
    // char pre_word;
    file >> noskipws;
    int data_level = 0;
    int index_level = 0;
    string phrase = "";
    string pre_word = "";
    int module_index = -1;
    int module_info = 0;
    label data_index = 0;

    int n_data = 0;
    label n_face = 0;

    int ND = -1;
    MESH::Zone zone_temp;
    MESH::Mesh fluent_mesh;

    cout << endl << "SmileCFD Fluent Reader" << endl << endl;
    while (!file.eof())
    {
        file >> word;
        string _word(1, word);

        if (_word != " " && _word != "\n" && _word != "(" && _word != ")")
        {
            phrase += _word;
            continue;
        }
        else if (phrase.size() > 0) // 获得一个字段 //get a complete phrase
        {
            // 获得模块索引号
            // get the module index
            if (index_level == 1 && data_level == 0 && module_index < 0)
            {
                try
                {
                    module_index = stoi(phrase);
                    // cout << module_index << endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                    cout << "The index is not a legal number." << endl;
                    cin.get();
                }
            }
            // 获得索引层的其他信息(其实只有维度)
            // get other info from index cycle(only dimension)
            else if (index_level == 1 && data_level == 0 && module_index > 0)
            {
                if (module_index != 2)
                {
                    cout << "Error in index level." << endl;
                    cout << phrase << endl;
                }
                else
                {
                    int dim = stoi(phrase);
                    cout << "Dimension: " << dim << endl;
                    ND = dim;
                }
            }
            // 获得数据层的头部
            // get the head infomation of data
            else if (index_level == 2 && data_level == 1)
            {
                switch (module_index)
                {
                case NODES:
                    readNodeHeader(module_info, phrase, &fluent_mesh,
                                   &zone_temp);
                    break;
                case CELLS:
                    readCellHeader(module_info, phrase, &fluent_mesh,
                                   &zone_temp);
                    break;
                case FACES:
                    readFaceHeader(module_info, phrase, &fluent_mesh,
                                   &zone_temp);
                    break;
                default:
                    // cout << "GET FAILED" << endl;
                    break;
                }
                module_info++;
            }

            else if (index_level == 2 && data_level == 2)
            {
                switch (module_index)
                {
                case NODES:

                    readNodeData(ND, phrase, &fluent_mesh, &zone_temp,
                                 data_index);
                    // cout << fluent_mesh.nodes.size() << endl;
                    break;
                case FACES:
                    readFaceData(phrase, &fluent_mesh, &zone_temp, &n_data,
                                 &n_face);
                    // readFaceData(data_index);
                    break;
                }
                data_index++;

                if (pre_word == "\n")
                {
                    // cout << data_index << endl;
                    // data_index = 0;
                }
            }
            phrase = ""; //清空字段进行下一次读取
        }

        /* ---------------------------------------------------------- */
        if (_word == "(")
        {
            if (index_level == 0) //进入索引层
            {
                index_level++;
                continue;
            }
            else //累加索引层并累加数据层
            {
                index_level++;
                data_level++;
                continue;
            }
        }
        if (_word == ")")
        {
            index_level--;
            if (index_level == 0)
            {
                // cout << "this module has " << data_level << " part." << endl;
                module_index = -1;
                module_info = 0;
                data_index = 0;
                data_level = 0;
            }
            continue;
        }
        string pre_word = _word;
    }
    file.close();

    return fluent_mesh;
}

// read head info.
void readNodeHeader(int info_index, string info, MESH::Mesh *mesh,
                    MESH::Zone *zone)
{
    switch (info_index)
    {
    case 0: // zone-id
    {
        int zone_id = stoi(info);
        mesh->createZone(zone_id);
        mesh->zones[zone_id].type = "node";
        *zone = mesh->zones[zone_id];
        break;
    }
    case 1: // first-index
    {
        zone->start = hextoll(info);
        break;
    }
    case 2: // last-index
        zone->end = hextoll(info);
        break;

    case 3: // type
        break;
    case 4: // ND
        if (zone->id == 0)
        {
            mesh->nodes.resize(zone->end - zone->start + 1);
            cout << endl << "--------------------------------" << endl;
            cout << "Total Node: " << zone->end - zone->start + 1 << endl;
        }
        break;
    default:
        cout << "Wrong number for Node header." << endl;
        break;
    }
}

// read cell info.
void readCellHeader(int info_index, string info, MESH::Mesh *mesh,
                    MESH::Zone *zone)
{
    // cout << "read header" << endl;
    switch (info_index)
    {
    case 0: // zone-id
    {
        int zone_id = (int)hextoll(info);
        mesh->createZone(zone_id);
        mesh->zones[zone_id].type = "cell";
        *zone = mesh->zones[zone_id];
        break;
    }
    case 1: // first-index
    {

        zone->start = hextoll(info);
        break;
    }
    case 2: // last-index

        zone->end = hextoll(info);
        break;

    case 3: // type, 1 is active , 32 is unactive
        break;
    case 4: // element-type
        zone->cell_type = (CELL_TYPE)stoi(info);
        if (zone->id == 0)
        {
            mesh->cells.resize(zone->end - zone->start + 1);
            cout << "Total Cell: " << zone->end - zone->start + 1 << endl;
        }
        break;
    default:
        cout << "Wrong number for Cell header." << endl;
        break;
    }
}

// read face info.
void readFaceHeader(int info_index, string info, MESH::Mesh *mesh,
                    MESH::Zone *zone)
{
    // cout << "read header" << endl;
    switch (info_index)
    {
    case 0: // zone-id
    {
        int zone_id = (int)hextoll(info);
        mesh->createZone(zone_id);
        mesh->zones[zone_id].type = "cell";
        *zone = mesh->zones[zone_id];
        break;
    }
    case 1: // first-index
    {

        zone->start = hextoll(info);
        break;
    }
    case 2: // last-index

        zone->end = hextoll(info);
        break;

    case 3: // bc-type
        break;
    case 4: // face-type
        zone->face_type = (FACE_TYPE)stoi(info);
        if (zone->id == 0)
        {
            mesh->faces.resize(zone->end - zone->start + 1);
            cout << "Total Face: " << zone->end - zone->start + 1 << endl;
            cout << "--------------------------------" << endl << endl;
        }
        break;
    default:
        cout << "Wrong number for Node header." << endl;
        break;
    }
}

// read node data
void readNodeData(int ND, string info, MESH::Mesh *mesh, MESH::Zone *zone,
                  label data_index)
{
    int location = data_index % ND;
    label i = (label)data_index / ND;
    mesh->nodes[i].coord(location) = stod(info);
    mesh->nodes[i].id = i + 1;
}

// read face data
void readFaceData(string info, MESH::Mesh *mesh, MESH::Zone *zone, int *n_data,
                  label *n_face)
{
    // 当face类型为mixed(0)或多边形(5)时，第一个数据表示构成该面的节点数
    if (*n_data == 0)
    {
        (*n_face)++;
        mesh->faces[(*n_face) - 1].zone_id = zone->id;
        mesh->faces[(*n_face) - 1].id = *n_face;
        switch (zone->face_type)
        {
        case Mixed_f:
            *n_data = stoi(info) + 2;
            return;
        case Linear:
            *n_data = 2 + 2;
            break;
        case Tri_f:
            *n_data = 3 + 2;
            break;
        case Quad_f:
            *n_data = 4 + 2;
            break;
        case Polygon:
            *n_data = stoi(info) + 2;
            return;
        }
    }
    if (*n_data > 2)
    {
        mesh->faces[(*n_face) - 1].nodes.push_back(
            &mesh->nodes[hextoll(info) - 1]);
    }
    else
    {
        mesh->faces[(*n_face) - 1].cells.push_back(
            &mesh->cells[hextoll(info) - 1]);
        mesh->cells[hextoll(info) - 1].faces.push_back(
            &mesh->faces[(*n_face) - 1]);
    }
    /*
if (*n_data > 2)
    mesh->faces[(*n_face) - 1].nodes_cache.push_back(hextoll(info));
else
    mesh->faces[(*n_face) - 1].cells_cache.push_back(hextoll(info));
*/
    (*n_data)--;
}
} // namespace FLUENT
