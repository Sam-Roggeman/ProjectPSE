//
// Created by User on 1/03/2021.
//

#include "Vaccinatiecentrum.h"

Vaccinatiecentrum::Vaccinatiecentrum() {
    _initCheck = this;
    aantal_vaccins = 0;
    aantal_gevaccineerden = 0;
    naam_centrum = "";
    adres_centrum = "";
    aantal_inwoners = 0;
    capaciteit= 0;
}


bool Vaccinatiecentrum::correctlyInitialized() const {
    return this == _initCheck;
}

//bool Vaccinatiecentrum::correctlyInitialized() const {
//    if (this->getCapaciteit()<0){
//        std::cerr << "capaciteit 0\n";
//        return false;
//    }
//    else if (this->getAdresCentrum().empty()){
//        std::cerr << "leeg adres \n";
//        return false;
//    }
//    else if (this->getAantalInwoners()<0) {
//        std::cerr << "aantal inwoners <= 0\n";
//        return false;
//    }
//    else if (this->getNaamCentrum().empty()){
//        std::cerr << "lege naam \n";
//        return false;
//    }
//    return true;
//}

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

//void Vaccinatiecentrum::vaccineren() {
//    vaccineren(std::cout);
//}

void Vaccinatiecentrum::vaccineren() {
    int ongevaccineerden = this->aantalOngevaccineerden();
    int kleinste = std::min(aantal_vaccins, capaciteit);
    int aantal_nieuwe_gevaccineerden = std::min(kleinste,ongevaccineerden);
    this->substractVaccins(aantal_nieuwe_gevaccineerden);
    this->addGevaccineerden(aantal_nieuwe_gevaccineerden);

    std::cout << "Er werden " << aantal_nieuwe_gevaccineerden <<" inwoners gevaccineerd in " <<
            this->naam_centrum << "." << std::endl;

}

void Vaccinatiecentrum::substractVaccins(int aantal) {
    this->aantal_vaccins -= aantal;
}

int Vaccinatiecentrum::getAantalInwoners() const {
    return aantal_inwoners;
}

void Vaccinatiecentrum::setAantalInwoners(int aantalInwoners) {
    aantal_inwoners = aantalInwoners;
}

int Vaccinatiecentrum::getCapaciteit() const {
    return capaciteit;
}

void Vaccinatiecentrum::setCapaciteit(int capaciteit1) {
    Vaccinatiecentrum::capaciteit = capaciteit1;
}

const std::string &Vaccinatiecentrum::getNaamCentrum() const {
    return naam_centrum;
}

void Vaccinatiecentrum::setNaamCentrum(const std::string &naamcentrum) {
    naam_centrum = naamcentrum;
}

void Vaccinatiecentrum::setAdresCentrum(const std::string &adrescentrum) {
    adres_centrum = adrescentrum;
}

const std::string &Vaccinatiecentrum::getAdresCentrum() const {
    return adres_centrum;
}



