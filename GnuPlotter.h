#include <vector>

class GnuPlotter {

    public:
        void add(int x, int y);
        std::vector<int> getX();
    private:
        std::vector<int> px;
};
