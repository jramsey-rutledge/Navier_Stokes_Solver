#include <iostream>
#include <fstream>
#include <iomanip>
#include "ScalarField.h"


ScalarField::ScalarField(const MeshType& mesh, std::string fieldName)
    : Nx(mesh.Nx), Ny(mesh.Ny),
      Nx2(mesh.Nx + 2), Ny2(mesh.Ny + 2),
      fieldName(fieldName)
{
    data.assign((mesh.Nx + 2) * (mesh.Ny + 2), 0.0);
}

double ScalarField::get(const int i, const int j) const {
    return data[i + j * Nx2];
}

void ScalarField::set(const int i, const int j, const double value) {
    data[i + j * Nx2] = value;
}

void ScalarField::write(double t) const {
    std::string path = "output/" + fieldName + "_" + std::to_string(t) + ".dat";
    std::ofstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    file << std::scientific << std::setprecision(16);

    for (int j = 0; j < Ny+2; j++) {
        for (int i = 0; i < Nx+2; i++) {
            file << get(i, j) << "\n";
        }
    }

    file.close();
}
