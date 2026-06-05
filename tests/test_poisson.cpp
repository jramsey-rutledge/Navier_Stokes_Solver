#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include "../src/MeshType.h"
#include "../src/NonUniformGrid.h"
#include "../src/UniformGrid.h"
#include "../src/PoissonSystem.h"
#include "../src/ScalarField.h"
#include "../src/VectorField.h"

/**
 * Zero Voriticity Test
 * 
 * Phi should remain zero to prove no issues in RHS and A matrix building. 
 */
void zero_voriticity_test() {
    // Create Mesh
    NonUniformGrid mesh;  
    mesh.create("../input/mesh.inp"); 

    // Create scalar fields
    ScalarField omega(mesh,"omega");
    ScalarField psi(mesh,"psi");

    // Set omega to zero everywhere
    for(int i=0; i<mesh.Nx+2; i++){
        for(int j=0; j<mesh.Ny+2; j++){
            omega.set(i,j,0.0);
        }
    }

    PoissonSystem poisson(mesh);

    poisson.BuildA(mesh);
    poisson.BuildRHS(mesh,omega);
    poisson.solve(psi);

    VectorField U("U", mesh);
    U.ComputeFromStreamFunction(mesh,psi);

    psi.write(0.0);

    for (int i=0; i<mesh.Nx; i++){
        for (int j=0; j<mesh.Ny; j++){
            if (psi.get(i,j) != 0) {
                std::cout<<"Nonzero Value Detected"<<std::endl;
            }
        }
    }
}


/**
 * Vorticity Blob Test - A small set of omega is set to non-zero values
 * 
 * Solutions should appear with smooth streamfunction contours, no checkerboarding,
 * and symmetry when expected
 */
void blob() {
    // Create Mesh
    UniformGrid mesh;  
    mesh.create("../input/mesh.inp"); 

    // Create scalar fields
    ScalarField omega(mesh,"omega");
    ScalarField psi(mesh,"psi");

    // Create Gaussian Blob in omega
    double xc = 0.5*mesh.Lx;
    double yc = 0.5*mesh.Ly;
    double sigma = 0.1*mesh.Lx;

    for(int i=1; i<=mesh.Nx; i++){
        for(int j=1; j<=mesh.Ny; j++){
            double x = mesh.xc[i];
            double y = mesh.yc[j];
            double r2 = (x-xc)*(x-xc) + (y-yc)*(y-yc);
            double w = exp(-r2/(sigma*sigma));
            omega.set(i,j,w);
        }
    }

    PoissonSystem poisson(mesh);

    poisson.BuildA(mesh);
    poisson.BuildRHS(mesh,omega);
    poisson.solve(psi);

    VectorField U("U", mesh);
    U.ComputeFromStreamFunction(mesh,psi);

    psi.write(0.0);
    U.write(0.0);

    // double psiMax = -1e20;
    // double psiMin =  1e20;

    // for(int i=1;i<=mesh.Nx;i++){
    //     for(int j=1;j<=mesh.Ny;j++){
    //         psiMax = std::max(psiMax,psi.get(i,j));
    //         psiMin = std::min(psiMin,psi.get(i,j));
    //     }
    // }

    // std::cout << "psiMin = " << psiMin << std::endl;
    // std::cout << "psiMax = " << psiMax << std::endl;
}

/**
 * Manufactured solution convergence test for the Poisson solver.
 * 
 * Solutions should converge to 
 * with second-order accuracy
 */


int main() {
    std::cout<<"Beginning Test 1"<<std::endl;
    blob();
    std::cout<<"End of Test 1"<<std::endl;
}
