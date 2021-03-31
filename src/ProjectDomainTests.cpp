//============================================================================
// Name        : ProjectDomainTests.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : tests domain functions in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "Project.h"
#include "Hub.h"
#include "Simulation.h"
#include "simulationImporter.h"

class HubDomainTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
        ofs.open("/dev/null");
        hub.addcentrum(&v);
        hub2.addcentrum(&vac);
    }

    virtual void TearDown() {
    }

    Hub hub;
    Vaccinatiecentrum v;
    Hub hub2;
    Vaccinatiecentrum vac;
    std::ofstream  ofs;
};

/**
Tests the default constructor.
*/
TEST_F(HubDomainTest, HubDefaultConstructor) {
    EXPECT_TRUE(hub.correctlyInitialized());
    // verify post-condition
    EXPECT_EQ(0, hub.getInterval());
    EXPECT_EQ(0, hub.getAantalVaccins());
    EXPECT_EQ(0, hub.getTransport());
    EXPECT_EQ(0, hub.getLevering());

    //Initialisering waardes
    hub.setLevering(500);
    hub.setInterval(6);
    hub.setTransport(50);
    hub.leveringToHub();

    //Testen voor de gelijkheid
    EXPECT_EQ(500,hub.getLevering());
    EXPECT_EQ(500,hub.getAantalVaccins());
    EXPECT_EQ(50,hub.getTransport());
    EXPECT_EQ(6,hub.getInterval());

    //Testen voor de niet gelijkheid
    EXPECT_NE(50,hub.getLevering());
    EXPECT_NE(500,hub.getTransport());
    EXPECT_NE(5,hub.getInterval());
    EXPECT_NE(1203,hub.getAantalVaccins());
}

//Tests voor de Vaccinatiecentra constructor
TEST_F(HubDomainTest, CentrumDefaultConstructor ){
    EXPECT_TRUE(v.correctlyInitialized());
    EXPECT_EQ("", v.getNaamCentrum());
    EXPECT_EQ("", v.getAdresCentrum());
    EXPECT_EQ(0, v.getAantalGevaccineerden());
    EXPECT_EQ(0, v.getAantalVaccins());
    EXPECT_EQ(0, v.getAantalInwoners());
    EXPECT_EQ(0, v.getCapaciteit());

    //Initialisering waardes
    v.setCapaciteit(1500);
    v.setNaamCentrum("Antwerpen");
    v.setAdresCentrum("vijfstraat 5");
    v.setAantalInwoners(500);
    v.setAantalVaccins(1300);
    v.setAantalGevaccineerden(1240);

    //Gelijkheid testen
    EXPECT_EQ(1500,v.getCapaciteit());
    EXPECT_EQ("Antwerpen",v.getNaamCentrum());
    EXPECT_EQ("vijfstraat 5", v.getAdresCentrum());
    EXPECT_EQ(500,v.getAantalInwoners());
    EXPECT_EQ(1300,v.getAantalVaccins());
    EXPECT_EQ(1240,v.getAantalGevaccineerden());
}


//Tests voor de functie SubstractVaccins
TEST_F(HubDomainTest, substractVaccins) {
    //Initialisering waardes
    hub2.setLevering(1000);
    hub2.leveringToHub();

    //Substract op de hub uitvoeren
    hub2.substractVaccins(0);

    //Gelijkheid checken
    EXPECT_EQ(1000,hub2.getAantalVaccins());

    //Substract op de hub uitvoeren
    hub2.substractVaccins(1000);

    //Gelijkheid checken
    EXPECT_EQ(0,hub2.getAantalVaccins());

    //Initialisering waardes
    hub2.leveringToHub();
    hub2.leveringToHub();

    //Achtereenvolgens de substract uitvoeren en de gelijkheid bekijken
    hub2.substractVaccins(1000);
    EXPECT_EQ(1000,hub2.getAantalVaccins());
    hub2.substractVaccins(500);
    EXPECT_EQ(500,hub2.getAantalVaccins());
    EXPECT_NE(2412,hub2.getAantalVaccins());
    hub2.substractVaccins(250);
    EXPECT_NE(0,hub2.getAantalVaccins());
    EXPECT_EQ(250,hub2.getAantalVaccins());
    hub2.substractVaccins(250);
    EXPECT_EQ(0,hub2.getAantalVaccins());
}

//Tests voor de functie isLeveringsDag
TEST_F(HubDomainTest, isLeveringsDag){
    //Initialisering waardes
    hub2.setInterval(1);
    hub.setInterval(6);

    //Kijken of de functie een True of False teruggeeft
    EXPECT_TRUE(hub2.isLeveringsDag(2));
    EXPECT_FALSE(hub2.isLeveringsDag(3));
    EXPECT_TRUE(hub.isLeveringsDag(7));
    EXPECT_FALSE(hub.isLeveringsDag(5));
    hub2.setInterval(0);

    //Loopen en steeds de return waarde van de functie checken
    //Deze zou altijd false moeten teruggeven
    while(hub2.getInterval() != 6){
        EXPECT_FALSE(hub.isLeveringsDag(8));
        hub2.setInterval(hub2.getInterval()+ 1);
    }

    //Waarde initaliseren en vervolgens de return waarde van de functie bekijken
    hub2.setInterval(hub2.getInterval()+1);
    EXPECT_TRUE(hub2.isLeveringsDag(8));
}

//Tests voor de functie notDone
TEST_F(HubDomainTest, notDone){
    //Initialisering alle waardes
    vac.setAantalInwoners(1000);
    vac.setCapaciteit(1000);

    //Testen op de return waarde van de functie
    EXPECT_TRUE(hub2.notDone());
    EXPECT_FALSE(hub.notDone());

    //Initalisering van alle waardes
    vac.setAantalVaccins(1000);
    vac.vaccineren(ofs);

    //Testen op de return waarde van de functie
    EXPECT_FALSE(hub2.notDone());
    EXPECT_FALSE(hub.notDone());
}

//Tests voor de functie aantalOngevaccineerden
TEST_F(HubDomainTest, aantalOngevaccineerden){
    //Initialisering alle waardes
    vac.setAantalInwoners(1000);
    vac.setCapaciteit(1000);
    hub2.vaccineren(ofs);

    //Testen op de return waarde van de functie
    EXPECT_EQ(0, hub.aantalOngevaccineerden());
    EXPECT_EQ(1000,hub2.aantalOngevaccineerden());
}

//Tests voor de functie addGevaccineerden
TEST_F(HubDomainTest, addGevaccineerden){

    //We voeren hier de functie uit
    vac.addGevaccineerden(500);

    //We bekijken de waardes van het aantalgevaccineerden
    EXPECT_EQ(500,vac.getAantalGevaccineerden());
    EXPECT_EQ(0,v.getAantalGevaccineerden());
    EXPECT_NE(0,vac.getAantalGevaccineerden());
    EXPECT_NE(500,v.getAantalGevaccineerden());

    //We voeren de functie weer 2 keer uit en kijken weer naar de output van getaantalgevaccineerden
    v.addGevaccineerden(5400);
    EXPECT_EQ(5400,v.getAantalGevaccineerden());
    vac.addGevaccineerden(1500);
    EXPECT_EQ(2000,vac.getAantalGevaccineerden());
}

//Tests voor de functie addVaccins
TEST_F(HubDomainTest, addVaccins){
    //Initialisering alle waardes
    v.addVaccins(500);
    v.setAantalInwoners(1500);
    v.setCapaciteit(500);

    //Returnwaarde vergelijken met verwachtte waarde
    EXPECT_EQ(500,v.getAantalVaccins());
    EXPECT_NE(0,v.getAantalVaccins());
    v.vaccineren(ofs);
    EXPECT_EQ(0,v.getAantalVaccins());
    EXPECT_NE(500,v.getAantalVaccins());
}

//Tests voor de functie clear
TEST_F(HubDomainTest, clear){
    Simulation s = Simulation(&hub);
    //Initialisering alle waardes
    simulationImporter::importSimulation("./testInput/test.xml", ofs,s);
    EXPECT_EQ(0,s.getDag());
    EXPECT_EQ(93000,s.getHub()->getAantalVaccins());
    EXPECT_EQ(2000,s.getHub()->getTransport());
    EXPECT_EQ(6,s.getHub()->getInterval());
    s.clear();
    EXPECT_EQ(0,s.getDag());
    EXPECT_EQ(0,s.getHub()->getAantalVaccins());
    EXPECT_EQ(0,s.getHub()->getTransport());
    EXPECT_EQ(0,s.getHub()->getInterval());



}
