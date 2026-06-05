// Other source files
#include "meshType.h"
#include "nonUniformGrid.h"
#include "uniformGrid.h"
#include "ScalarField.h"
#include "SimulationTime.h"
#include "LinearSystemType.h"
#include "PoissonSystem.h"
#include "VectorField.h"

// Important Libraries
#include <iostream>
#include <cmath>


main() {
 // - - - - - - - - - preprocessing - - - - - - - - - - //
    
    // Create Mesh
    // UniformGrid mesh;      // uniform mesh   
    NonUniformGrid mesh;   // non uniform mesh
    mesh.create("input/mesh.inp"); 

    // initialize runTime
    SimulationTime runTime("input/controlDict.inp");

    // Create scalar fields
    ScalarField omega(mesh,"omega");
    ScalarField psi(mesh,"psi");

    // Set omega to zero everywhere
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

//  // - - - - - - - - - the time loop - - - - - - - - - - //
//     while (runTime.run()) {

//         // Increment Time
//         runTime.advance();
//         std::cout << std::string(50, '=') << std::endl;
//         std::cout << "Running: t = " << runTime.time << std::endl;
    

//         // Solve Vorticity Transport


//         // Solve Poisson Equation

//         // Compute Velocity

//         // Update Wall Vorticity

    
//         // Output
//         if (runTime.writeNow()) {
            
//         }

//     }

    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Complete!";

    return 0;
}