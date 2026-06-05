#include "LinearSystemType.h"
#include "MeshType.h"
#include "ScalarField.h"
#include "VectorField.h"
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include "Eigen/Sparse"
#include "Eigen/SparseLU"
using namespace std;

// Member Functions Defined 
// Initialize
LinearSystemType::LinearSystemType(const MeshType & Mesh){
    Nx = Mesh.Nx ;
    Ny = Mesh.Ny ;
    Nx2 = Nx + 2;
    Ny2 = Ny + 2;
    B.assign ( Nx2 * Ny2 , 0.0);
}

// add a matrix entry at row , col
void LinearSystemType::addEntry ( int row , int col , double val ){
    ROW.push_back ( row );
    COL.push_back ( col );
    VAL.push_back ( val );
}

// set RHS at cell (i , j )
void LinearSystemType::setRHS ( int i , int j , double val ){
    B[ i + j * Nx2 ] = val ;
}

// get RHS at cell (i , j )
double LinearSystemType::getRHS ( int i , int j ) const {
    return B [ i + j * Nx2 ];
}

// Solve Matrix
void LinearSystemType::solve(ScalarField& phi){
  int Ntot = Nx2 * Ny2;

  // load matrix
  Eigen::SparseMatrix<double> A(Ntot, Ntot);
  std::vector<Eigen::Triplet<double>> triplets;
  triplets.reserve(VAL.size());
  for (size_t k = 0; k < VAL.size(); ++k){
    triplets.emplace_back(ROW[k], COL[k], VAL[k]);
  }
  A.setFromTriplets(triplets.begin(), triplets.end());

  // load right-hand-side
  Eigen::VectorXd RHS(Ntot);
  for (int i = 0; i < Ntot; ++i)
  {
    RHS[i] = B[i];
  }

  // compute the LU factorization of A
  Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
  solver.compute(A);
  if(solver.info() != Eigen::Success) 
  {
    std::cerr << "Decomposition failed!\n";
    return;
  }

  // solve
  Eigen::VectorXd C = solver.solve(RHS);
  if(solver.info() != Eigen::Success) 
  {
    std::cerr << "Solving failed!\n";
    return;
  }

  // load solution into ScalarField T
  for (int j = 0; j < Ny2; ++j)
  {
    for (int i = 0; i < Nx2; ++i)
    {
      phi.set(i, j, C[i + j*Nx2]);
    }
  }
}
