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
