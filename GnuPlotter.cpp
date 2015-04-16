#include "GnuPlotter.h"

void GnuPlotter::add(int x, int y) {
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
