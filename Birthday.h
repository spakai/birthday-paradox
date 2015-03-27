#include <algorithm>
#include <random>
#include <vector>

class Birthday {
    public:
        Birthday(int samples);
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int size);
        int simulate(int size);
    private:
        int samples;
};
