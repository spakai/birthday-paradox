#include "BirthdayParadox.h"
#include <iostream>

void BirthdayParadox::useThreadPool(std::shared_ptr<ThreadPool> pool) {
    this->pool = pool;
}
 
bool BirthdayParadox::hasDuplicates(std::vector<int> & birthdays) {
    std::set<int> uniqueBirthdays(birthdays.begin(), birthdays.end());
    return (uniqueBirthdays.size() != birthdays.size());
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

void BirthdayParadox::simulate(const int samples, std::vector<int> popList, BaseListener & listener) {
    for(auto it=popList.begin(); it!=popList.end(); ++it) {
        int id = *it;
        Work work {[&, id,samples] {
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
