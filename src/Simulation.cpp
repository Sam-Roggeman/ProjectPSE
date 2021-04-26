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
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
        hub->vacLeveringen(dag);

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra2(dag,out);
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(dag);
        out << std::endl;
    }
    ENSURE(dag == eind, "de autosimulation eindigde niet op de einddag");
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
//    1.1 IF er vaccins geleverd worden op de huidige dag
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
        hub->vacLeveringen(dag);
        hub->outputHub(out);

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra2(dag,out);
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(dag,out);
        out << std::endl;
        nextDay();

    }
    hub->outputHub(out);
    ENSURE(this->getHub()->aantalOngevaccineerden() == 0,"Aantal ongevaccineerden was niet 0 bij afloop van autoSimulationUntillDone");
}

void Simulation::addcentrum(Vaccinatiecentrum *v) {
    REQUIRE(v->correctlyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(v->completelyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    hub->addcentrum(v);
}

void Simulation::nextDay(){
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    int startdag = dag;
    dag += 1;
    ENSURE(dag == startdag+1, "dag was niet verghoogt met 1 na oproep van nextDay()");
}

int Simulation::getDag() const {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    REQUIRE(dag >= 0, "De dag mag niet negatief zijn");
    return dag;
}

void Simulation::setDag(int d) {
    REQUIRE(correctlyInitialized(), "Foutieve simulatie");
    REQUIRE(d > 0, "De dag mag niet negatief zijn");
    Simulation::dag = d;
}

void Simulation::clear() {
    hub->clear();
}

void Simulation::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "Hub was niet correct geinitializeerd bij oproep van impressie");
    this->getHub()->impressie(out);
}

