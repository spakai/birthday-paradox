#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include "Work.h"

class BirthdayParadoxListener {
    public:
        void update(int id, int duplicates) {
            results.emplace(id,duplicates);            
        }

        int getSize() const {
            return results.size();
        }
    private:
        std::map<int, int> results;
};

class BirthdayParadox {
    public:
        BirthdayParadox(int samples, std::vector<int> sizes);
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int size);
        void simulate(BirthdayParadoxListener & listener);
    private:
        int samples;
        std::vector<int> sizes;
};
