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
#include "simulationImporter.h"

class HubOutputTest: public ::testing::Test {
protected:

    friend class Hub;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
    Hub* hub = new Hub(1);
    Vaccinatiecentrum v;
};

TEST_F(HubOutputTest, Fouteoutput){
    hub->addcentrum(&v);
    Simulation s = Simulation();
    s.addHub(hub);
    std::ofstream o;
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    o.open("./testOutput/testOutput/outputSimulation1.txt");
    s.outputSimulation(o);
    EXPECT_FALSE(FileCompare("./testOutput/testFiles/outputSimulation1.txt",
                            "./testOutput/testOutput/outputSimulation2.txt"));
    o.close();
    o.clear();
    v.setCapaciteit(9000);
    v.setAantalInwoners(2000);
    o.open("testOutput/testOutput/outputSimulation2.txt");
    s.outputSimulation( o);
    EXPECT_FALSE(FileCompare("testOutput/testFiles/outputSimulation1.txt",
                            "testOutput/testOutput/outputSimulation2.txt"));
    o.close();
    o.clear();
    o.open("testOutput/testOutput/outputSimulation3.txt");
    s.outputSimulation( o);
    v.setAantalGevaccineerden(1000);
    EXPECT_TRUE(FileCompare("testOutput/testFiles/outputSimulation2.txt",
                            "testOutput/testOutput/outputSimulation3.txt"));
    o.close();
    o.clear();
}
TEST_F(HubOutputTest, outputSimulation){
    hub->addcentrum(&v);
    Simulation s = Simulation();
    s.addHub(hub);
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
    hub->addcentrum(&v);
    Simulation s = Simulation();
    s.addHub(hub);
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
    v.vaccineren(0,o);
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
    hub->addcentrum(&vaccinatiecentrum);
    VaccinType b = VaccinType();
    b.setName("b");
    b.sethernieuwing(1);
    b.setGereserveerd(0);
    b.setTransport(1000);
    std::map<std::string, VaccinType*> a3;
    a3["b"] = &b;
    vaccinatiecentrum.setTypes(a3);
    vaccinatiecentrum.addVaccins(1500, "b");
    vaccinatiecentrum.vaccineren(0,o);
    o.open("./testOutput/testOutput/ImpressieOutput3.txt");
    s.impressie(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/ImpressieOutput3.txt",
                            "./testOutput/testFiles/ImpressieOutput3.txt"));
}

TEST_F(HubOutputTest,Autosimulation){
    std::ofstream o;
    Hub* h = new Hub(0);
    Simulation s = Simulation();
    s.addHub(h);
    simulationImporter::importSimulation("./testInput/t2.xml",  o, s);
    o.open("./testOutput/testOutput/Autosim1.txt");
    s.autoSimulationUntilDone(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/Autosim1.txt",
                            "./testOutput/testFiles/Autosim1.txt"));
    EXPECT_FALSE(FileCompare("./testOutput/testOutput/Autosim1.txt",
                            "./testOutput/testFiles/ImpressieOutput3.txt"));

    o.clear();
    Simulation s2 = Simulation();
    s2.addHub(h);
    simulationImporter::importSimulation("./testInput/t.xml",  o, s2);
    o.open("./testOutput/testOutput/Autosim2.txt");
    s2.autoSimulationUntilDone(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/Autosim2.txt",
                            "./testOutput/testFiles/Autosim2.txt"));
    EXPECT_FALSE(FileCompare("./testOutput/testOutput/Autosim2.txt",
                             "./testOutput/testFiles/ImpressieOutput3.txt"));

    o.clear();
    Simulation s3 = Simulation();
    s3.addHub(h);
    simulationImporter::importSimulation("./testInput/t3.xml",  o, s3);
    o.open("./testOutput/testOutput/Autosim3.txt");
    s.autoSimulationUntilDone(o);
    o.close();
    EXPECT_TRUE(FileCompare("./testOutput/testOutput/Autosim3.txt",
                            "./testOutput/testFiles/Autosim3.txt"));
    EXPECT_FALSE(FileCompare("./testOutput/testOutput/Autosim3.txt",
                             "./testOutput/testFiles/ImpressieOutput3.txt"));
}

TEST_F(HubOutputTest,GraphicIntegration){
    std::ofstream o;
    Hub* h = new Hub(0);
    Simulation s = Simulation();
    s.addHub(h);
    simulationImporter::importSimulation("./testInput/t2.xml",  o, s);
    s.autoSimulation(0,1,o);
    srand(0);
    s.graphicIntegration("./src/engine", "./testOutput/testOutput/", "0GraphicIntegration");
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/0GraphicIntegration.ini",
                            "./testOutput/testOutput/0GraphicIntegration.ini"));
    s.autoSimulation(1,2,o);
    srand(0);
    s.graphicIntegration("./src/engine", "./testOutput/testOutput/", "1GraphicIntegration");
    EXPECT_FALSE(FileCompare("./testOutput/testFiles/0GraphicIntegration.ini",
                             "./testOutput/testOutput/1GraphicIntegration.ini"));
    s.autoSimulation(2,3,o);
    EXPECT_TRUE(FileCompare("./testOutput/testFiles/1GraphicIntegration.ini",
                            "./testOutput/testOutput/1GraphicIntegration.ini"));
    s.autoSimulation(3,4,o);
    EXPECT_FALSE(FileCompare("./testOutput/testFiles/1GraphicIntegration.ini",
                             "./testOutput/testOutput/0GraphicIntegration.ini"));
}