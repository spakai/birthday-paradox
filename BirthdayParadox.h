#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include "Work.h"
#include "ThreadPool.h"

class BaseListener {
    public:
        virtual void update(int id, int duplicates)=0;
};

class BirthdayParadoxListener : public BaseListener {
    public:
        virtual void update(int id, int duplicates) {
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
        void simulate(BaseListener & listener);
    private:
        int samples;
        std::vector<int> sizes;
};
