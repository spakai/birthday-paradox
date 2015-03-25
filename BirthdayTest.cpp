#include "gmock/gmock.h" 

#include "Birthday.h"

using namespace testing;

TEST(BirthdayTest, HasDuplicates) {
    Birthday birthday(1000);
    std::vector<int> list_of_numbers {32,21,32,2,4};
    ASSERT_THAT(birthday.has_duplicates(list_of_numbers),Eq(1));
}

TEST(BirthdayTest, HasNoDuplicates) {
    Birthday birthday(1000);
    std::vector<int> list_of_numbers {17,21,3,32,4};
    ASSERT_THAT(birthday.has_duplicates(list_of_numbers),Eq(0));
}
