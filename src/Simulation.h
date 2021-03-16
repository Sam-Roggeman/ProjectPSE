//
// Created by User on 16/03/2021.
//

#ifndef PROJECT_SIMULATION_H
#define PROJECT_SIMULATION_H
#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include "DesignByContract.h"


class Simulation {
    Simulation* _initcheck;
    Hub* hub;
    int dag;
public:
    int getDag() const;

    void setDag(int dag);

    Simulation(Hub* hub1);

    int initializeSimulation(const char *filename, std::ostream &errstream);
    void outputSimulation();
    void outputSimulation(std::ostream &out);
    void autoSimulation(int start, int eind, std::ostream &out);
    void autoSimulation(int start, int eind);
    void autoSimulationUntilDone();
    void autoSimulationUntilDone(std::ostream &out);

    const Hub * getHub() const;

    void setHub(Hub *h);

    void addcentrum(Vaccinatiecentrum *v);

    void nextDay();

    bool correctlyInitialized();

    void clear();
};


#endif //PROJECT_SIMULATION_H
