#ifndef WorkControllerTest_hpp
#define WorkControllerTest_hpp

#include "oatpp-test/UnitTest.hpp"

class WorkControllerTest : public oatpp::test::UnitTest {
public:
    WorkControllerTest() : oatpp::test::UnitTest("TEST[WorkControllerTest]")
    {}

    void onRun() override;
};

#endif // WorkControllerTest_hpp
