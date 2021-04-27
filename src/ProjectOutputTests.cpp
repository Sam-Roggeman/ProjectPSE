//============================================================================
// Name        : ProjectOutputTests.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Output tests in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "Hub.h"
#include "TicTacToeUtils.h"
#include "Simulation.h"

class HubOutputTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
    Hub hub;
    Vaccinatiecentrum v;
};

TEST_F(HubOutputTest, Fouteoutput){
    hub.addcentrum(&v);
    Simulation s = Simulation(&hub);
    std::ofstream o;
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    o.open("./testOutput/testOutput/outputSimulation1.txt");
    s.outputSimulation(o);
    EXPECT_FALSE(FileCompare("./testOutput/testFiles/outputSimulation1.txt",
                            "./testOutput/testOutput/outputSimulation2.txt"));
    o.clear();
    v.setCapaciteit(9000);
    v.setAantalInwoners(2000);
    o.open("testOutput/testOutput/outputSimulation2.txt");
    s.outputSimulation( o);
    EXPECT_FALSE(FileCompare("testOutput/testFiles/outputSimulation1.txt",
                            "testOutput/testOutput/outputSimulation2.txt"));
    o.clear();
    o.open("testOutput/testOutput/outputSimulation3.txt");
    s.outputSimulation( o);
    v.setAantalGevaccineerden(1000);
    EXPECT_FALSE(FileCompare("testOutput/testFiles/outputSimulation2.txt",
                            "testOutput/testOutput/outputSimulation3.txt"));
    o.clear();
}
TEST_F(HubOutputTest, outputSimulation){
    hub.addcentrum(&v);
    Simulation s = Simulation(&hub);
    std::ofstream o;
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    o.open("./testOutput/testOutput/outputSimulation1.txt");
    s.outputSimulation(o);
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/outputSimulation1.txt",
                            "./testOutput/testOutput/outputSimulation1.txt"));
    o.clear();
    v.setCapaciteit(9000);
    v.setAantalInwoners(2000);
    o.open("testOutput/testOutput/outputSimulation2.txt");
    s.outputSimulation( o);
    EXPECT_TRUE(FileCompare("testOutput/testFiles/outputSimulation2.txt",
                            "testOutput/testOutput/outputSimulation2.txt"));
    o.clear();
    o.open("testOutput/testOutput/outputSimulation3.txt");
    s.outputSimulation( o);
    v.setAantalGevaccineerden(1000);
    EXPECT_TRUE(FileCompare("testOutput/testFiles/outputSimulation3.txt",
                            "testOutput/testOutput/outputSimulation3.txt"));
    o.clear();
}