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
    EXPECT_EQ(0, initializeSimulation("./testInput/test.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/Juist.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/Juist1.xml",hub));
}

TEST_F(ProjectTest, verkeerde_input){
    //file not found
    EXPECT_EQ(1, initializeSimulation("./testInput/abc.xml",hub));
    //verkeerde xml constructie
    EXPECT_EQ(1, initializeSimulation("./testInput/test1.xml",hub));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie.xml",hub));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie1.xml",hub));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie2.xml",hub));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie3.xml",hub));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie4.xml",hub));
    //onherkenbaar element
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar1.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar2.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar3.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar4.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar5.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar6.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar7.xml",hub));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar8.xml",hub));

    //ongeldige informatie
    EXPECT_EQ(0, initializeSimulation("./testInput/ongeldigeinfo1.xml",hub));
    EXPECT_EQ(0,initializeSimulation("./testInput/ongeldigeinfo2.xml",hub));
    EXPECT_EQ(0,initializeSimulation("./testInput/ongeldigeinfo3.xml",hub));

}
//inconsistente simulaties
TEST_F(ProjectTest,inconsistent1){
    EXPECT_EQ(1,initializeSimulation("./testInput/Inconsistentesim.xml",hub));
}
TEST_F(ProjectTest,inconsistent2){
    EXPECT_EQ(1,initializeSimulation("./testInput/Inconsistentesim1.xml",hub));
}
TEST_F(ProjectTest,inconsistent3){
    EXPECT_EQ(1,initializeSimulation("./testInput/Inconsistentesim2.xml",hub));
}
