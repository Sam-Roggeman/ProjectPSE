//
// Created by User on 1/03/2021.
//

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
//void autoSimulation(Hub& hub, int start, int eind, std::ostream out);
void autoSimulation(Hub& hub, int start, int eind);



#endif //PROJECT_PROJECT_H
