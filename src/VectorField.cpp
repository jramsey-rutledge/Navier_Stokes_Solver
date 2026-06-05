#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

#include "VectorField.h"
#include "ScalarField.h"

VectorField::VectorField(const string& fieldName, const MeshType& mesh) {
    name = fieldName;
    Nx = mesh.Nx;
    Ny = mesh.Ny;
    Nx2 = Nx + 2;
    Ny2 = Ny + 2;

    vx.assign(Nx2 * Ny2, 0.0);
    vy.assign(Nx2 * Ny2, 0.0);
}

double VectorField::get_x(const int i, const int j) const {
    double val = vx[i + j * Nx2];

    return val;
}

double VectorField::get_y(const int i, const int j) const {
    double val = vy[i + j * Nx2];

    return val;
}

void VectorField::set_x(const int i, const int j, const double val) {
    vx[i + j * Nx2] = val;
}

void VectorField::set_y(const int i, const int j, const double val) {
    vy[i + j * Nx2] = val;
}

VectorField VectorField::operator+(const VectorField& other) const {
    if (Nx2 != other.Nx2 || Ny2 != other.Ny2) {
        throw std::runtime_error("VectorField::operator+: field sizes do not match");
    }

    VectorField result = *this;
    result.name = name + "_plus_" + other.name;

    for (int i = 0; i < Nx2; ++i) {
        for (int j = 0; j < Ny2; ++j) {
            result.set_x(i, j, get_x(i, j) + other.get_x(i, j));
            result.set_y(i, j, get_y(i, j) + other.get_y(i, j));
        }
    }

    return result;
}

void VectorField::write(double t) {
    std::string path = "output/" + name + "_" + std::to_string(t) + ".dat";
    std::ofstream file(path);

    file << std::scientific << std::setprecision(16);

    file << "# Ex Ey\n";
    for (int j = 1; j <= Ny; j++) {
        for (int i = 1; i <= Nx; i++) {
            file << get_x(i, j) << " " << get_y(i, j) << "\n";
        }
    }

    file.close();

}

void VectorField::ComputeFromStreamFunction(const MeshType& Mesh,const ScalarField& psi) {
    int Nx = Mesh.Nx;
    int Ny = Mesh.Ny;

    for (int i=1; i<=Nx; i++) {
        for (int j=1; j<=Ny; j++) {

            double dy =  Mesh.yc[j+1] - Mesh.yc[j-1];

            double dx = Mesh.xc[i+1] - Mesh.xc[i-1];

            double u = (psi.get(i,j+1)-psi.get(i,j-1))/dy;

            double v = -(psi.get(i+1,j)-psi.get(i-1,j))/dx;

            set_x(i,j,u);
            set_y(i,j,v);
        }
    }

    // bottom and top
    for(int i=0;i<Nx2;i++) {
        set_x(i,0,0.0);
        set_y(i,0,0.0);

        set_x(i,Ny+1,1.0);   // lid velocity
        set_y(i,Ny+1,0.0);
    }

    // left and right
    for(int j=0;j<Ny2;j++){
        set_x(0,j,0.0);
        set_y(0,j,0.0);

        set_x(Nx+1,j,0.0);
        set_y(Nx+1,j,0.0);
    }
}
