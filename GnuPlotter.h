#include <vector>
#include <fstream>
#include <mutex>

class GnuPlotter {

    public:
        ~GnuPlotter();
        void add(int x, int y);
        std::vector<int> getX();
        std::vector<int> getY();
        void writeToCsv();
        void writePlotCommands();
    private:
        std::vector<int> px;
        std::vector<int> py;
        std::mutex m;
};
