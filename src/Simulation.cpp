//============================================================================
// Name        : Simulation.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================
#include "Simulation.h"

Simulation::Simulation(Hub *hub1) {
    REQUIRE(hub1->correctlyInitialized(),"Foutieve hub");
    hub = hub1;
    _initcheck = this;
    dag =0;
    ENSURE(this->getHub() != NULL, "Geen hub toegevoegd");
    ENSURE(this->getHub()->correctlyInitialized(), "Foutieve hub");
}


Hub * Simulation::getHub() const {
    REQUIRE(correctlyInitialized(),"Foutieve simulatie");
    REQUIRE(hub->correctlyInitialized(),"Foutieve hub");
    return hub;
}

bool Simulation::correctlyInitialized() const {
    return this == _initcheck;
}

void Simulation::setHub(Hub *h) {
    REQUIRE(h->correctlyInitialized(),"Foutieve hub");
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    Simulation::hub = h;
}



void Simulation::outputSimulation(std::ostream &out) {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    hub->outputHub(out);
}

void Simulation::outputSimulation() {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    outputSimulation(std::cout);
}

void Simulation::autoSimulation(int start, int eind) {
    REQUIRE(hub->correctlyInitialized(), "Foutieve hub");
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    autoSimulation(start, eind, std::cout);
}

void Simulation::autoSimulation(int start, int eind, std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(hub->correctlyInitialized(), "Foutieve hub");
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
//    1.  WHILE huidige dag<eind dag

    for (int current = start; current < eind; current++) {
        out << "DAG " << current << ":" << std::endl;
        hub->outputHub(out);
//    1.1 IF er vaccins geleverd worden op de huidige dag
        if (hub->isLeveringsDag(current) && current != 0){
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
            hub->leveringToHub();
        }

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra(out);
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(out);
        out << std::endl;
    }

}

void Simulation::autoSimulationUntilDone() {
    REQUIRE(hub->correctlyInitialized(), "Foutieve hub");
    REQUIRE(hub->completelyInitialized(), "Foutieve hub");
    autoSimulationUntilDone(std::cout);
}


void Simulation::autoSimulationUntilDone(std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(hub->correctlyInitialized(), "Foutieve hub");
    REQUIRE(hub->completelyInitialized(), "Foutieve hub");
//    1.  WHILE not done
    while (hub->notDone()){
        out << "DAG " << dag << ":" << std::endl;
        hub->outputHub(out);
//    1.1 IF er vaccins geleverd worden op de huidige dag
        if (hub->isLeveringsDag(dag) && dag != 0){
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
            hub->leveringToHub();
        }

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra(out);
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(out);
        out << std::endl;
        nextDay();
    }
}

void Simulation::addcentrum(Vaccinatiecentrum *v) {
    REQUIRE(v->correctlyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(v->completelyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    hub->addcentrum(v);
}

void Simulation::nextDay(){
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    dag += 1;
}

int Simulation::getDag() const {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    REQUIRE(dag >= 0, "De dag mag niet negatief zijn");
    return dag;
}

void Simulation::setDag(int d) {
    REQUIRE(d > 0, "De dag mag niet negatief zijn");
    Simulation::dag = d;
}

void Simulation::clear() {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    hub->clear();
}

