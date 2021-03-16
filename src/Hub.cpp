//============================================================================
// Name        : Hub.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Hub simulation in C++, Ansi-style
//============================================================================

#include "Hub.h"

Hub::Hub() {
    _initCheck = this;
    this->interval = 0;
    this->levering = 0;
    this->transport = 0;
    aantal_vaccins = 0;
    ENSURE(this->getLevering() == 0, "levering is niet 0 op het einde van de default constructor");
    ENSURE(this->getAantalVaccins() == 0, "aantal vaccins is niet 0 op het einde van de default constructor");
    ENSURE(this->getInterval() == 0, "interval is niet 0 op het einde van de default constructor");
    ENSURE(this->getTransport() == 0, "transport is niet 0 op het einde van de default constructor");
    ENSURE(this->correctlyInitialized(),
           "Het hub object was niet goed geinitializeerd bij het einde van de constructor");
}

int Hub::getAantalVaccins() const {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van getAantalVaccins");
    return aantal_vaccins;
}

bool Hub::correctlyInitialized() const {
    bool out = true;
    if (this != _initCheck){
        out = false;
    }
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        if (!it->second->correctlyInitialized()){
            out = false;
        }
    }
    return out;
}

void Hub::outputHub() const {
    outputHub(std::cout);
}

void Hub::outputHub(std::ostream& out) const {
    REQUIRE(this->correctlyInitialized(), "foutieve hub");
    out << "Hub (" << this->aantal_vaccins <<" vaccins)"<< std::endl;
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
            it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << "\t-> " << centrum->getNaamCentrum() <<" ("<< centrum->getAantalVaccins() << " vaccins)"<<std::endl;
    }
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
         it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << centrum->getNaamCentrum() <<": "<< centrum->getAantalGevaccineerden() << " gevaccineerd"<< ", nog " <<
                centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd" <<std::endl;
    }
}

void Hub::transportToCentra() {
    transportToCentra(std::cout);
}

void Hub::transportToCentra(std::ostream& out) {
    REQUIRE(this->correctlyInitialized(), "Hub is niet geinitializeerd bij oproep van transportToCentra");
    Vaccinatiecentrum* centrum;

    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        int aantal_ladingen = 0;
        int tot_lading = 0;
        centrum = it->second;
        while (centrum->getCapaciteit() > tot_lading + centrum->getAantalVaccins()){
            tot_lading += this->transport;
            aantal_ladingen++;
        }
        if (tot_lading > 2*centrum->getCapaciteit() ){
            std::cerr << "2* capaciteit overeschreven " << std::endl;
            return;
        }
        if (tot_lading <= this->aantal_vaccins){
            centrum->addVaccins(tot_lading);
            this->substractVaccins(tot_lading);
            out << "Er werden " << aantal_ladingen << " ladingen (" << tot_lading <<" vaccins) getransporteerd naar " <<
                    centrum->getNaamCentrum() << "." << std::endl;
        }
    }
}

void Hub::substractVaccins(int vaccins) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van substractVaccins");
    REQUIRE(vaccins >= 0, "substractVaccins accepteerd geen negatieve getallen");
    int old = aantal_vaccins;
    this->aantal_vaccins -= vaccins;
    ENSURE(aantal_vaccins >= 0, "aantal overgebleven vaccins is minder dan 0 na substracting");
    ENSURE(aantal_vaccins == old -vaccins,
           "oud aantal vaccins - verschil is niet gelijk aan nieuw aantal na substracting");
}


bool Hub::isLeveringsDag(int dag) {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitializeerd bij oproep van isLeveringDag");
    REQUIRE(dag >= 0, "Dag kan geen negatieve getal zijn");
    if (dag % (interval+1) == 0)
        return true;
    else
        return false;
}

void Hub::leveringToHub() {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitalizeerd bij oproep van leveringToHub");
    int old = aantal_vaccins;
    aantal_vaccins += levering;
    ENSURE(old == aantal_vaccins - levering, "Vaccins is incorrect afgetrokken van de hub");
}

void Hub::vaccineren() {
    vaccineren(std::cout);
}

void Hub::vaccineren(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van vaccineren");
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        Vaccinatiecentrum* centrum = it->second;
        int aantal_vaccins_start = centrum->getAantalVaccins();
        int gevaccineerden = centrum->getAantalGevaccineerden();
        centrum->vaccineren(out);
        ENSURE(centrum->getAantalVaccins()<= aantal_vaccins_start, "Aantal vaccins is gestegen na vaccineren" );
        ENSURE(centrum->getAantalGevaccineerden()>= gevaccineerden, "Gevaccineerden is gezakt na vaccineren" );
    }
}

int Hub::getInterval() const {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van getInterval");
    return interval;
}

void Hub::setInterval(int interval1) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van setInterval");
    REQUIRE(interval1>=0, "Het interval moet een natuurlijk getal zijn");
    Hub::interval = interval1;
}

int Hub::getTransport() const {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van getTransport");
    return transport;
}


void Hub::setTransport(int transport1) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van setTransport");
    REQUIRE(transport1 >= 0,"transport moet een natuurlijk getal zijn");
    Hub::transport = transport1;
}

void Hub::addcentrum(Vaccinatiecentrum *vaccinatiecentrum) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van addcentrum");
    REQUIRE(vaccinatiecentrum->correctlyInitialized(),
            "Het vaccinatiecentrum object was niet geinitializeerd oproeping van addcentrum");
    REQUIRE(vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end(),
            "Naam van centrum komt al voor in de lijst van centra bij oproep van addcentrum");
    unsigned int s1 = this->vaccinatiecentra.size();
    vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;

    ENSURE(s1+1 == this->vaccinatiecentra.size(),"lijst met vaccinatiecentra is niet verhoogd");
}

void Hub::setLevering(int levering1) {
    REQUIRE(levering1>=0,"Levering moet een natuurlijk getal zijn");
    Hub::levering = levering1;
    ENSURE(levering == levering1,"Levering is niet gewijzigd naar levering1 na setLevering");
}

bool Hub::notDone(){
    REQUIRE(this->correctlyInitialized(),"De hub was niet geinitializeerd bij oproep van notDone");
    if (this->aantalOngevaccineerden() > 0){
        return true;
    }
    return false;
}

int Hub::aantalOngevaccineerden() {
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van aantalOngevaccineerden");
    int ongevaccineerden = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        ongevaccineerden += it->second->aantalOngevaccineerden();
    }
    return ongevaccineerden;
}

int Hub::getLevering() {
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van getLevering");
    return levering;
}

bool Hub::completelyInitialized() const {
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van completelyInitialized");
    bool out = true;
    if (aantal_vaccins<0||levering<0||interval<0||transport<0){
        out = false;
    }
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        if (!it->second->completelyInitialized()){
            out = false;
        }
    }
    return out;
}

void Hub::setAantalVaccins(int aantal_vaccins1) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van setAantalVaccins");
    REQUIRE(aantal_vaccins>=0, "aantal vaccins kan niet kleiner zijn dan 0");
    aantal_vaccins = aantal_vaccins1;
}

void Hub::clear() {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitializeerd bij oproep van clear");
    this->setInterval(0);
    this->setTransport(0);
    this->setLevering(0);
    this->setAantalVaccins(0);
    vaccinatiecentra.clear();
    ENSURE(getTransport() == 0,"Transport was niet 0 op het einde van clear");
    ENSURE(getLevering() == 0,"Levering was niet 0 op het einde van clear");
    ENSURE(getInterval() == 0,"Interval was niet 0 op het einde van clear");
    ENSURE(getAantalVaccins() == 0,"Aantal vaccins was niet 0 op het einde van clear");
}



