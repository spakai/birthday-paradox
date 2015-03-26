#include "gmock/gmock.h" 

#include "Birthday.h"
#include <iostream>

using namespace testing;

TEST(BirthdayTest, HasDuplicates) {
    Birthday birthday(0);
    std::vector<int> list_of_numbers {32,21,32,2,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(1));
}

TEST(BirthdayTest, HasNoDuplicates) {
    Birthday birthday(0);
    std::vector<int> list_of_numbers {17,21,3,32,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(0));
}

TEST(BirthdayTest, CorrectNoOfNumbersGenerated) {
    Birthday birthday(0);
    auto list = birthday.generateNumbers(20);
    ASSERT_THAT(list.size(), Eq(20));
}

TEST(BirthdayTest, MaxNoDoesNotExceed365) {
    Birthday birthday(0);
    auto list = birthday.generateNumbers(20);
    auto it = std::max_element(list.begin(), list.end());
    ASSERT_THAT(*it, Lt(366)); 
}

TEST(BirthdayTest, AreTheNumbersReallyRandom) {
    Birthday birthday(0);
    auto list1 = birthday.generateNumbers(20);
    auto list2 = birthday.generateNumbers(20);
    int sum1 = std::accumulate(list1.begin(),list1.end(), 0);
    int sum2 = std::accumulate(list2.begin(),list2.end(), 0);
    ASSERT_FALSE(sum1==sum2);

}
