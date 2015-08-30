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
        bool hasDuplicates(const std::vector<int> & birthdays);
        std::vector<int> generateNumbers(const int popSize);
        void simulate(const int samples, const std::vector<int> & popList, BaseListener & listener);
        void useThreadPool(std::shared_ptr<ThreadPool> pool);
    private:
        std::shared_ptr<ThreadPool> pool;
};
