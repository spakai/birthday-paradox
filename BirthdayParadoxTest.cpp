#include "gmock/gmock.h" 

#include "BirthdayParadox.h"
#include <iostream>

using namespace testing;

TEST(BirthdayParadoxTest, HasDuplicates) {
    BirthdayParadox birthday(0,{23});
    std::vector<int> list_of_numbers {32,21,32,2,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(1));
}

TEST(BirthdayParadoxTest, HasNoDuplicates) {
    BirthdayParadox birthday(0,{23});
    std::vector<int> list_of_numbers {17,21,3,32,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(0));
}

TEST(BirthdayParadoxTest, CorrectNoOfNumbersGenerated) {
    BirthdayParadox birthday(0,{23});
    auto list = birthday.generateNumbers(20);
    ASSERT_THAT(list.size(), Eq(20));
}

TEST(BirthdayParadoxTest, MaxNoDoesNotExceed365) {
    BirthdayParadox birthday(0,{23});
    auto list = birthday.generateNumbers(20);
    auto it = std::max_element(list.begin(), list.end());
    ASSERT_THAT(*it, Lt(366)); 
}

TEST(BirthdayParadoxTest, AreTheNumbersReallyRandom) {
    BirthdayParadox birthday(0,{23});
    auto list1 = birthday.generateNumbers(20);
    auto list2 = birthday.generateNumbers(20);
    ASSERT_THAT(list1 == list2, Eq(0));
}

TEST(BirthdayParadoxTest, Simulate) {
    BirthdayParadox birthday(10,{10,23,30,40,50});
    BirthdayParadoxListener listener;
    birthday.simulate(listener);
    for(int i=0; i< 100000;i++) {
    for(int j=0; j< 10000;j++) {} 


    }
        
    ASSERT_THAT(listener.getSize(),Eq(5));
}
