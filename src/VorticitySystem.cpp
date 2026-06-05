#include "VorticitySystem.h"
#include "MeshType.h"
#include "VectorField.h"
#include "ScalarField.h"

void VorticitySystem::BuildA(const MeshType& Mesh, const VectorField& U, const ScalarField& omega,  double dt, double nu) {
    ROW.clear();
    COL.clear();
    VAL.clear();

    int row ;
    double a,b,g;
    double D = 0.026; // Diffusivity constant

    // south / north boundary conditions
    for (int i = 1; i <= Nx; i++) {
        // south
        row = i ;
        omega.BC.south(Mesh.xc[i],0.0,a,b,g);
        addEntry(row,row,0.5*a+b/Mesh.dy[0]);
        addEntry(row,row + Nx2,0.5*a-b/Mesh.dy[0]);

        // north
        row = (Ny2-1)* Nx2 + i;
        omega.BC.north(Mesh.xc[i],0.0,a,b,g);
        addEntry(row,row,0.5*a+b/Mesh.dy[Ny-1]);
        addEntry(row,row - Nx2,0.5*a-b/Mesh.dy[Ny-1]);
    }

    // east / west boundary conditions
    for (int j = 1; j <= Ny; j++) {
    // west 
        row = j * Nx2;
        omega.BC.west(Mesh.yc[j],0.0,a,b,g);
        addEntry(row,row,0.5*a+b/Mesh.dx[0]);
        addEntry(row,row+1, 0.5*a-b/Mesh.dx[0]);

    // east
        row = (j+1) * Nx2 - 1;
        omega.BC.east(Mesh.yc[j],0.0,a,b,g);
        addEntry(row,row,a*0.5+b/Mesh.dx[Nx-1]);
        addEntry(row,row-1,a*0.5-b/Mesh.dx[Nx-1]);

    }

    // 5-point stencil
    for (int i=1; i<=Nx; i++) {
        for (int j=1; j<=Ny; j++) {
            row = j*Nx2 + i;
            
            // Geometry
            double dxe = Mesh.xc[i+1] - Mesh.xc[i];
            double dxw = Mesh.xc[i]   - Mesh.xc[i-1];
            double dyn = Mesh.yc[j+1] - Mesh.yc[j];
            double dys = Mesh.yc[j]   - Mesh.yc[j-1];

            double Ae = Mesh.yf[j] - Mesh.yf[j-1];
            double Aw = Ae;
            double An = Mesh.xf[i] - Mesh.xf[i-1];
            double As = An;

            // Diffusion
            double ae = D * Ae / dxe;
            double aw = D * Aw / dxw;
            double an = D * An / dyn;
            double as = D * As / dys;

            // Fluxes (must be fixed with updates to ScalarField)
            double ue = 0.5*(U.get_x(i,j) + U.get_x(i+1,j));
            double uw = 0.5*(U.get_x(i,j) + U.get_x(i-1,j));
            double vn = 0.5*(U.get_y(i,j) + U.get_y(i,j+1));
            double vs = 0.5*(U.get_y(i,j) + U.get_y(i,j-1));

            double Fe = ue * Ae;
            double Fw = uw * Aw;
            double Fn = vn * An;
            double Fs = vs * As;

            // Central differencing convection
            double cE =  0.5*Fe;
            double cW = -0.5*Fw;
            double cN =  0.5*Fn;
            double cS = -0.5*Fs;
            double cP = 0.5*(Fe-Fw+Fn-Fs);

            double a_time = (Mesh.xf[i]-Mesh.xf[i-1]) * (Mesh.yf[j]-Mesh.yf[j-1]) / dt; // transient term
            double ap = ae+aw+an+as+a_time;
            

            // Matrix
            addEntry(row,row,ap+cP);
            addEntry(row,row+1,-ae+cE);
            addEntry(row,row-1,-aw+cW);
            addEntry(row,row+Nx2,-an+cN);
            addEntry(row,row-Nx2,-as+cS);
        }
    }

    // extraneous nodes
    addEntry(0,0,1.0);
    addEntry(Nx+1,Nx+1,1.0);
    addEntry((Ny2-1)*Nx2,(Ny2-1)*Nx2,1.0);
    addEntry(Nx2*Ny2-1,Nx2*Ny2-1,1.0);

}

void VorticitySystem::BuildRHS( const MeshType& Mesh, const ScalarField& omega, const ScalarField& omega_old, const VectorField& U, const double& dt ){
    std::fill(B.begin(), B.end(), 0.0);
    double a,b,g;
    
    // south / north boundary conditions
    for ( int i = 1; i <= Nx ; i++){
    
        omega.BC.south(Mesh.xc[i],0.0,a,b,g);
        setRHS(i,0,g);

        omega.BC.north(Mesh.xc[i],0.0,a,b,g);
        setRHS(i,Ny2-1,g);
        
    }

    // east / west boundary conditions
    for ( int j = 1; j <= Ny ; j ++){

        omega.BC.east(Mesh.yc[j],0.0,a,b,g);
        setRHS(Nx2-1,j,g);

        omega.BC.west(Mesh.yc[j],0.0,a,b,g);
        setRHS(0,j,g);
    }

    // internal nodes
    for (int i = 1; i <= Nx; i++){
        for (int j = 1; j <= Ny; j++){
            double a_time = (Mesh.xf[i]-Mesh.xf[i-1]) * (Mesh.yf[j]-Mesh.yf[j-1]) / dt; // transient term
            setRHS(i, j, a_time*omega_old.get(i,j));
        }
    }

}