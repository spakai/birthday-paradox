#include "gmock/gmock.h" 
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <set>

#include "ThreadPool.h"

using namespace testing;

class ThreadPoolTest : public Test {
    public:
        ThreadPool pool;
        std::condition_variable wasExecuted;
        std::mutex m;
        std::vector<std::shared_ptr<std::thread>> threads; 
 
        unsigned int count{0};
 
        void incrementCountAndNotify() {
            std::unique_lock<std::mutex> lock(m);
            ++count;
            wasExecuted.notify_all();
        }
       
        void waitForNotificationOrFailOnTimeout(unsigned expectedCount, int milliseconds=100) {
            std::unique_lock<std::mutex> lock(m);
            ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(milliseconds), [&] { return count == expectedCount; }), Eq(true));      
 
        } 

        void TearDown() override {
            for (auto& t: threads) t->join();
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
    pool.start(4);
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
    pool.start(4);
    unsigned int NumberOfWorkItems{3};
    Work work{[&] {
        incrementCountAndNotify();
    }};
    for(unsigned int i{0}; i < NumberOfWorkItems ; i++) {
        pool.add(work);
    } 

    waitForNotificationOrFailOnTimeout(NumberOfWorkItems);
}

TEST_F(ThreadPoolTest, DispatchMultipleClientThreads) {
    pool.start(4);
    unsigned int NumberOfWorkItems{10};
    unsigned int NumberOfThreads{10};
    Work work{[&] {
        incrementCountAndNotify();
    }};

    for(unsigned int i{0}; i < NumberOfThreads; i++) {
        threads.push_back(std::make_shared<std::thread>([&] { 
            for(unsigned int j{0}; j < NumberOfWorkItems; j++) 
                pool.add(work); 
        })); 
    }

    waitForNotificationOrFailOnTimeout(NumberOfThreads * NumberOfWorkItems);

}

TEST_F(ThreadPoolTest, MakesSureAllThreadsWorkToRetrieveFromQueue) {
    unsigned int NumberOfThreads=4;
    pool.start(NumberOfThreads);
    std::set<std::thread::id> threadIds;
    Work work{[&] {
        threadIds.insert(std::this_thread::get_id()); 
        incrementCountAndNotify();
    }};

    unsigned int NumberOfWorkItems{500};
    for(unsigned int j{0}; j < NumberOfWorkItems; j++) { 
        pool.add(work); 
    }
    waitForNotificationOrFailOnTimeout(NumberOfWorkItems);
    ASSERT_THAT(threadIds.size(),Eq(NumberOfThreads));
 
}

