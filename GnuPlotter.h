#include <vector>

class GnuPlotter {

    public:
        void add(int x, int y);
        std::vector<int> getX();
        std::vector<int> getY();
    private:
        std::vector<int> px;
        std::vector<int> py;
};
