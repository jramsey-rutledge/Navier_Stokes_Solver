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


main() {
 // - - - - - - - - - preprocessing - - - - - - - - - - //
    
    // Create Mesh
    // UniformGrid mesh;      // uniform mesh   
    NonUniformGrid mesh;   // non uniform mesh
    mesh.create(); 

    // initialize runTime
    SimulationTime runTime;

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