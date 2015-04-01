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

TEST(ThreadPoolTest,PullWork) {
    ThreadPool pool;
    pool.add(Work{1});
    auto work = pool.pull();
    ASSERT_THAT(work.getId(), 1); 
}

TEST(ThreadPoolTest,WorkGetsPulledInSequence) {
    ThreadPool pool;
    pool.add(Work{1});
    pool.add(Work{2});
    auto work1 = pool.pull();
    auto work2 = pool.pull();
    ASSERT_THAT(work2.getId(), 2); 
}
