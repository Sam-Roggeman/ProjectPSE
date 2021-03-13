//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include "DesignByContract.h"
#include "Project.h"
using namespace std;





int main(int argc, char **argv) {
    Hub hub;
    initializeSimulation("./testInput/test.xml", hub);
    autoSimulation(hub,0,5, std::cout);
    return 0;
}