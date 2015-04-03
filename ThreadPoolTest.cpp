#include "gmock/gmock.h" 
#include <chrono>
#include <condition_variable>
#include <mutex>

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

TEST(ThreadPoolTest,HasNoWorkAfterLastWorkIsPulled) {
    ThreadPool pool;
    pool.add(Work{});
    pool.add(Work{});
    auto work1 = pool.pull();
    auto work2 = pool.pull();
    ASSERT_THAT(pool.hasWork(), Eq(0));
}

TEST(ThreadPoolTest,HasWorkAfterOneWorkIsPulled) {
    ThreadPool pool;
    pool.add(Work{});
    pool.add(Work{});
    auto work1 = pool.pull();
    ASSERT_THAT(pool.hasWork(), Eq(1));
}

TEST(ThreadPoolTest, PullsWorkInAThread) {
    ThreadPool pool; 
    pool.start();
    std::condition_variable wasExecuted;
    bool wasWorked{0};
    std::mutex m;
    Work work{[&] {
        std::unique_lock<std::mutex> lock(m);
        wasWorked = true;
        wasExecuted.notify_all();
    }};

    pool.add(work);
    std::unique_lock<std::mutex> lock(m);
 
    ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(100), [&] { return wasWorked; }), Eq(true));      
}
