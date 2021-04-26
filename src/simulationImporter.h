//
// Created by User on 31/03/2021.
//

#ifndef PROJECT_SIMULATIONIMPORTER_H
#define PROJECT_SIMULATIONIMPORTER_H
#include "Simulation.h"

//todo contracten

class simulationImporter {
public:
    /**Initialiseert een simulatie uit een xml file
     *
     * @param filename: De file waar de simulatie die uitgevoerd moet worden instaat
     * @param errstream De outputstream waar de errors naartoe gestuurd worden
     * @param sim, de plaats waar de simulatie terecht komt
     * @return Een 0 als er niks verkeerd is gegaan en een 1 als er iets fouts is gegaan
     * @pre root != NULL
     * @post hub->completelyInitialized()
     * @post hubcounter < 2
     * @post vaccinatiecentracounter > 0
     * @post hubcounter > 0
     */
    static int importSimulation(const char *filename, std::ostream &errstream, Simulation &sim);
};
#endif //PROJECT_SIMULATIONIMPORTER_H
