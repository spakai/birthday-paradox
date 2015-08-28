#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include <set>
#include "Work.h"
#include "ThreadPool.h"
#include "Listener.h"

class BirthdayParadox {
    public:
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int popSize);
        void simulate(int samples, std::vector<int> popList, BaseListener & listener);
        void useThreadPool(std::shared_ptr<ThreadPool> pool);
    private:
        std::shared_ptr<ThreadPool> pool;
};
