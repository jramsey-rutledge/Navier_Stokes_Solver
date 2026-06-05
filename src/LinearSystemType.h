// header file

// header guards
#ifndef LINEARSYSTEMTYPE_H
#define LINEARSYSTEMTYPE_H

// libraries
#include <vector>
class MeshType;
class ScalarField;
class VectorField;


// structure definitions
class LinearSystemType {
public:
    int Nx , Ny ;               // number of cells in x and y
    int Nx2 , Ny2 ;             // include ghost cells  
    std::vector<int> ROW ;      // row indices of nonzeros
    std::vector<int> COL ;      // column indices of nonzeros
    std::vector<double> VAL ;   // values of nonzeros
    std::vector<double> B ;     // right - hand side vector

    // constructor
    LinearSystemType( const MeshType & Mesh );

    // add a matrix entry at row , col
    void addEntry ( int row , int col , double val );

    // set RHS at cell (i , j )
    void setRHS ( int i , int j , double val );

    // get RHS at cell (i , j )
    double getRHS ( int i , int j ) const ;

    // solve
    void solve(ScalarField& phi);

    // universal destructor
    virtual ~LinearSystemType() = default;

};


#endif