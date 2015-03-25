#include <algorithm>
#include <random>
#include <vector>

class Birthday {
    public:
        Birthday(int samples);
        bool has_duplicates(std::vector<int> & birthdays);
    private:
        int samples;
};
