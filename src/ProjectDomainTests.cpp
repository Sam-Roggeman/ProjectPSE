//
// Created by User on 1/03/2021.
//

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <gtest/gtest.h>

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
}

TEST_F(HubDomainTest, CentrumDefaultConstructor ){
    EXPECT_TRUE(v.correctlyInitialized());
    EXPECT_EQ("", v.getNaamCentrum());
    EXPECT_EQ("", v.getAdresCentrum());
    EXPECT_EQ(0, v.getAantalGevaccineerden());
    EXPECT_EQ(0, v.getAantalVaccins());
    EXPECT_EQ(0, v.getAantalInwoners());
    EXPECT_EQ(0, v.getCapaciteit());
}

TEST_F(HubDomainTest, substractVaccins) {
    hub2.setLevering(1000);
    hub2.leveringToHub();
    hub2.substractVaccins(0);
    EXPECT_EQ(1000,hub2.getAantalVaccins());
    hub2.substractVaccins(1000);
    EXPECT_EQ(0,hub2.getAantalVaccins());
}

TEST_F(HubDomainTest, isLeveringsDag){
    hub2.setInterval(1);
    hub.setInterval(6);
    EXPECT_TRUE(hub2.isLeveringsDag(2));
    EXPECT_FALSE(hub2.isLeveringsDag(3));
    EXPECT_TRUE(hub.isLeveringsDag(7));
    EXPECT_FALSE(hub.isLeveringsDag(5));
}
TEST_F(HubDomainTest, notDone){
    vac.setAantalInwoners(1000);
    hub2.addcentrum(&vac);
    EXPECT_FALSE(hub2.notDone());
    EXPECT_TRUE(hub.notDone());
}

TEST_F(HubDomainTest, aantalOngevaccineerden){
    vac.setAantalInwoners(1000);
    hub2.addcentrum(&vac);
    vac.setCapaciteit(1000);
    hub2.vaccineren();
    EXPECT_EQ(0, hub.aantalOngevaccineerden());
    EXPECT_EQ(1000,hub2.aantalOngevaccineerden());
}
//TODO
//    void substractVaccins(int vaccins);
//    void leveringToHub();
//    bool isLeveringsDag(int dag);
//    bool notDone();
//    int aantalOngevaccineerden();
