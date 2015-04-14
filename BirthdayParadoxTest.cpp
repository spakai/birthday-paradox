#include "gmock/gmock.h" 

#include "BirthdayParadox.h"
#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>

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

TEST(BirthdayParadoxTest, SimulateWithSingleThreadedPool) {

    class SingleThreadedPool : public ThreadPool {
        public:
            virtual void add(Work work) {
                work.execute();
            }
    };

    std::shared_ptr<ThreadPool> pool;
    pool = std::make_shared<SingleThreadedPool>(); 
    pool->start(0);
    BirthdayParadox birthday(10,{10,23,30,40,50});
    birthday.useThreadPool(pool);
    BirthdayParadoxListener listener;
    birthday.simulate(listener);
        
    ASSERT_THAT(listener.getSize(),Eq(5));
}

TEST(BirthdayParadoxTest, Listener) {

    class CountingListener : public BaseListener {
        public:
            void update(int id, int duplicates) override {
                std::unique_lock<std::mutex> lock(m);
                count++;
                std::cout << count << std::endl;
                wasExecuted.notify_all(); 
            }

            void waitForNotificationOrFailOnTimeout(unsigned expectedCount, int milliseconds=10000) {
                std::unique_lock<std::mutex> lock(m);
                ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(milliseconds), [&] { return count == expectedCount; }), Eq(true));      
            } 

            std::condition_variable wasExecuted;
            unsigned int count{0};
            std::mutex m;
    };

    CountingListener countingListener;
    std::shared_ptr<ThreadPool> pool;
    std::shared_ptr<std::thread> t;
    pool = std::make_shared<ThreadPool>(); 
    BirthdayParadox birthday(100000,{10,23,30,40,50});
    birthday.useThreadPool(pool);
    pool->start(4);
 
    t = std::make_shared<std::thread> (
        [&] { birthday.simulate(countingListener);} 
    );

    t->join();
    countingListener.waitForNotificationOrFailOnTimeout(5);
 
}

