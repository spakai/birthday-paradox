#include "gmock/gmock.h" 

#include "Work.h"

using namespace testing;

TEST(WorkTest,DefaultId) {
    Work work;
    ASSERT_THAT(work.getId(), 0);
}
