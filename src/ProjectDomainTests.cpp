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
#include "Hub.h"
#include "Simulation.h"
#include "simulationImporter.h"

class HubDomainTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
        ofs.open("/dev/null");
        vac.setNaamCentrum("vac");
        hub.addcentrum(&v);
    }

    virtual void TearDown() {
    }

    Hub hub;
    Vaccinatiecentrum v;
    Hub hub2;
    Vaccinatiecentrum vac;
    Vaccinatiecentrum *vac2;
    std::ofstream  ofs;
    VaccinType vaccinType;
    VaccinType vaccinType1;
};

/**
Tests the default constructor.
*/
TEST_F(HubDomainTest, HubDefaultConstructor) {
    EXPECT_TRUE(hub.correctlyInitialized());
    // verify post-condition
    EXPECT_EQ(0,hub.getAantalGer());
    EXPECT_EQ(0,hub.getAantalVac());

    //Initialisering waardes
    vaccinType.setAantalVaccins(1000);
    vaccinType.settemperatuur(20);
    vaccinType.sethernieuwing(2);
    vaccinType.setName("Hallo");
    vaccinType.setInterval(5);
    vaccinType.setTransport(220);
    vaccinType.setLevering(2000);
    vaccinType.setGereserveerd(500);

    //Testen voor de gelijkheid
    EXPECT_EQ(2000,vaccinType.getLevering());
    EXPECT_EQ(1000,vaccinType.getAantalVaccins());
    EXPECT_EQ(20,vaccinType.gettemperatuur());
    EXPECT_EQ(2,vaccinType.gethernieuwing());
    EXPECT_EQ("Hallo",vaccinType.getName());
    EXPECT_EQ(5,vaccinType.getInterval());
    EXPECT_EQ(220,vaccinType.getTransport());
    EXPECT_EQ(500,vaccinType.getGereserveerd());

    //Testen voor de niet gelijkheid
    EXPECT_NE(200,vaccinType.getLevering());
    EXPECT_NE(100,vaccinType.getAantalVaccins());
    EXPECT_NE(202,vaccinType.gettemperatuur());
    EXPECT_NE(21,vaccinType.gethernieuwing());
    EXPECT_NE("allo",vaccinType.getName());
    EXPECT_NE(54,vaccinType.getInterval());
    EXPECT_NE(20,vaccinType.getTransport());
    EXPECT_NE(50,vaccinType.getGereserveerd());

}

//Tests voor de Vaccinatiecentra constructor
TEST_F(HubDomainTest, CentrumDefaultConstructor ){
    EXPECT_TRUE(v.correctlyInitialized());
    EXPECT_EQ("", v.getNaamCentrum());
    EXPECT_EQ("", v.getAdresCentrum());
    EXPECT_EQ(0, v.getAantalGevaccineerden());
    v.setAantalVaccins("hallo",0);
    EXPECT_EQ(0, v.getAantalVaccinsVanType("hallo"));
    EXPECT_EQ(0, v.getAantalInwoners());
    EXPECT_EQ(0, v.getCapaciteit());

    //Initialisering waardes
    v.setCapaciteit(1500);
    v.setNaamCentrum("Antwerpen");
    v.setAdresCentrum("vijfstraat 5");
    v.setAantalInwoners(500);
    v.setAantalVaccins("hallo", 1300);
    v.setAantalGevaccineerden(1240);

    //Gelijkheid testen
    EXPECT_EQ(1500,v.getCapaciteit());
    EXPECT_EQ("Antwerpen",v.getNaamCentrum());
    EXPECT_EQ("vijfstraat 5", v.getAdresCentrum());
    EXPECT_EQ(500,v.getAantalInwoners());
    EXPECT_EQ(1300, v.getAantalVaccinsVanType("hallo"));
    EXPECT_EQ(1240,v.getAantalGevaccineerden());

    //Testen voor de niet gelijkheid
    EXPECT_NE(150,v.getCapaciteit());
    EXPECT_NE("Antwerpn",v.getNaamCentrum());
    EXPECT_NE("vijfsraat 5", v.getAdresCentrum());
    EXPECT_NE(50,v.getAantalInwoners());
    EXPECT_NE(130, v.getAantalVaccinsVanType("hallo"));
    EXPECT_NE(124,v.getAantalGevaccineerden());
}


////Tests voor de functie SubstractVaccins
TEST_F(HubDomainTest, substractVaccins) {
    //Initialisering waardes
    vaccinType.setAantalVaccins(500);


    //Substract op de hub uitvoeren
    vaccinType.substractVaccins(100);

    //Gelijkheid checken
    EXPECT_EQ(400,vaccinType.getAantalVaccins());

    //Substract op de hub uitvoeren
    vaccinType.substractVaccins(400);

    //Gelijkheid checken
    EXPECT_EQ(0,vaccinType.getAantalVaccins());

    //Initialisering waardes
    vaccinType.setLevering(4000);
    vaccinType.leveringVanTypeToHub();

    //Achtereenvolgens de substract uitvoeren en de gelijkheid bekijken
    vaccinType.substractVaccins(1000);
    EXPECT_EQ(3000,vaccinType.getAantalVaccins());
    vaccinType.substractVaccins(500);
    EXPECT_EQ(2500,vaccinType.getAantalVaccins());
    EXPECT_NE(2412,vaccinType.getAantalVaccins());
    vaccinType.substractVaccins(1000);
    EXPECT_NE(250,vaccinType.getAantalVaccins());
    EXPECT_EQ(1500,vaccinType.getAantalVaccins());
    vaccinType.substractVaccins(250);
    EXPECT_EQ(1250,vaccinType.getAantalVaccins());
}

////Tests voor de functie isLeveringsDag
TEST_F(HubDomainTest, isLeveringsDag){
    //Initialisering waardes
    vaccinType.setInterval(6);

    //Kijken of de functie een True of False teruggeeft
    EXPECT_TRUE(vaccinType.isLeveringsDag(7));
    EXPECT_FALSE(vaccinType.isLeveringsDag(3));
    EXPECT_FALSE(vaccinType.isLeveringsDag(1));
    EXPECT_FALSE(vaccinType.isLeveringsDag(5));
    vaccinType.setInterval(4);

    //Loopen en steeds de return waarde van de functie checken
    //Deze zou altijd false moeten teruggeven
    while(vaccinType.getInterval() != 6){
        EXPECT_FALSE(vaccinType.isLeveringsDag(8));
        vaccinType.setInterval(vaccinType.getInterval()+ 1);
    }

    //Waarde initaliseren en vervolgens de return waarde van de functie bekijken
    vaccinType.setInterval(vaccinType.getInterval()+1);
    EXPECT_TRUE(vaccinType.isLeveringsDag(8));
}

//Tests voor de functie notDone
TEST_F(HubDomainTest, notDone){
    //Initialisering alle waardes
    vac.setAantalInwoners(1000);
    vac.setCapaciteit(1000);

    //Testen op de return waarde van de functie
    EXPECT_FALSE(hub2.notDone());
    EXPECT_FALSE(hub.notDone());

    //Initalisering van alle waardes
    vac.setAantalVaccins("vac", 1000);
    vac.vaccineren(0, ofs);
    hub.addcentrum(&vac);

    //Testen op de return waarde van de functie
    EXPECT_FALSE(hub2.notDone());
    EXPECT_TRUE(hub.notDone());
}

//Tests voor de functie aantalOngevaccineerden
TEST_F(HubDomainTest, aantalOngevaccineerden){
    //Initialisering alle waardes
    vac.setAantalInwoners(1000);
    vac.setCapaciteit(1000);
    vac.vaccineren(0);
    hub2.addcentrum(&vac);

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
    VaccinType a = VaccinType();
    a.setName("a");
    std::map<std::string, VaccinType*> a2;
    a2["a"] = &a;
    v.setTypes(a2);
    v.addVaccins(500, "a");
    v.setAantalInwoners(1500);
    v.setCapaciteit(500);

    //Returnwaarde vergelijken met verwachtte waarde
    EXPECT_EQ(500, v.getAantalVaccinsVanType("a"));
    EXPECT_NE(0, v.getAantalVaccinsVanType("a"));
    v.vaccineren(0, ofs);
    EXPECT_EQ(0, v.getAantalVaccinsVanType("a"));
    EXPECT_NE(500, v.getAantalVaccinsVanType("a"));
}

//Tests voor de functie clear
TEST_F(HubDomainTest, clear){

    Simulation s = Simulation(&hub);

    //Initialisering alle waardes
    simulationImporter::importSimulation("./testInput/tt.xml", ofs,s);
    hub.vacLeveringen(17);

    EXPECT_EQ(0,s.getDag());
    EXPECT_EQ(40000,s.getHub()->getAantalVac());
    EXPECT_EQ(0,s.getHub()->getAantalGer());
    s.clear();

    EXPECT_EQ(0,s.getDag());
    EXPECT_EQ(0,s.getHub()->getAantalVac());
    EXPECT_EQ(0,s.getHub()->getAantalGer());
}

//Tests voor de functie substractvaccins
TEST_F(HubDomainTest,substractvaccin){

    vaccinType.setLevering(5000);
    vaccinType.leveringVanTypeToHub();
    vaccinType1.setLevering(2000);
    vaccinType1.leveringVanTypeToHub();

    vaccinType.substractVaccins(1000);
    vaccinType1.substractVaccins(500);

    EXPECT_EQ(4000,vaccinType.getAantalVaccins());
    EXPECT_NE(3210,vaccinType.getAantalVaccins());
    EXPECT_EQ(1500,vaccinType1.getAantalVaccins());
    EXPECT_NE(154214,vaccinType1.getAantalVaccins());

    vaccinType.substractVaccins(500);
    vaccinType1.substractVaccins(1000);

    EXPECT_NE(500,vaccinType.getAantalVaccins());
    EXPECT_NE(100,vaccinType.getAantalVaccins());
    EXPECT_EQ(3500,vaccinType.getAantalVaccins());
    EXPECT_NE(12312,vaccinType1.getAantalVaccins());
    EXPECT_NE(1500,vaccinType1.getAantalVaccins());
    EXPECT_EQ(500,vaccinType1.getAantalVaccins());
}
//Tests voor de functie leveringtohub
TEST_F(HubDomainTest,leveringtohub){

    vaccinType.setLevering(1354);
    vaccinType.leveringVanTypeToHub();
    vaccinType1.setLevering(1111);
    vaccinType1.leveringVanTypeToHub();

    EXPECT_EQ(1354,vaccinType.getAantalVaccins());
    EXPECT_NE(12,vaccinType.getAantalVaccins());
    EXPECT_NE(15,vaccinType1.getAantalVaccins());
    EXPECT_EQ(1111,vaccinType1.getAantalVaccins());

    vaccinType1.leveringVanTypeToHub();
    vaccinType1.leveringVanTypeToHub();
    vaccinType.leveringVanTypeToHub();

    EXPECT_EQ(3333,vaccinType1.getAantalVaccins());
    EXPECT_NE(1234,vaccinType1.getAantalVaccins());
    EXPECT_EQ(2708,vaccinType.getAantalVaccins());
    EXPECT_NE(1315,vaccinType.getAantalVaccins());
}
//Tests voor de functie isleveringsdag
TEST_F(HubDomainTest,isleveringsdag){
    vaccinType.setInterval(5);
    vaccinType1.setInterval(11);

    EXPECT_TRUE(vaccinType.isLeveringsDag(6));
    EXPECT_FALSE(vaccinType.isLeveringsDag(11));
    EXPECT_TRUE(vaccinType1.isLeveringsDag(12));
    EXPECT_FALSE(vaccinType1.isLeveringsDag(424));
    EXPECT_TRUE(vaccinType.isLeveringsDag(12));
    EXPECT_TRUE(vaccinType1.isLeveringsDag(24));
}
//Tests voor de functie nextleveringsdag
TEST_F(HubDomainTest,nextleveringsdag){

    vaccinType1.setInterval(5);
    vaccinType.setInterval(10);

    EXPECT_EQ(11,vaccinType.nextLeveringsDag(0));
    EXPECT_NE(22,vaccinType.nextLeveringsDag(0));
    EXPECT_EQ(6,vaccinType1.nextLeveringsDag(0));
    EXPECT_NE(12,vaccinType1.nextLeveringsDag(0));

    EXPECT_EQ(4,vaccinType1.nextLeveringsDag(8));
    EXPECT_NE(3,vaccinType1.nextLeveringsDag(8));
    EXPECT_EQ(3,vaccinType.nextLeveringsDag(30));
    EXPECT_NE(3,vaccinType.nextLeveringsDag(20));
}
//Tests voor de functie addgereserveerd
TEST_F(HubDomainTest,addgereserveerd){

    vaccinType.addGereserveerd(500);
    vaccinType1.addGereserveerd(1000);

    EXPECT_EQ(500,vaccinType.getGereserveerd());
    EXPECT_NE(1000,vaccinType.getGereserveerd());
    EXPECT_EQ(1000,vaccinType1.getGereserveerd());
    EXPECT_NE(500,vaccinType1.getGereserveerd());

    int test1 = vaccinType.getGereserveerd()/5;
    int test2 = vaccinType.getGereserveerd()*2;
    int test3 = vaccinType1.getGereserveerd()/5;
    int test4 = vaccinType1.getGereserveerd()*2;

    EXPECT_EQ(100,test1);
    EXPECT_EQ(1000,test2);
    EXPECT_EQ(200,test3);
    EXPECT_EQ(2000,test4);

    EXPECT_NE(222,test1);
    EXPECT_NE(1001,test2);
    EXPECT_NE(222,test3);
    EXPECT_NE(20001,test4);
}
//Tests voor de functie subgereserveerd
TEST_F(HubDomainTest,subgereserveerd){

    vaccinType1.setGereserveerd(5000);
    vaccinType.setGereserveerd(1000);
    vaccinType.subGereserveerd(1000);
    vaccinType1.subGereserveerd(200);

    EXPECT_EQ(0,vaccinType.getGereserveerd());
    EXPECT_EQ(4800,vaccinType1.getGereserveerd());

    EXPECT_NE(12,vaccinType1.getGereserveerd());
    EXPECT_NE(4000,vaccinType.getGereserveerd());
    EXPECT_NE(100,vaccinType.getGereserveerd());
    EXPECT_NE(4700,vaccinType1.getGereserveerd());

    vaccinType1.addGereserveerd(500);
    vaccinType1.subGereserveerd(1000);
    vaccinType.addGereserveerd(10000);
    vaccinType.subGereserveerd(4000);

    EXPECT_EQ(4300,vaccinType1.getGereserveerd());
    EXPECT_EQ(6000,vaccinType.getGereserveerd());

    EXPECT_NE(1111,vaccinType1.getGereserveerd());
    EXPECT_NE(5000,vaccinType.getGereserveerd());
    EXPECT_NE(1000,vaccinType.getGereserveerd());
    EXPECT_NE(6000,vaccinType1.getGereserveerd());

}

