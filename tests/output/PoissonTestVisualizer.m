clear; clc; close all;

%% --- USER INPUT ---
Nx = 64;          % must match simulation
Ny = 64;
Lx = 1.0;            % change per case
Ly = 1.0;

%% --- Load data ---
psi_full = load('psi_0.000000.dat');

Nx2 = Nx + 2;
Ny2 = Ny + 2;

% reshape (C++ is column-major flattened as i + j*Nx2)
psi_full = reshape(psi_full, [Nx2, Ny2])';

% only plot interior points
psi_plot = psi_full(2:end-1, 2:end-1);
%% --- Create mesh ---
xc = load('x.dat');
yc = load('y.dat');
x = xc(2:end-1);
y = yc(2:end-1);

[X,Y] = meshgrid(x,y);

%% --- Create Concentration Plot --
%% 3-D Plot
figure;
surf(X, Y, psi_plot);   
shading interp;
colorbar;

xlabel('x');
ylabel('y');
zlabel('psi');

title('Values of psi');

%% Omega plot
%% Parameters
Lx = max(xc) - min(xc);
x0 = 0.5*(min(xc)+max(xc));
y0 = 0.5*(min(yc)+max(yc));
sigma = 0.1*Lx;

%% Analytical Gaussian
omega = exp(-((X-x0).^2 + (Y-y0).^2)/sigma^2);

%% Plot
figure
surf(X,Y,omega)
shading interp;
colorbar
axis equal tight

xlabel('x')
ylabel('y')
title('Analytical Gaussian Blob')