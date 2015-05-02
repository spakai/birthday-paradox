#include "GnuPlotter.h"

void GnuPlotter::add(int x, int y) {
    std::lock_guard<std::mutex> lock(m);
    px.push_back(x);
    py.push_back(y);
}

std::vector<int> GnuPlotter::getX() {
    return px;
}

std::vector<int> GnuPlotter::getY() {
    return py;
}

void GnuPlotter::writeToCsv() {
    std::ofstream outputFile("output.csv"); 
    unsigned int size = px.size();
    for(unsigned int i=0 ; i < size ; i++) {
        outputFile << px.at(i) << "," << py.at(i) << std::endl; 
    }
}

void GnuPlotter::writePlotCommands() {
    std::ofstream outputFile("plot.gp");
    outputFile << "set datafile separator \",\"" << std::endl;
    outputFile << "plot \"output.csv\" using 1:2 with lines" << std::endl;
    
}

GnuPlotter::~GnuPlotter() {
    writeToCsv();
    writePlotCommands();
}
