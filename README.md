# 2D Lid-Driven Navier Stokes
This project implements a C++ solver 

**Author:**
- Jenna Ramsey-Rutledge


## Background



## Physics and Mathematical Model

### Governing Equations


### Initial and Boundary Conditions


## Numerical Methods


## Verification


## Applying the Solver
.

## Results


## Quick Start

### Prerequisites

- C++17-compatible compiler
- GNU Make
- Eigen 5.0.0+

### Building and Running

```bash
# Clone the repository
git clone <repo-url>
cd Navier_Stokes_Solver

# Ensure that the makefile has the appropriate path to the Eigen library on your device

# Compile the project
make build

# Run the program
./build/solver.exe

# Remove compiled artifacts
make clean

# Build and run in one step
make all
```

### Adjusting the Simulation

Edit the CSV files in `input/` to change the spatial domain, velocity domain, or resolution before building


## Project Structure

```
vlasov_maxwell/
├── src/                      # Source and header files
│   ├── FileIO.{cpp,h}                  # Helper functions for reading inputs
│   ├── Mesh.{h}                        # Parent class for mesh
│   ├── UniformMesh.{cpp,h}             # Uniform mesh
│   ├── NonUniformMesh.{cpp,h}          # Nonuniform mesh
│   ├── Operators.{cpp,h}               # Gradient and integrate operators
│   ├── ScalarField.{cpp,h}             # Scalar field data structure for charge density
│   ├── SimulationTime.{cpp,h}          # Time stepping
│   ├── VectorField.{cpp,h}             # Vector field data structure for electric field 
│   ├── main.cpp
│   └── README.md
├── input/                    # Configuration files
│   ├── controlDict.inp                   # Time stepping parameters
│   ├── mesh.inp                          # Spatial Dimensions
│   ├── nonUniformGrid.inp                # Mesh-warping parameter
│   ├── C.inp                             # Physical Properties
│   └── README.md
├── output/                   # Results
├── scripts/                  # Postprocessing scripts
|   ├── plot_results.py                 # Produces visualizations of charge density and the Electric field
│   └── README.md                       
├── tests/                    # Test Module
│   ├── test_poisson.cpp               # Runs tests for building the poisson equation 
│   ├── test_solver.cpp                # Runs tests for the iterative implicit solver
|   ├── mms.cpp                        # Runs method of manufactured solution test
│   └── makefile                       # Build test suites
├── makefile                  # Build configuration
└──README.md                  # This file
```

## References

Many source files are adapted from previous work done with Byron Selvage and Kyle Sperberg. 
