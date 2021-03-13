//
// Created by said2 on 1-3-2021.
//

#include "Hub.h"

bool Hub::correctlyInitialized() const {
    if (vaccinatiecentra.empty()) return false;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        if (! it->second->correctlyInitialized()){
            return false;
        }
    }
    if (this->getInterval() < 0 || this->getAantalVaccins() < 0 || this->getTransport() < 0){
        std::cerr << "levering, interval of transport < 0";
        return false;
    }
    return true;
}



void Hub::outputHub() const {
    REQUIRE(this->correctlyInitialized(), "foutieve hub");
    std::cout << "Hub (" << this->levering <<" vaccins)"<< std::endl;
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
            it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        std::cout << "\t-> " << it->first <<" ("<< centrum->getAantalVaccins() << " vaccins)"<<std::endl;
    }
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
         it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        std::cout << it->first <<": "<< centrum->getAantalGevaccineerden() << " gevaccineerd"<< ", nog " <<
                centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd" <<std::endl;
    }
}

//void Hub::transportToCentra() {
//    transportToCentra(std::cout);
//}

void Hub::transportToCentra() {
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
        if (tot_lading <= this->levering){
            centrum->addVaccins(tot_lading);
            this->substractVaccins(tot_lading);
            std::cout << "Er werden " << aantal_ladingen << " (" << tot_lading <<" vaccins) getransporteerd naar " <<
                    centrum->getNaamCentrum() << "." << std::endl;
        }
        else {
            std::cerr << "te weinig vaccins in de hub" << std::endl;
            return;
        }
    }
}

void Hub::substractVaccins(int vaccins) {
    this->aantal_vaccins -= vaccins;
}

bool Hub::isLeveringsDag(int dag) {
    if (dag % (interval+1) == 0)
        return true;
    else
        return false;
}

void Hub::leveringToHub() {
    aantal_vaccins += levering;
}

//void Hub::vaccineren() {
//    vaccineren(std::cout);
//}

void Hub::vaccineren() {
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        it->second->vaccineren();
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
    aantal_vaccins = 0;
}

void Hub::setLevering(int levering1) {
    Hub::levering = levering1;
}

