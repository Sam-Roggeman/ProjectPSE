//============================================================================
// Name        : ProjectInputTests.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Input tests in C++, Ansi-style
//============================================================================
#include <fstream>
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
        ofs.open("/dev/null");
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    Hub hub;
    std::ofstream ofs;

};
TEST_F (ProjectTest, Juistteruggeven){
    EXPECT_EQ(0, initializeSimulation("./testInput/test.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/Juist.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/Juist1.xml", hub, ofs));
}

TEST_F(ProjectTest, verkeerde_input){
    //file not found
    EXPECT_EQ(1, initializeSimulation("./testInput/abc.xml", hub, ofs));
    //verkeerde xml constructie
    EXPECT_EQ(1, initializeSimulation("./testInput/test1.xml", hub, ofs));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie.xml", hub, ofs));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie1.xml", hub, ofs));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie2.xml", hub, ofs));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie3.xml", hub, ofs));
    EXPECT_EQ(1, initializeSimulation("./testInput/verkeerdeconstructie4.xml", hub, ofs));
    //onherkenbaar element
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar1.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar2.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar3.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar4.xml", hub, ofs));
    ASSERT_DEATH(initializeSimulation("./testInput/onherkenbaar5.xml", hub, ofs), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    ASSERT_DEATH(initializeSimulation("./testInput/onherkenbaar6.xml", hub, ofs), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar7.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/onherkenbaar8.xml", hub, ofs));

    //ongeldige informatie
    EXPECT_EQ(0, initializeSimulation("./testInput/ongeldigeinfo1.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/ongeldigeinfo2.xml", hub, ofs));
    EXPECT_EQ(0, initializeSimulation("./testInput/ongeldigeinfo3.xml", hub, ofs));

}
//inconsistente simulaties
TEST_F(ProjectTest,inconsistent1){
    ASSERT_DEATH(initializeSimulation("./testInput/Inconsistentesim.xml", hub, ofs),"Je mag maar 1 hub hebben");
}
TEST_F(ProjectTest,inconsistent2){
    ASSERT_DEATH(initializeSimulation("./testInput/Inconsistentesim1.xml", hub, ofs),"Je moet minstens 1 vaccinatiecentrum hebben");
}
TEST_F(ProjectTest,inconsistent3){
    ASSERT_DEATH(initializeSimulation("./testInput/Inconsistentesim2.xml", hub, ofs),"Je moet minstens 1 Hub hebben");
}
