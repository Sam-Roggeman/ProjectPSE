//============================================================================
// Name        : ProjectMain.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Project Main in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include <fstream>
#include "DesignByContract.h"
#include "Project.h"
#include "Simulation.h"


using namespace std;





int main(int argc, char **argv) {
    ofstream o;
//    o.open("a.txt");
    Hub h = Hub();
    Simulation s = Simulation(&h);
//    hub.addcentrum(&v);
//    o.open("./testOutput/testFiles");

//    initializeSimulation("./testInput/test.xml", hub);

//    outputSimulation(hub, o);
//    autoSimulationUntilDone(hub);
//    autoSimulation(hub,0,5);
//    o.close();
    Vaccinatiecentrum v;
    s.addcentrum(&v);
    v.setNaamCentrum("a");
    v.setAdresCentrum("A");
    s.outputSimulation();
    //    o.open("./testOutput/testFiles");
//    s.outputSimulation(o);
//    o.close();
//    v.setCapaciteit(9000);
//    v.setAantalInwoners(2000);
//    o.open("./testOutput/outputSimulation2.txt");
//    s.outputSimulation(o);
//    o.close();
//    o.open("./testOutput/outputSimulation3.txt");
//    v.setAantalGevaccineerden(2000);
//    s.outputSimulation(o);
//    o.close();
    return 0;
}

