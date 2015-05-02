#include "gmock/gmock.h" 

#include "GnuPlotter.h"
#include <thread>

using namespace testing;
class GnuPlotterTest : public Test {
    public:
        GnuPlotter gnuplotter;

};

TEST_F(GnuPlotterTest, DataIsPushedtoX) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);
    gnuplotter.add(3,8);
    gnuplotter.add(4,16);
    gnuplotter.add(5,32);
    ASSERT_THAT(gnuplotter.getX(),ElementsAre(1,2,3,4,5));
}

TEST_F(GnuPlotterTest, DataIsPushedtoY) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);

    ASSERT_THAT(gnuplotter.getY(),ElementsAre(2,4));
}

TEST_F(GnuPlotterTest, WriteInputCSV) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);
    gnuplotter.add(3,8);
    gnuplotter.add(4,16);
    gnuplotter.add(5,32);
    gnuplotter.writeToCsv();
}

TEST_F(GnuPlotterTest, WritePlotCommands) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);
    gnuplotter.add(3,8);
    gnuplotter.add(4,16);
    gnuplotter.add(5,32);
    gnuplotter.writeToCsv();
    gnuplotter.writePlotCommands();
}

TEST_F(GnuPlotterTest, UnderMultipleThreadsStress) {
    unsigned int NumberOfWorkItems{100};
    unsigned int NumberOfThreads{100};
    std::vector<std::shared_ptr<std::thread>> threads;     
    for(unsigned int i{0}; i < NumberOfThreads; i++) {
        threads.push_back(std::make_shared<std::thread>([&] { 
            for(unsigned int j{0}; j < NumberOfWorkItems; j++) 
                gnuplotter.add(i,j); 
        })); 
    }

    for (auto& t: threads) t->join();

}
