//============================================================================
// Name        : ProjectInputTests.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Input tests in C++, Ansi-style
//============================================================================
#include <fstream>
#include "gtest/gtest.h"
#include "Simulation.h"
#include "Hub.h"
#include "simulationImporter.h"

class ProjectTest: public ::testing::Test {
protected:
    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    ProjectTest() {}

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
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/test.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/Juist.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/Juist1.xml",  ofs, s));
}

TEST_F(ProjectTest, verkeerde_input){
    Simulation s = Simulation(&hub);
    //file not found
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/abc.xml",  ofs, s));
    s.clear();
    //verkeerde xml constructie
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/test1.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie1.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie2.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie3.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie4.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(1, simulationImporter::importSimulation("./testInput/verkeerdeconstructie5.xml",  ofs, s));
    s.clear();
    //onherkenbaar element
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar1.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar2.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar3.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar4.xml",  ofs, s));
    s.clear();
    EXPECT_DEATH(simulationImporter::importSimulation("./testInput/onherkenbaar5.xml",  ofs, s),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    s.clear();
    EXPECT_DEATH(simulationImporter::importSimulation("./testInput/onherkenbaar6.xml",  ofs, s),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    s.clear();
    EXPECT_DEATH( simulationImporter::importSimulation("./testInput/onherkenbaar7.xml",  ofs, s),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    s.clear();
    EXPECT_DEATH(simulationImporter::importSimulation("./testInput/onherkenbaar8.xml",  ofs, s),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar9.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar10.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/onherkenbaar11.xml",  ofs, s));
    s.clear();
    //ongeldige informatie
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/ongeldigeinfo1.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/ongeldigeinfo2.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/ongeldigeinfo3.xml",  ofs, s));
    s.clear();
    EXPECT_EQ(0, simulationImporter::importSimulation("./testInput/ongeldigeinfo4.xml",  ofs, s));
}
//inconsistente simulaties
TEST_F(ProjectTest,inconsistent1){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(simulationImporter::importSimulation("./testInput/Inconsistentesim.xml",  ofs, s),"Er bestaat al een vaccintype met dezelfde naam");
}
TEST_F(ProjectTest,inconsistent2){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(simulationImporter::importSimulation("./testInput/Inconsistentesim1.xml",  ofs, s),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
}
TEST_F(ProjectTest,inconsistent3){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(simulationImporter::importSimulation("./testInput/Inconsistentesim2.xml",  ofs, s),"Je moet minstens 1 Hub hebben");
}
TEST_F(ProjectTest,inconsistent4){
    Simulation s = Simulation(&hub);

    ASSERT_DEATH(simulationImporter::importSimulation("./testInput/Inconsistentesim3.xml",ofs,s),"Je moet minstens 1 vaccintype hebben");
}