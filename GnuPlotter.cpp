#include "GnuPlotter.h"

void GnuPlotter::add(int x, int y) {
    px.push_back(x);
}

std::vector<int> GnuPlotter::getX() {
    return px;
} 
