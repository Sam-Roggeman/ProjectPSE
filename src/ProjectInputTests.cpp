//
// Created by User on 1/03/2021.
//
#include "gtest/gtest.h"
#include "Project.h"
class ProjectTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    Hub hub;
};
TEST_F (ProjectTest, Juistteruggeven){
    EXPECT_EQ(0, initializeSimulation("./test.xml",hub));

}

TEST_F(ProjectTest,foutteruggeven){
    EXPECT_EQ(1, initializeSimulation("./test1.xml",hub));
}

