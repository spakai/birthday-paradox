#include "Birthday.h"

Birthday::Birthday(int samples=1000) {
    this->samples = samples;
}

bool Birthday::hasDuplicates(std::vector<int> & birthdays) {
    std::sort(birthdays.begin(), birthdays.end());
    for(unsigned int i=1; i < birthdays.size(); i++) {
        if(birthdays.at(i) == birthdays.at(i-1)) 
            return true;
    }

    return false;
}

std::vector<int> Birthday::generateNumbers(int size) {
    std::vector<int> list;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0,365);
    for(int i{0}; i < size ; i++) {
        list.push_back(di(dre));
    } 
    return list;
}
 
