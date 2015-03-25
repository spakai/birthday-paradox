#include "Birthday.h"

Birthday::Birthday(int samples=1000) {
    this->samples = samples;
}

bool Birthday::has_duplicates(std::vector<int> & birthdays) {
    std::sort(birthdays.begin(), birthdays.end());
    for(unsigned int i=1; i < birthdays.size(); i++) {
        if(birthdays.at(i) == birthdays.at(i-1)) 
            return true;
    }

    return false;
}
