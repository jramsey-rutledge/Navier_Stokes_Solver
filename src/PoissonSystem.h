// header file

// header guards
#ifndef POISSONSYSTEM_H
#define POISSONSYSTEM_H

#include <fstream>
#include <sstream>
#include <vector>

#include "LinearSystemType.h"


class PoissonSystem : public LinearSystemType {
    public:

        PoissonSystem(const MeshType& Mesh);

        void BuildA(const MeshType& Mesh);

        void BuildRHS(const MeshType& Mesh, const ScalarField& omega);

};

#endif
