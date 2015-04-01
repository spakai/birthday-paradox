#include "gmock/gmock.h" 

#include "ThreadPool.h"

using namespace testing;

TEST(ThreadPoolTest,PoolHasWorkAfterAdd) {
    ThreadPool pool;
    pool.add(Work{});
    ASSERT_THAT(pool.hasWork(), Eq(1));
}

TEST(ThreadPoolTest,PoolHasNoWorkAfterCreation) {
    ThreadPool pool;
    ASSERT_THAT(pool.hasWork(), Eq(0));
}
