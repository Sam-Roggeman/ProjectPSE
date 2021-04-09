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
    ENSURE(this->correctlyInitialized(),
           "Het hub object was niet goed geinitializeerd bij het einde van de constructor");
    ENSURE(this->types.size() == 0, "De map types is niet correct geinitialiseerd");
    ENSURE(this->vaccinatiecentra.size() == 0, "De map types is niet correct geinitialiseerd");
}

bool Hub::correctlyInitialized() const {
    bool out = true;
    if (this != _initCheck){
        return false;
    }
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        if (!it->second->correctlyInitialized()){
            return false;
        }
    }
    for (std::map<std::string, VaccinType*>::const_iterator it = types.begin(); it != types.end() ;it++) {
        if (!it->second->correctlyInitialized()){
            return false;
        }
    }
    return true;
}

//todo output hub
//void Hub::outputHub() const {
//    outputHub(std::cout);
//}

//todo output hub
//void Hub::outputHub(std::ostream& out) const {
//    REQUIRE(this->correctlyInitialized(), "foutieve hub");
//    out << "Hub (" << this->aantal_vaccins <<" vaccins)"<< std::endl;
//    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
//            it != this->vaccinatiecentra.end(); it++){
//        Vaccinatiecentrum* centrum = it->second;
//        out << "\t-> " << centrum->getNaamCentrum() <<" ("<< centrum->getAantalVaccinsVanType() << " vaccins)"<<std::endl;
//    }
//    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
//         it != this->vaccinatiecentra.end(); it++){
//        Vaccinatiecentrum* centrum = it->second;
//        out << centrum->getNaamCentrum() <<": "<< centrum->getAantalGevaccineerden() << " gevaccineerd"<< ", nog " <<
//                centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd" <<std::endl;
//    }
//}

void Hub::transportToCentra(std::string naam_type) {
    transportToCentra(naam_type, std::cout);
}

void Hub::transportToCentra(std::string naam_type, std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "Hub is niet geinitializeerd bij oproep van transportToCentra");
    Vaccinatiecentrum* centrum;
    VaccinType* type = this->types[naam_type];
    int aantal_ladingen;
    int tot_lading;
    int aantal_vaccins_hub_start = types[naam_type]->getAantalVaccins();
    int aantal_vaccins_centrum_start;

    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        aantal_ladingen = 0;
        tot_lading = 0;
        centrum = it->second;
        aantal_vaccins_centrum_start = centrum->getAantalVaccinsVanType(std::string());
        while (centrum->getCapaciteit() > tot_lading + centrum->getAantalVaccinsVanType(std::string())){
            tot_lading += types[naam_type]->getTransport();
            aantal_ladingen++;
        }
        ENSURE(tot_lading > 2*centrum->getCapaciteit(), "2* capaciteit overeschreven van centrum overschreven");
        if (tot_lading <= types[naam_type]->getAantalVaccins()){
            centrum->addVaccins(tot_lading, std::string());
            type->substractVaccins(tot_lading);
            out << "Er werden " << aantal_ladingen << " ladingen (" << tot_lading <<" vaccins) getransporteerd naar " <<
                centrum->getNaamCentrum() << "." << std::endl;
        }
        ENSURE(centrum->getAantalVaccinsVanType(std::string()) >= aantal_vaccins_centrum_start, "Aantal vaccins in centrum is gezakt na transport naar centra");
    }
    ENSURE(type->getAantalVaccins()<=aantal_vaccins_hub_start, "Aantal vaccins in hub gestegen na transport naar centra");
}

void Hub::vaccineren() {
    vaccineren(std::cout);
}

void Hub::vaccineren(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van vaccineren");
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        Vaccinatiecentrum* centrum = it->second;
        int aantal_vaccins_start = centrum->getAantalVaccinsVanType(std::string());
        int gevaccineerden = centrum->getAantalGevaccineerden();
        centrum->vaccineren(std::string(), out);
        ENSURE(centrum->getAantalVaccinsVanType(std::string()) <= aantal_vaccins_start, "Aantal vaccins is gestegen na vaccineren" );
        ENSURE(centrum->getAantalGevaccineerden() >= gevaccineerden, "Gevaccineerden is gezakt na vaccineren" );
    }
}

void Hub::addcentrum(Vaccinatiecentrum * const vaccinatiecentrum) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van addcentrum");
    REQUIRE(vaccinatiecentrum->correctlyInitialized(),
            "Het vaccinatiecentrum object was niet geinitializeerd oproeping van addcentrum");
    REQUIRE(vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end(),
            "Naam van centrum komt al voor in de lijst van centra bij oproep van addcentrum");
    unsigned int s1 = this->vaccinatiecentra.size();
    vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;

    ENSURE(vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) != vaccinatiecentra.end(),
            "Naam van centrum komt niet voor in centra op het einde van addcentrum");
    ENSURE(s1+1 == this->vaccinatiecentra.size(),"lijst met vaccinatiecentra is niet verhoogd");
}


bool Hub::notDone()const{
    REQUIRE(this->correctlyInitialized(),"De hub was niet geinitializeerd bij oproep van notDone");
    if (this->aantalOngevaccineerden() > 0){
        return true;
    }
    return false;
}

int Hub::aantalOngevaccineerden() const{
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van aantalOngevaccineerden");
    int ongevaccineerden = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        ongevaccineerden += it->second->aantalOngevaccineerden();
    }
    return ongevaccineerden;
}


bool Hub::completelyInitialized() const {
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van completelyInitialized");
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        if (!it->second->completelyInitialized()){
            return false;
        }
    }
    for (std::map<std::string, VaccinType*>::const_iterator it =types.begin(); it != types.end() ;it++) {
        if (!it->second->completelyInitialized()){
            return false;
        }
    }
    return true;
}

void Hub::clear() {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitializeerd bij oproep van clear");
    types.clear();
    vaccinatiecentra.clear();
    ENSURE(vaccinatiecentra.size() == 0, "vaccinatiecentra niet leeg na clear van hub");
    ENSURE(types.size() == 0, "types niet leeg na clear van hub");
}

void Hub::addType(VaccinType *type) {
    REQUIRE(type->correctlyInitialized(), "Het object Vaccintype is niet correct geinitialiseerd");
    REQUIRE(type->completelyInitialized(), "Het object Vaccintype is niet juist geinitialiseerd");
    REQUIRE(this->types.find(type->getName()) == this->types.end(), "Er bestaat al een vaccintype met dezelfde naam");
    int startsize = types.size();
    types[type->getName()]=type;
    ENSURE(this->types.find(type->getName()) != this->types.end(), "Het Vaccintype is niet juist toegevoegd aan de types map");
    ENSURE(this->types.size() == startsize + 1, "Er is geen Vaccintype toegevoegd aan de map types na addType");
}



