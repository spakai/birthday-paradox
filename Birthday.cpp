#include "Birthday.h"

Birthday::Birthday(int samples=1000) {
    this->samples = samples;
}

bool Birthday::hasDuplicates(std::vector<int> & birthdays) {
    std::sort(birthdays.begin(), birthdays.end());
    unsigned int size = birthdays.size();
    for(unsigned int i{1}; i < size; i++) {
        if(birthdays.at(i) == birthdays.at(i-1)) 
            return true;
    }

    return false;
}

std::vector<int> Birthday::generateNumbers(int size) {
    std::vector<int> list;
    std::random_device rd;
    std::default_random_engine dre(rd());
    std::uniform_int_distribution<int> di(0,365);
    for(int i{0}; i < size ; i++) {
        list.push_back(di(dre));
    } 
    return list;
}

int Birthday::simulate(int size) {
    int dup{0};
    for(int i{0}; i < samples ; i++) {
        auto list = generateNumbers(size);
        if(hasDuplicates(list)) { 
            ++dup; 
        }
    } 
    return dup;
}
