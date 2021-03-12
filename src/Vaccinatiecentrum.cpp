//
// Created by User on 1/03/2021.
//

#include "Vaccinatiecentrum.h"

Vaccinatiecentrum::Vaccinatiecentrum() {
    aantal_vaccins = 0;
    aantal_gevaccineerden = 0;
}

bool Vaccinatiecentrum::correctlyInitialized() const {
    if (this->getCapaciteit()<0){
        std::cerr << "capaciteit 0\n";
        return false;
    }
    else if (this->getAdresCentrum().empty()){
        std::cerr << "leeg adres \n";
        return false;
    }
    else if (this->getAantalInwoners()<0) {
        std::cerr << "aantal inwoners <= 0\n";
        return false;
    }
    else if (this->getNaamCentrum().empty()){
        std::cerr << "lege naam \n";
        return false;
    }
    return true;
}

int Vaccinatiecentrum::getAantalVaccins() const {
    return aantal_vaccins;
}

void Vaccinatiecentrum::addVaccins(int aantalVaccins) {
    aantal_vaccins += aantalVaccins;
}

int Vaccinatiecentrum::getAantalGevaccineerden() const {
    return aantal_gevaccineerden;
}

void Vaccinatiecentrum::addGevaccineerden(int aantal_gevaccineerden1) {
    aantal_gevaccineerden += aantal_gevaccineerden1;
}

int Vaccinatiecentrum::aantalOngevaccineerden() const {
    return aantal_inwoners-aantal_gevaccineerden;
}

void Vaccinatiecentrum::vaccineren() {
    vaccineren(std::cout);
}

void Vaccinatiecentrum::vaccineren(std::ostream& out) {
    int ongevaccineerden = this->aantalOngevaccineerden();
    int aantal_nieuwe_gevaccineerden = std::min(aantal_vaccins, capaciteit, ongevaccineerden);
    this->substractVaccins(aantal_nieuwe_gevaccineerden);
    this->addGevaccineerden(aantal_nieuwe_gevaccineerden);

    out << "Er werden " << aantal_nieuwe_gevaccineerden <<" inwoners gevaccineerd in " <<
            this->naam_centrum << "." << std::endl;

}

void Vaccinatiecentrum::substractVaccins(int aantal) {
    this->aantal_vaccins -= aantal;
}



