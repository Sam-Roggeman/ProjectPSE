//
// Created by User on 16/03/2021.
//
#include "Simulation.h"

Simulation::Simulation(Hub *hub1) {
    REQUIRE(hub1->correctlyInitialized(),"Foutieve hub");
    hub = hub1;
    _initcheck = this;
    dag =0;
    ENSURE(this->getHub() != NULL, "Geen hub toegevoegd");
    ENSURE(this->getHub()->correctlyInitialized(), "Foutieve hub");
}


const Hub * Simulation::getHub() const {
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

int Simulation::initializeSimulation(const char *filename, std::ostream &errstream) {
    this->clear();
    int hubcounter = 0;
    int vaccinatiecentracounter = 0;
    Vaccinatiecentrum* centrum;
    TiXmlDocument doc;
    //open xml file indien: ASCII bestand met daarop een beschrijving van de vaccinatiecentra
    if (!doc.LoadFile(filename)) {
        errstream << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    //als er geen root element is
    REQUIRE(root != NULL, "Failed to load file: No root element.");
    //loop over alle child elementen zolang het bestand niet is ingelezen
    for (TiXmlElement *cdElement = root->FirstChildElement();
         cdElement != NULL; cdElement = cdElement->NextSiblingElement()) {
        std::string elem_name = cdElement->Value();
        //vindt het soort element
        if (elem_name == "VACCINATIECENTRUM") {
            vaccinatiecentracounter += 1;
            centrum = new Vaccinatiecentrum();
            //loop over alle kinderelementen
            for (TiXmlElement *vac_elem = cdElement->FirstChildElement();
                 vac_elem != NULL; vac_elem = vac_elem->NextSiblingElement()) {
                elem_name = vac_elem->Value();
                //herken het element
                if (elem_name == "naam") {
                    centrum->setNaamCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "adres") {
                    centrum->setAdresCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "inwoners") {
                    centrum->setAantalInwoners(std::atoi(vac_elem->FirstChild()->Value()));
                } else if (elem_name == "capaciteit") {
                    centrum->setCapaciteit(std::atoi(vac_elem->FirstChild()->Value()));
                } else {
                    errstream << "element niet herkend" << std::endl;
                }
            }
            hub->addcentrum(centrum);
        } else if (elem_name == "HUB") {
            hubcounter += 1;
            //loop over alle kinderelementen
            for (TiXmlElement *hub_elem = cdElement->FirstChildElement(); hub_elem != NULL; hub_elem = hub_elem->NextSiblingElement()) {
                elem_name = hub_elem->Value();
                //herken het element
                if (elem_name == "levering") {
                    hub->setLevering(atoi(hub_elem->FirstChild()->Value()));
                    hub->leveringToHub();
                } else if (elem_name == "interval") {
                    hub->setInterval(atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "transport") {
                    hub->setTransport(std::atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "CENTRA"){
                    continue;
                }
                    //element is niet herkent
                else {
                    errstream << "element niet herkend" << std::endl;
                }
            }
        }
            //element is geen hub of centrum
        else {
            errstream << "element niet herkend" << std::endl;
        }
    }
    ENSURE(hub->completelyInitialized(), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    ENSURE((hubcounter < 2),"Je mag maar 1 hub hebben");
    ENSURE((vaccinatiecentracounter > 0),"Je moet minstens 1 vaccinatiecentrum hebben");
    ENSURE(hubcounter > 0,"Je moet minstens 1 Hub hebben");
    doc.Clear();
    return 0;
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

