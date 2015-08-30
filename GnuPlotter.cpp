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

void GnuPlotter::setHeaders(const std::string & xHeader, const std::string & yHeader) {
    this->xHeader = xHeader;
    this->yHeader = yHeader;
}

void GnuPlotter::writeToCsv(const std::string & filename) {
    std::ofstream outputFile(filename);
    outputFile << xHeader << "," << yHeader << std::endl; 
    unsigned int size = px.size();
    for(unsigned int i=0 ; i < size ; i++) {
        outputFile << px.at(i) << "," << py.at(i) << std::endl; 
    }
}

void GnuPlotter::writePlotCommands(const std::string & filename) {
    std::ofstream outputFile(filename);
    outputFile << "set datafile separator \",\"" << std::endl;
    outputFile << "set xlabel " << "\"" << xHeader << "\"" << std::endl;
    outputFile << "set ylabel " << "\"" << yHeader << "\"" << std::endl;
    outputFile << "plot \"output.csv\" using 1:2 with lines" << std::endl;
    outputFile << "pause -1 \"Hit any key to continue\"" << std::endl;
}

GnuPlotter::~GnuPlotter() {
    writeToCsv("output.csv");
    writePlotCommands("plot.gp");
}