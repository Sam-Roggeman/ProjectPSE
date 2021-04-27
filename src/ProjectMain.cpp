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
#include "Simulation.h"
#include "simulationImporter.h"

using namespace std;


/*
 * todo sam
 *  contracten:
 *          done:
 *              Hub
 *              Simulation
 *              Importer
 *              Type
 *          notdone:
 *              Centrum
 *  3d-omgeving
 *
 */

//todo said:

//todo

int main(int argc, char **argv) {

    ofstream o;
    o.open("test.txt");
    Hub h = Hub();
    Simulation s = Simulation(&h);
    simulationImporter::importSimulation("t2.xml",  std::cout, s);
//    s.autoSimulationUntilDone(std::cout);
    s.impressie(std::cout);
    s.autoSimulationUntilDone(std::cout);
//    s.impressie(std::cout);
//    h.transportToCentra(0);
//    s.impressie(std::cout);
//    h.vaccineren();
//    s.impressie(std::cout);
//    s.initializeSimulation("./testInput/test.xml", std::cerr);
//    s.autoSimulationUntilDone();
//    s.autoSimulation(0,5);
    o.close();
    return 0;
}

