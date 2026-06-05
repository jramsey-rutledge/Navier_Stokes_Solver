// header file

// header guards
#ifndef VORTICITYSYSTEM_H
#define VORTICITYSYSTEM_H

#include <fstream>
#include <sstream>
#include <vector>

#include "LinearSystemType.h"


class VorticitySystem : public LinearSystemType {
    public:

    void BuildA(const MeshType& Mesh, const VectorField& U, const ScalarField& omega,  double dt, double nu);

    void BuildRHS( const MeshType& Mesh, const ScalarField& omega, const ScalarField& omega_old, const VectorField& U, const double& dt );

};

#endif