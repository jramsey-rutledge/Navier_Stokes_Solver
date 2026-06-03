// Other source files
#include "meshType.h"
#include "nonUniformGrid.h"
#include "uniformGrid.h"
#include "ScalarField.h"
#include "SimulationTime.h"

// Important Libraries


main() {
 // - - - - - - - - - preprocessing - - - - - - - - - - //
    
    // Create Mesh
    // UniformGrid Mesh;      // uniform mesh   
    NonUniformGrid Mesh;   // non uniform mesh
    Mesh.create(); 

    // initialize runTime
    SimulationTime runTime;



 // - - - - - - - - - the time loop - - - - - - - - - - //
    return 0;
}