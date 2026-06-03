// header file

// header guards
#ifndef UNIFORMGRID_H
#define UNIFORMGRID_H

#include <fstream>
#include <sstream>
#include <vector>
#include "FileIO.h"
#include "MeshType.h"


// structure definitons
class UniformGrid : public MeshType {
    public:

// function prototypes
/**
 * @brief constructor of Mesh grid
 * 
 * @param Mesh passed by reference to make a copy
 */
void create() override;




};

#endif