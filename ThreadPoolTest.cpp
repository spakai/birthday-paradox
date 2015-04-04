#include "gmock/gmock.h" 
#include <chrono>
#include <condition_variable>
#include <mutex>

#include "ThreadPool.h"

using namespace testing;

class ThreadPoolTest : public Test {
    public:
        ThreadPool pool;
        std::condition_variable wasExecuted;
        std::mutex m;
        unsigned int count{0};
 
        void incrementCountAndNotify() {
            std::unique_lock<std::mutex> lock(m);
            ++count;
            wasExecuted.notify_all();
        }
};

TEST_F(ThreadPoolTest,PoolHasWorkAfterAdd) {
    pool.add(Work{});
    ASSERT_THAT(pool.hasWork(), Eq(1));
}

TEST_F(ThreadPoolTest,PoolHasNoWorkAfterCreation) {
    ASSERT_THAT(pool.hasWork(), Eq(0));
}

TEST_F(ThreadPoolTest,PullWork) {
    pool.add(Work{1});
    auto work = pool.pull();
    ASSERT_THAT(work.getId(), 1); 
}

TEST_F(ThreadPoolTest,WorkGetsPulledInSequence) {
    pool.add(Work{1});
    pool.add(Work{2});
    auto work1 = pool.pull();
    auto work2 = pool.pull();
    ASSERT_THAT(work2.getId(), 2); 
}

TEST_F(ThreadPoolTest,HasNoWorkAfterLastWorkIsPulled) {
    pool.add(Work{});
    pool.add(Work{});
    auto work1 = pool.pull();
    auto work2 = pool.pull();
    ASSERT_THAT(pool.hasWork(), Eq(0));
}

TEST_F(ThreadPoolTest,HasWorkAfterOneWorkIsPulled) {
    pool.add(Work{});
    pool.add(Work{});
    auto work1 = pool.pull();
    ASSERT_THAT(pool.hasWork(), Eq(1));
}

TEST_F(ThreadPoolTest, PullsWorkInAThread) {
    pool.start();
    bool wasWorked{0};
    Work work{[&] {
        std::unique_lock<std::mutex> lock(m);
        wasWorked = true;
        wasExecuted.notify_all();
    }};

    pool.add(work);
    std::unique_lock<std::mutex> lock(m);
    ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(100), [&] { return wasWorked; }), Eq(true));      
}

TEST_F(ThreadPoolTest, ExecutesMultipleWork) {
    pool.start();
    unsigned int NumberOfWorkItems{3};
    Work work{[&] {
        incrementCountAndNotify();
    }};
    for(unsigned int i{0}; i < NumberOfWorkItems ; i++) {
        pool.add(work);
    } 

    std::unique_lock<std::mutex> lock(m);
    ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(100), [&] { return count == NumberOfWorkItems; }), Eq(true));      
}
