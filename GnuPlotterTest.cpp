#include "gmock/gmock.h" 

#include "GnuPlotter.h"

using namespace testing;
class GnuPlotterTest : public Test {
    public:
        GnuPlotter gnuplotter;

};

TEST_F(GnuPlotterTest, DataIsPushedtoX) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);
    ASSERT_THAT(gnuplotter.getX(),ElementsAre(1,2));
}

TEST_F(GnuPlotterTest, DataIsPushedtoY) {
    gnuplotter.add(1,2);
    gnuplotter.add(2,4);

    ASSERT_THAT(gnuplotter.getY(),ElementsAre(2,4));
}
