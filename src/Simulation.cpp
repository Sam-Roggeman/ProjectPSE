//============================================================================
// Name        : Simulation.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================
#include "Simulation.h"

Simulation::Simulation(Hub *hub1) {
    REQUIRE(hub1->correctlyInitialized(),"hub niet geinitializeerd bij aanroep simulatie constructor");
    hub = hub1;
    _initcheck = this;
    dag =0;
    ENSURE(this->getHub() != NULL, "Geen hub toegevoegd");
    ENSURE(this->getHub()->correctlyInitialized(), "hub niet geinitializeerd bij einde simulatie constructor");
    ENSURE(this->correctlyInitialized(), "simulatie niet geinitializeerd bij einde simulatie constructor");
}


Hub * Simulation::getHub() const {
    REQUIRE(correctlyInitialized(),"simulatie niet geinitializeerd bij aanroep getHub");
    REQUIRE(hub->correctlyInitialized(),"hub niet geinitializeerd bij aanroep getHub");
    return hub;
}

bool Simulation::correctlyInitialized() const {
    return this == _initcheck;
}

void Simulation::setHub(Hub *h) {
    REQUIRE(h->correctlyInitialized(),"meegegeven hub niet geinitializeerd bij aanroep setHub");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep setHub");
    Simulation::hub = h;
}



void Simulation::outputSimulation(std::ostream &out) {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep outputSimulation");
    REQUIRE(hub->correctlyInitialized(),"meegegeven hub niet geinitializeerd bij aanroep outputSimulation");
    hub->outputHub(out);
}

void Simulation::outputSimulation() {
    outputSimulation(std::cout);
}

void Simulation::autoSimulation(int start, int eind) {
    REQUIRE(hub->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autosimulation");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    autoSimulation(start, eind, std::cout);
}

void Simulation::autoSimulation(int start, int eind, std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(start>=0, "startdag <0");
    REQUIRE(eind >start, "einddag <=startdag");
    REQUIRE(hub->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autosimulation");
    REQUIRE(hub->completelyInitialized(), "hub niet compleet geinitializeerd bij aanroep autoSimulation");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    dag = start;
//    1.  WHILE huidige dag<eind dag
    while (dag < eind) {
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
        hub->vaccineren(dag);
        nextDay();
        out << std::endl;
    }
    ENSURE(dag == eind, "de autosimulation eindigde niet op de einddag");
}

void Simulation::autoSimulationUntilDone() {
    autoSimulationUntilDone(std::cout);
}


void Simulation::autoSimulationUntilDone(std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(hub->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autoSimulationUntilDone");
    REQUIRE(hub->completelyInitialized(), "hub niet compleet geinitializeerd bij aanroep autoSimulationUntilDone");
    REQUIRE(this->correctlyInitialized(), "centrum niet geinitializeerd bij aanroep autoSimulationUntilDone");
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
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep addcentrum");
    hub->addcentrum(v);
}

void Simulation::nextDay(){
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep nextDay");
    int startdag = dag;
    dag += 1;
    ENSURE(dag == startdag+1, "dag was niet verghoogt met 1 na oproep van nextDay()");
}

int Simulation::getDag() const {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep getDag");
    REQUIRE(dag >= 0, "De dag mag niet negatief zijn");
    return dag;
}

void Simulation::setDag(int d) {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep setDag");
    REQUIRE(d > 0, "De dag mag niet negatief zijn");
    Simulation::dag = d;
}

void Simulation::clear() {
    hub->clear();
}

void Simulation::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van impressie");
    this->getHub()->impressie(out);
}

