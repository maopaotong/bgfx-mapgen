#pragma once


#include "delaunator/delaunator.h"
#include "DualMesh.h"
namespace mg
{
    using namespace delaunator;
    struct DualMap
    {
        

        DualMesh &mesh;
        std::vector<float> elevation_t;
        std::vector<float> elevation_r;
        DualMap(DualMesh &mesh) : mesh(mesh), elevation_r(mesh.numRegions, 0.0f), elevation_t(mesh.numSolidTriangles, 0.0f)
        {
        }
    };

};