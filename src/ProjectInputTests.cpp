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
#include "Simulation.h"
#include "Hub.h"
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
    Simulation s = Simulation(&hub);

    EXPECT_EQ(0, s.initializeSimulation("./testInput/test.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/Juist.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/Juist1.xml",  ofs));
}

TEST_F(ProjectTest, verkeerde_input){
    Simulation s = Simulation(&hub);

    //file not found
    EXPECT_EQ(1, s.initializeSimulation("./testInput/abc.xml",  ofs));
    //verkeerde xml constructie
    EXPECT_EQ(1, s.initializeSimulation("./testInput/test1.xml",  ofs));
    EXPECT_EQ(1, s.initializeSimulation("./testInput/verkeerdeconstructie.xml",  ofs));
    EXPECT_EQ(1, s.initializeSimulation("./testInput/verkeerdeconstructie1.xml",  ofs));
    EXPECT_EQ(1, s.initializeSimulation("./testInput/verkeerdeconstructie2.xml",  ofs));
    EXPECT_EQ(1, s.initializeSimulation("./testInput/verkeerdeconstructie3.xml",  ofs));
    EXPECT_EQ(1, s.initializeSimulation("./testInput/verkeerdeconstructie4.xml",  ofs));
    //onherkenbaar element
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar1.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar2.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar3.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar4.xml",  ofs));
    ASSERT_DEATH(s.initializeSimulation("./testInput/onherkenbaar5.xml",  ofs), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    ASSERT_DEATH(s.initializeSimulation("./testInput/onherkenbaar6.xml",  ofs), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar7.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/onherkenbaar8.xml",  ofs));

    //ongeldige informatie
    EXPECT_EQ(0, s.initializeSimulation("./testInput/ongeldigeinfo1.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/ongeldigeinfo2.xml",  ofs));
    EXPECT_EQ(0, s.initializeSimulation("./testInput/ongeldigeinfo3.xml",  ofs));

}
//inconsistente simulaties
TEST_F(ProjectTest,inconsistent1){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(s.initializeSimulation("./testInput/Inconsistentesim.xml",  ofs),"Je mag maar 1 hub hebben");
}
TEST_F(ProjectTest,inconsistent2){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(s.initializeSimulation("./testInput/Inconsistentesim1.xml",  ofs),"Je moet minstens 1 vaccinatiecentrum hebben");
}
TEST_F(ProjectTest,inconsistent3){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(s.initializeSimulation("./testInput/Inconsistentesim2.xml",  ofs),"Je moet minstens 1 Hub hebben");
}
