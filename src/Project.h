//============================================================================
// Name        : Project.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : project simulation functions in C++, Ansi-style
//============================================================================

#ifndef PROJECT_PROJECT_H
#define PROJECT_PROJECT_H
#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include "DesignByContract.h"

int initializeSimulation(const char *filename, Hub &hub);
void outputSimulation(const Hub& hub);
void outputSimulation(const Hub& hub,std::ostream& out);
void autoSimulation(Hub& hub, int start, int eind, std::ostream& out);
void autoSimulation(Hub& hub, int start, int eind);
void autoSimulationUntilDone(Hub &hub);
void autoSimulationUntilDone(Hub& hub, std::ostream &out);



#endif //PROJECT_PROJECT_H
