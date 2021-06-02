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
#include "vaccininterface.h"
#include <QApplication>

using namespace std;


/*
 * todo sam
 */

//todo said:

//todo

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VaccinInterface w;
    w.show();
    return a.exec();
}

//int main(int argc, char **argv) {
//    Simulation* simulatie;
//    Gegevens gegevens = Gegevens();
//    simulatie = new Simulation();
//    ofstream o;
//    simulationImporter::importSimulation("/mnt/a/School/2020-2021/pse/ProjectPSE/testInput/Juist.xml", std::cout, *simulatie);
//
//    simulatie->simulateDay(gegevens, o);
//    simulatie->impressie(std::cout);
//
//    simulatie = new Simulation(*simulatie);
//
////    ofstream o;
////    o.open("test.txt");
////    Simulation s;
////    simulationImporter::importSimulation("./testInput/t2.xml",  std::cout, s);
////    s.autoSimulationUntilDone(std::cout);
////    o.close();
//    return 0;
//}

