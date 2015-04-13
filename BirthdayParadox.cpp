#include "BirthdayParadox.h"

BirthdayParadox::BirthdayParadox(int samples=1000, std::vector<int> sizes={}) {
    this->samples = samples;
    this->sizes = sizes;
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

std::vector<int> BirthdayParadox::generateNumbers(int size) {
    std::vector<int> list;
    std::random_device rd;
    std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> di(0,365);
    for(int i{0}; i < size ; i++) {
        list.push_back(di(dre));
    } 
    return list;
}

void BirthdayParadox::simulate(BaseListener & listener) {
    for(auto it=sizes.begin(); it!=sizes.end(); ++it) {
        Work work {[&] {
            int dup{0};
            for(int i{0}; i < samples ; i++) {
                auto list = generateNumbers(*it);
                if(hasDuplicates(list)) ++dup; 
            }

            listener.update(*it, dup); 
        }};

        pool->add(work);
    } 
}
