#include <vector>
#include <fstream>

class GnuPlotter {

    public:
        void add(int x, int y);
        std::vector<int> getX();
        std::vector<int> getY();
        void writeToCsv();
        void writePlotCommands();
    private:
        std::vector<int> px;
        std::vector<int> py;
};
