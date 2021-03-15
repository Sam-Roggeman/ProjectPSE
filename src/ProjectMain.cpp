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
#include <fstream>
#include "DesignByContract.h"
#include "Project.h"


using namespace std;





int main(int argc, char **argv) {
    ofstream o;
//    o.open("a.txt");
    Hub hub;
    Vaccinatiecentrum v;
//    hub.addcentrum(&v);
//    o.open("./testOutput/testFiles");

//    initializeSimulation("./testInput/test.xml", hub);

//    outputSimulation(hub, o);
//    autoSimulationUntilDone(hub);
//    autoSimulation(hub,0,5);
//    o.close();

    hub.addcentrum(&v);
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    o.open("./testOutput/testFiles");
    outputSimulation(hub, o);
    o.close();
    v.setCapaciteit(9000);
    v.setAantalInwoners(2000);
    o.open("./testOutput/outputSimulation2.txt");
    outputSimulation(hub, o);
    o.close();
    o.open("./testOutput/outputSimulation3.txt");
    v.setAantalGevaccineerden(2000);
    outputSimulation(hub, o);
    o.close();
    return 0;
}

