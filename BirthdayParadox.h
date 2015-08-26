#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include <set>
#include "Work.h"
#include "ThreadPool.h"
#include "GnuPlotter.h"

class BaseListener {
    public:
        virtual void update(int popSize, int duplicates)=0;
};

class BirthdayParadoxListener : public BaseListener {
    public:
        virtual void update(int popSize, int duplicates) {
            gnuplotter.add(popSize, duplicates); 
        }

    private:
        GnuPlotter gnuplotter;
};

class BirthdayParadox {
    public:
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int popSize);
        void simulate(int samples, std::vector<int> popList, BaseListener & listener);
        void useThreadPool(std::shared_ptr<ThreadPool> pool);
    private:
        int samples;
        std::vector<int> popList;
        std::shared_ptr<ThreadPool> pool;
};
