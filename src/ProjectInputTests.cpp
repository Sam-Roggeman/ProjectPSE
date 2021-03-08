//
// Created by User on 1/03/2021.
//
#include "gtest/gtest.h"
#include "Hub.h"
#include "ProjectMain.cpp"
Hub hub;
TEST (Goedefiletest, Juistteruggeven){
    EXPECT_EQ(initializeSimulation("test.xml",hub), 0);

}

TEST(FouteFiletest,foutteruggeven){
    EXPECT_EQ(initializeSimulation("test1.xml",hub), 1);
}