#pragma once

#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include "Work.h"
#include "ThreadPool.h"
#include "GnuPlotter.h"

class BaseListener {
    public:
        virtual void update(int id, int duplicates)=0;
};

class BirthdayParadoxListener : public BaseListener {
    public:
        virtual void update(int id, int duplicates) {
            gnuplotter.add(id, duplicates); 
        }

    private:
        GnuPlotter gnuplotter;
};

class BirthdayParadox {
    public:
        BirthdayParadox(int samples, std::vector<int> sizes);
        bool hasDuplicates(std::vector<int> & birthdays);
        std::vector<int> generateNumbers(int size);
        void simulate(BaseListener & listener);
        void useThreadPool(std::shared_ptr<ThreadPool> pool);
    private:
        int samples;
        std::vector<int> sizes;
        std::shared_ptr<ThreadPool> pool;
};
