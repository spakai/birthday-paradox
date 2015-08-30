#include <vector>
#include <fstream>
#include <mutex>

class GnuPlotter {

    public:
        ~GnuPlotter();
        void add(int x, int y);
        std::vector<int> getX();
        std::vector<int> getY();
        void setHeaders(const std::string & xHeader, const std::string & yHeader);
        void writeToCsv(const std::string & filename);
        void writePlotCommands(const std::string & filename);
    private:
        std::vector<int> px;
        std::vector<int> py;
        std::string xHeader;
        std::string yHeader;
};
