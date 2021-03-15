//============================================================================
// Name        : Hub.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Hub simulation in C++, Ansi-style
//============================================================================

#include "Hub.h"

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
    REQUIRE(vaccins >= 0, "substractVaccins accepteerd geen negatieve getallen");
    this->aantal_vaccins -= vaccins;
    ENSURE(aantal_vaccins >= 0, "aantal overgebleven vaccins is minder dan 0");
}

bool Hub::isLeveringsDag(int dag) {
    REQUIRE(dag >= 0, "dag kan geen negatieve getal zijn");
    if (dag % (interval+1) == 0)
        return true;
    else
        return false;
}

void Hub::leveringToHub() {
    int old = aantal_vaccins;
    aantal_vaccins += levering;
    ENSURE(old == aantal_vaccins - levering, ""); //TODO
}

void Hub::vaccineren() {
    vaccineren(std::cout);
}

void Hub::vaccineren(std::ostream &out) {
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        it->second->vaccineren(out);
    }
}

int Hub::getAantalVaccins() const {
    return aantal_vaccins;
}

int Hub::getInterval() const {
    return interval;
}

void Hub::setInterval(int interval1) {
    Hub::interval = interval1;
}

int Hub::getTransport() const {
    return transport;
}

void Hub::setTransport(int transport1) {
    Hub::transport = transport1;
}


void Hub::addcentrum(Vaccinatiecentrum *vaccinatiecentrum) {
    vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;
}

Hub::Hub() {
    _initCheck = this;
    this->interval = 0;
    this->levering = 0;
    this->transport = 0;
    aantal_vaccins = 0;
}

void Hub::setLevering(int levering1) {
    Hub::levering = levering1;
}

bool Hub::notDone(){
    if (this->aantalOngevaccineerden() > 0){
        return true;
    }
    return false;
}

int Hub::aantalOngevaccineerden() {
    int ongevaccineerden = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        ongevaccineerden += it->second->aantalOngevaccineerden();
    }
    return ongevaccineerden;
}

int Hub::getLevering() {
    return levering;
}



