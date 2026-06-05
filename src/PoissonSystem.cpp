#include "PoissonSystem.h"
#include "MeshType.h"
#include "ScalarField.h"


PoissonSystem::PoissonSystem(const MeshType& Mesh)
    : LinearSystemType(Mesh)
{
}

void PoissonSystem::BuildA(const MeshType& Mesh) {
    ROW.clear();
    COL.clear();
    VAL.clear();

    int row;

    // North and South Boundaries
    for (int i=0; i<Nx2; i++) {
        // south
        row = i;
        addEntry(row,row,1.0);

        //north
        row = (Ny2-1)*Nx2 + i;
        addEntry(row,row,1.0);
    }

    // West and East Boundaries
    for (int j=1; j<Ny2-1; j++) {
        // west 
        row = j*Nx2;
        addEntry(row,row,1.0);

        // east
        row = j*Nx2 + (Nx2-1);
        addEntry(row,row,1.0);
    }

    // interior nodes
    for (int i=1; i<=Nx; i++){
        for (int j=1; j<=Ny; j++){
            
            double dxe = Mesh.xc[i+1] - Mesh.xc[i];
            double dxw = Mesh.xc[i]   - Mesh.xc[i-1];
            double dyn = Mesh.yc[j+1] - Mesh.yc[j];
            double dys = Mesh.yc[j]   - Mesh.yc[j-1];

            double Ae = Mesh.yf[j] - Mesh.yf[j-1];
            double Aw = Ae;
            double An = Mesh.xf[i] - Mesh.xf[i-1];
            double As = An;

            double ae = Ae/dxe;
            double aw = Aw/dxw;
            double an = An/dyn;
            double as = As/dys;

            double ap = ae+aw+an+as;

            addEntry(row,row,ap);
            addEntry(row,row+1,-ae);
            addEntry(row,row-1,-aw);
            addEntry(row,row+Nx2,-an);
            addEntry(row,row-Nx2,-as);

        }
    }

}

void PoissonSystem::BuildRHS(const MeshType& Mesh, const ScalarField& omega) {
    std::fill(B.begin(), B.end(), 0.0);

    // Boundaries
    // South + North boundaries
    for (int i=0; i<Nx2; i++) {
        setRHS(i,0,0.0);
        setRHS(i,Ny2-1,0.0);
    }

    // West + East boundaries
    for (int j=1; j<Ny2-1; j++){
        setRHS(0,j,0.0);
        setRHS(Nx2-1,j,0.0);
    }
    
    // Fill internal nodes
    for(int i=1;i<=Nx;i++) {
        for(int j=1;j<=Ny;j++) {
            double Vol = (Mesh.xf[i]-Mesh.xf[i-1])*(Mesh.yf[j]-Mesh.yf[j-1]);
            setRHS(i,j,-omega.get(i,j)*Vol);
        }
    }


}