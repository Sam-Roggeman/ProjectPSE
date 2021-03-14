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

}

//TODO
//    void substractVaccins(int vaccins);
//    void leveringToHub();
//    bool isLeveringsDag(int dag);
//    bool notDone();
//    int aantalOngevaccineerden();
