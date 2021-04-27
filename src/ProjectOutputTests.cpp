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
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/outputSimulation1.txt",
                            "./testOutput/testOutput/outputSimulation1.txt"));
    v.setCapaciteit(9000);
    v.setAantalInwoners(2000);
    o.open("./testOutput/testOutput/outputSimulation2.txt");
    s.outputSimulation( o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/outputSimulation2.txt",
                            "./testOutput/testOutput/outputSimulation2.txt"));
    o.open("./testOutput/testOutput/outputSimulation3.txt");
    s.outputSimulation( o);
    o.close();
    v.setAantalGevaccineerden(1000);
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/outputSimulation3.txt",
                            "./testOutput/testOutput/outputSimulation3.txt"));
}

TEST_F(HubOutputTest,Impressie){
    hub.addcentrum(&v);
    Simulation s = Simulation(&hub);
    std::ofstream o;
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    v.setAantalInwoners(2000);
    v.setCapaciteit(1000);
    o.open("./testOutput/testOutput/ImpressieOutput1.txt");
    s.impressie(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/ImpressieOutput1.txt",
                            "./testOutput/testFiles/ImpressieOutput1.txt"));

    VaccinType a = VaccinType();
    a.setName("a");
    std::map<std::string, VaccinType*> a2;
    a2["a"] = &a;
    v.setTypes(a2);
    v.addVaccins(1500, "a");
    v.vaccineren(0);
    o.open("./testOutput/testOutput/ImpressieOutput2.txt");
    s.impressie(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/ImpressieOutput2.txt",
                            "./testOutput/testFiles/ImpressieOutput2.txt"));

    Vaccinatiecentrum vaccinatiecentrum;
    vaccinatiecentrum.setNaamCentrum("b");
    vaccinatiecentrum.setAdresCentrum("b");
    vaccinatiecentrum.setAantalInwoners(2000);
    vaccinatiecentrum.setCapaciteit(1000);
    hub.addcentrum(&vaccinatiecentrum);
    VaccinType b = VaccinType();
    b.setName("b");
    b.sethernieuwing(1);
    b.setGereserveerd(0);
    b.setTransport(1000);
    std::map<std::string, VaccinType*> a3;
    a3["b"] = &b;
    vaccinatiecentrum.setTypes(a3);
    vaccinatiecentrum.addVaccins(1500, "b");
    vaccinatiecentrum.vaccineren(0);
    o.open("./testOutput/testOutput/ImpressieOutput3.txt");
    s.impressie(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/ImpressieOutput3.txt",
                            "./testOutput/testFiles/ImpressieOutput3.txt"));
}