#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>

class BirthdayParadox {
    public:
        BirthdayParadox(int samples, std::vector<int> sizes);
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int size);
        std::map<int, int> simulate();
    private:
        int samples;
        std::vector<int> sizes;
};
