#include "SimulationTime.h"
#include <iostream>
#include <iomanip>
#include <fstream>

// ---- constructor ----- //
SimulationTime::SimulationTime(const std::string& filename){
    read(filename);
    disp();
    time = startTime;
    timeStep = 0;
}

// ------ member functions ------- //
void SimulationTime::read (const std::string& filename) {
    // read startTime , dt , Nt , and writeInterval from controlDict.inp
    std::ifstream infile;
    infile.open(filename);

    if (!infile) {
        std::cout << "Error opening File\n";
        exit(1);
    }

    startTime = readDouble(infile);
    dt = readDouble(infile);
    Nt = readInt(infile);
    writeInterval = readInt(infile);
}

void SimulationTime::disp() const {
    // display inputs read from controlDict.inp to the terminal
    std :: cout << "- -- Time Parameters -- -" << std :: endl ;
    std::cout << "startTime = " << startTime << std::endl;
    std::cout << "dt = " << dt << std::endl;
    std::cout << "Nt = " << Nt << std::endl;
    std::cout << "writeInterval = " << writeInterval << std::endl;
}

void SimulationTime::advance() {
    timeStep = timeStep+1;
    time = time + dt;
}

bool SimulationTime::run() const { return (timeStep < Nt);}

bool SimulationTime::writeNow() const { return (timeStep % writeInterval == 0);}
