//============================================================================
// Name        : Simulation.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================

#ifndef PROJECT_SIMULATION_H
#define PROJECT_SIMULATION_H
#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include "DesignByContract.h"

//todo contracten
class Simulation {
    Simulation* _initcheck;
    Hub* hub;
    int dag;
public:
    /**Geeft de huidige dag van de simulatie terug
     * @returns Huidige dag
     * @pre this->correctlyinitialized()
     */
    int getDag() const;

    /**Zet de huidige dag in de variable "dag"
     *
     * @param dag: De huidige dag die in de simulatie wordt gezet
     * @pre this->correctlyinitialized()
     * @pre De dag is een natuurlijke getal
     */
    void setDag(int dag);

    /**Dit is de constructor voor het maken van een simulatie
     *
     * @param hub1: Dit is de hub die we voor de simulatie gaan gebruiken
     * @pre hub1->correctlyInitialized()
     * @post this->getHub() != NULL
     * @post this->getHub()->correctlyInitialized()
     * @pre this->correctlyInitialized()
     */
    Simulation(Hub* hub1);


    /**Een functie die alles in de hub en het vaccinatiecentrum output door cout
     * @pre this->correctlyInitialized()
     */
    void outputSimulation();
    /**Een functie die alles in de hub en de vaccinatiecentra output naar een gegeven ostream
     * @param out: De ostream waar de gegeven output naartoe gaat
     * @pre this->correctlyInitialized()
     * @pre this->correctlyInitialized()
     */
    void outputSimulation(std::ostream &out);

    /**Dit is een automatische simulatie van de transport van vaccins tot een
     * gegeven einddag en de output wordt bepaald door de gegeven ostream
     * @param start: De gegeven startdag
     * @param eind: De gegeven einddag
     * @param out: De ostream waar de output naartoe gaat
     * @pre hub->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @post this->dag == eind
     */
    void autoSimulation(int start, int eind, std::ostream &out);
    /**Dit is een automatische simulatie van de transport van vaccins tot
     * een gegeven einddag en de output hiervan wordt gegeven door cout
     * @param start: De gegeven startdag
     * @param eind: De gegeven einddag
     * @pre hub->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @post this->dag == eind
     */
    void autoSimulation(int start, int eind);
    /**Dit is een automatische simulatie van de transport van vaccins tot
     * elke persoon in elk vaccinatiecentrum gevaccineerd is en deze output met cout
     * @pre hub->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @post this->getHub()->getAantalOngevaccineerden() == 0
     */
    void autoSimulationUntilDone();
    /**Dit is een automatische simulatie van de transport van vaccins tot elke
     * persoon in elk vaccinatiecentrum gevaccineerd is en de waar de output bepaald wordt door ostream
     * @param out: De ostream die bepaalt wat de locatie van de output wordt
     * @pre hub->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @post this->getHub()->getAantalOngevaccineerden() == 0
     */
    void autoSimulationUntilDone(std::ostream &out);

    /**Geeft de hub van de simulatie terug
     * @return De hub die de simulatie bevat
     * @pre this->correctlyInitialized()
     * @pre hub->correctlyInitialized()
     */
    Hub * getHub() const;

    /**Zet de gegeven hub in als de hub van de simulatie
     * @param h: De hub die in de simulatie wordt gezet
     * @pre hub->correctlyInitialized()
     * @pre this->correctlyInitialized()
     */
    void setHub(Hub *h);

    /**Voegt een gegeven vaccinatiecentra toe aan de simulatie
     *
     * @param v: Een gegeven vaccinatiecentrum die aan de simulatie wordt toegoegd
     * @pre v->correctlyInitialized()
     * @pre v->completelyInitialized()
     * @pre this->correctlyInitialized()
     * @pre hub->vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end()
     * @post hub->vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) != vaccinatiecentra.end()
     * @post hub->vaccinatiecentra.size() += 1
     */
    void addcentrum(Vaccinatiecentrum *v);

    /**Zorgt ervoor dat de simulatie van de huidige dag naar de volgende dag gaat
     * @pre this->correctlyInitialized()
     * @post dag == startdag +1
     */
    void nextDay();

    /**Kijkt na of de simulatie correct geinitialiseerd is
     * @return Een boolean: True als de simulatie juist is geinitialiseerd
     */
    bool correctlyInitialized() const;

    /**Dit cleared heel de simulatie
     * @pre this->correctlyInitialized()
     */
    void clear();

    /**Maakt een grafische impressie van de huidige staat van de simulatie
     * @param out de ostream waarnaar de impressie wordt uitgeput
     * @pre this->correctlyinitialized()
     * */
    void impressie(std::ostream &out);
};


#endif //PROJECT_SIMULATION_H
