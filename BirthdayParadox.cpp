#include "BirthdayParadox.h"
#include <iostream>
BirthdayParadox::BirthdayParadox(int samples=1000, std::vector<int> popList={}) {
    this->samples = samples;
    this->popList = popList;
}

void BirthdayParadox::useThreadPool(std::shared_ptr<ThreadPool> pool) {
    this->pool = pool;
}
 
bool BirthdayParadox::hasDuplicates(std::vector<int> & birthdays) {
    std::sort(birthdays.begin(), birthdays.end());
    unsigned int size = birthdays.size();
    for(unsigned int i{1}; i < size; i++) {
        if(birthdays.at(i) == birthdays.at(i-1)) 
            return true;
    }

    return false;
}

std::vector<int> BirthdayParadox::generateNumbers(int popSize) {
    std::vector<int> list;
    std::random_device rd;
    std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> di(0,365);
    for(int i{0}; i < popSize ; i++) {
        list.push_back(di(dre));
    } 
    return list;
}

void BirthdayParadox::simulate(BaseListener & listener) {
    for(auto it=popList.begin(); it!=popList.end(); ++it) {
        int id = *it;
        Work work {[&, id] {
            int dup{0};
            for(int i{0}; i < samples ; i++) {
                auto list = generateNumbers(id);
                if(hasDuplicates(list)) ++dup; 
            }

            listener.update(id, dup); 
        }};

        pool->add(work);
    } 
}
