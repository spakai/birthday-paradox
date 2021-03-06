#include "gmock/gmock.h" 
#include "BirthdayParadox.h"
#include <chrono>
#include <condition_variable>
#include <mutex>

using namespace testing;

class BirthdayParadoxTest : public Test {
    public:
        BirthdayParadox birthday;
};

TEST_F(BirthdayParadoxTest, HasDuplicates) {
    std::vector<int> list_of_numbers {32,21,32,2,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(true));
}

TEST_F(BirthdayParadoxTest, HasNoDuplicates) {
    std::vector<int> list_of_numbers {17,21,3,32,4};
    ASSERT_THAT(birthday.hasDuplicates(list_of_numbers),Eq(false));
}

TEST_F(BirthdayParadoxTest, CorrectNoOfNumbersGenerated) {
    auto list = birthday.generateNumbers(20);
    ASSERT_THAT(list.size(), Eq(20));
}

TEST_F(BirthdayParadoxTest, MaxNoDoesNotExceed365) {
    auto list = birthday.generateNumbers(20);
    auto it = std::max_element(list.begin(), list.end());
    ASSERT_THAT(*it, Lt(366)); 
}

TEST_F(BirthdayParadoxTest, AreTheNumbersReallyRandom) {
    auto list1 = birthday.generateNumbers(20);
    auto list2 = birthday.generateNumbers(20);
    ASSERT_THAT(list1 == list2, Eq(0));
}

TEST_F(BirthdayParadoxTest, SimulateWithSingleThreadedPool) {

    class SingleThreadedPool : public ThreadPool {
        public:
            virtual void add(Work work) {
                work.execute();
            }
    };

    class TestListener : public BaseListener {
        public:
            virtual void update(int id, int duplicates) {
                results.emplace(id,duplicates);            
            }

            int getSize() const {
                return results.size();
            }
        private:
            std::map<int, int> results;
    }; 

    std::shared_ptr<ThreadPool> pool;
    pool = std::make_shared<SingleThreadedPool>(); 
    pool->start(0);
    birthday.useThreadPool(pool);
    TestListener listener;
    birthday.simulate(1000, {10,23,30,40,50},listener);
        
    ASSERT_THAT(listener.getSize(),Eq(5));
}

TEST_F(BirthdayParadoxTest, Listener) {

    class CountingListener : public BaseListener {
        public:
            void update(int id, int duplicates) override {
                std::unique_lock<std::mutex> lock(m);
                count=count+duplicates;
                wasExecuted.notify_all(); 
            }

            void waitForNotificationOrFailOnTimeout(unsigned expectedCount, int milliseconds=20000) {
                std::unique_lock<std::mutex> lock(m);
                ASSERT_THAT(wasExecuted.wait_for(lock, std::chrono::milliseconds(milliseconds), [&] { return count == expectedCount; }), Eq(true));      
            } 

            std::initializer_list<int> getIdList() const {
                std::initializer_list<int> initList{365,400,450,500,550,650,700};
                return initList;
            }

            std::condition_variable wasExecuted;
            unsigned int count{0};
            std::mutex m;
    };

    CountingListener countingListener;
    std::shared_ptr<ThreadPool> pool;
    std::shared_ptr<std::thread> t;
    pool = std::make_shared<ThreadPool>(); 
    birthday.useThreadPool(pool);
    pool->start(4);
 
    t = std::make_shared<std::thread> (
        [&] { birthday.simulate(1000, countingListener.getIdList(), countingListener);} 
    );

    t->join();
    countingListener.waitForNotificationOrFailOnTimeout(7000);
}
