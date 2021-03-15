//
// Created by User on 1/03/2021.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>
#include "Project.h"

#include "Hub.h"

class HubDomainTest: public ::testing::Test {
protected:
    friend class Hub;

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Hub hub;
    Vaccinatiecentrum v;
    Hub hub2;
    Vaccinatiecentrum vac;
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

    hub.setLevering(500);
    hub.setInterval(6);
    hub.setTransport(50);
    hub.leveringToHub();
    EXPECT_EQ(500,hub.getLevering());
    EXPECT_EQ(500,hub.getAantalVaccins());
    EXPECT_EQ(50,hub.getTransport());
    EXPECT_EQ(6,hub.getInterval());

    EXPECT_NE(50,hub.getLevering());
    EXPECT_NE(500,hub.getTransport());
    EXPECT_NE(5,hub.getInterval());
    EXPECT_NE(1203,hub.getAantalVaccins());
}

TEST_F(HubDomainTest, CentrumDefaultConstructor ){
    EXPECT_TRUE(v.correctlyInitialized());
    EXPECT_EQ("", v.getNaamCentrum());
    EXPECT_EQ("", v.getAdresCentrum());
    EXPECT_EQ(0, v.getAantalGevaccineerden());
    EXPECT_EQ(0, v.getAantalVaccins());
    EXPECT_EQ(0, v.getAantalInwoners());
    EXPECT_EQ(0, v.getCapaciteit());

    v.setCapaciteit(1500);
    v.setNaamCentrum("Antwerpen");
    v.setAdresCentrum("vijfstraat 5");
    v.setAantalInwoners(500);
    v.setAantalVaccins(1300);
    v.setAantalGevaccineerden(1240);
    EXPECT_EQ(1500,v.getCapaciteit());
    EXPECT_EQ("Antwerpen",v.getNaamCentrum());
    EXPECT_EQ("vijfstraat 5", v.getAdresCentrum());
    EXPECT_EQ(500,v.getAantalInwoners());
    EXPECT_EQ(1300,v.getAantalVaccins());
    EXPECT_EQ(1240,v.getAantalGevaccineerden());
}

TEST_F(HubDomainTest, substractVaccins) {
    hub2.setLevering(1000);
    hub2.leveringToHub();
    hub2.substractVaccins(0);
    EXPECT_EQ(1000,hub2.getAantalVaccins());
    hub2.substractVaccins(1000);
    EXPECT_EQ(0,hub2.getAantalVaccins());

    hub2.leveringToHub();
    hub2.leveringToHub();
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

TEST_F(HubDomainTest, isLeveringsDag){
    hub2.setInterval(1);
    hub.setInterval(6);
    EXPECT_TRUE(hub2.isLeveringsDag(2));
    EXPECT_FALSE(hub2.isLeveringsDag(3));
    EXPECT_TRUE(hub.isLeveringsDag(7));
    EXPECT_FALSE(hub.isLeveringsDag(5));
    hub2.setInterval(0);
    while(hub2.getInterval() != 6){
        EXPECT_FALSE(hub.isLeveringsDag(8));
        hub2.setInterval(hub2.getInterval()+ 1);
    }
    hub2.setInterval(hub2.getInterval()+1);
    EXPECT_TRUE(hub2.isLeveringsDag(8));
}
TEST_F(HubDomainTest, notDone){
    vac.setAantalInwoners(1000);
    hub2.addcentrum(&vac);
    vac.setCapaciteit(1000);
    EXPECT_TRUE(hub2.notDone());
    EXPECT_FALSE(hub.notDone());
    vac.setAantalVaccins(1000);
    vac.vaccineren();
    EXPECT_FALSE(hub2.notDone());
}

TEST_F(HubDomainTest, aantalOngevaccineerden){
    vac.setAantalInwoners(1000);
    hub2.addcentrum(&vac);
    vac.setCapaciteit(1000);
    hub2.vaccineren();
    EXPECT_EQ(0, hub.aantalOngevaccineerden());
    EXPECT_EQ(1000,hub2.aantalOngevaccineerden());
}
TEST_F(HubDomainTest, addGevaccineerden){
    vac.addGevaccineerden(500);
    EXPECT_EQ(500,vac.getAantalGevaccineerden());
    EXPECT_EQ(0,v.getAantalGevaccineerden());
    EXPECT_NE(0,vac.getAantalGevaccineerden());
    EXPECT_NE(500,v.getAantalGevaccineerden());
    v.addGevaccineerden(5400);
    EXPECT_EQ(5400,v.getAantalGevaccineerden());
    vac.addGevaccineerden(1500);
    EXPECT_EQ(2000,vac.getAantalGevaccineerden());
}

TEST_F(HubDomainTest, addVacins){
    v.addVaccins(500);
    v.setAantalInwoners(1500);
    v.setCapaciteit(500);
    EXPECT_EQ(500,v.getAantalVaccins());
    EXPECT_NE(0,v.getAantalVaccins());
    v.vaccineren();
    EXPECT_EQ(0,v.getAantalVaccins());
    EXPECT_NE(500,v.getAantalVaccins());
}
/*TODO
 * Vaccinatiecentrum:
     * addGevaccineerden(int aantal_gevaccineerden);
     * void addVaccins(int aantal);

*/