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

const std::map<std::string, Vaccinatiecentrum *> &Hub::getVaccinatiecentra() const {
    return vaccinatiecentra;
}

void Hub::outputHub(std::ostream& out) const {
    REQUIRE(this->correctlyInitialized(), "foutieve hub");
    out << "Hub (" << this->levering <<" vaccins)"<< std::endl;
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
            it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << "\t-> " << it->first <<" ("<< centrum->getAantalVaccins() << " vaccins)"<<std::endl;
    }
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
         it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << it->first <<": "<< centrum->getAantalGevaccineerden() << " gevaccineerd"<< ", nog " <<
                centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd" <<std::endl;
    }
}

void Hub::transportToCentra() {
    transportToCentra(std::cout);
}

void Hub::transportToCentra(std::ostream& out) {
    Vaccinatiecentrum* centrum;
    int aantal_ladingen = 0;
    int tot_lading = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        centrum = it->second;
        while (centrum->getCapaciteit() > tot_lading){
            tot_lading += this->transport;
            aantal_ladingen++;
        }
        if (tot_lading >= 2*centrum->getAantalVaccins() ){
            std::cerr << "2* capaciteit overeschreven " << std::endl;
            return;
        }
        if (tot_lading <= this->levering){
            centrum->addVaccins(tot_lading);
            this->substractVaccins(tot_lading);
            out << "Er werden " << aantal_ladingen << " (" << tot_lading <<" vaccins) getransporteerd naar " <<
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

void Hub::vaccineren() {
    vaccineren(std::cout);
}

void Hub::vaccineren(std::ostream out) {
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        it->second->vaccineren(out);
    }
}

int Hub::getAantalVaccins() const {
    return aantal_vaccins;
}

void Hub::setAantalVaccins(int levering1) {
    Hub::aantal_vaccins = levering1;
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

void Hub::setVaccinatiecentra(const std::vector<Vaccinatiecentrum *> &vaccinatiecentra1) {
    for (unsigned int i = 0; i<vaccinatiecentra1.size();i++ ){
        Vaccinatiecentrum* centrum = vaccinatiecentra1[i];
        vaccinatiecentra[centrum->getNaamCentrum()] = centrum;
    }
}

void Hub::addcentrum(Vaccinatiecentrum *vaccinatiecentrum) {
    vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;
}

Hub::Hub() {
    aantal_vaccins = 0;
}

int Hub::getLevering() const {
    return levering;
}

void Hub::setLevering(int levering1) {
    Hub::levering = levering1;
}

