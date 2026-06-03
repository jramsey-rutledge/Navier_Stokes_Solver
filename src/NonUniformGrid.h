// header file

// header guards
#ifndef NONUNIFORMGRID_H
#define NONUNIFORMGRID_H

#include <fstream>
#include <sstream>
#include <vector>
#include "FileIO.h"
#include "MeshType.h"


// structure definitons
class NonUniformGrid : public MeshType {
    public:
    double beta_x, beta_y;        // clustering strength

    void create() override;

};

#endif