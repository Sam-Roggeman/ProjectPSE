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

void Hub::outputHub() const {
    outputHub(std::cout);
}

void Hub::outputHub(std::ostream& out) const {
    REQUIRE(this->correctlyInitialized(), "foutieve hub");

    out << "Hub (" << this->get_aantal_vac() <<" vaccins)"<< std::endl;
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin(); it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << "\t-> " << centrum->getNaamCentrum() << " (" << centrum->getAantalVaccins() << " vaccins)" << std::endl;
    }
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
         it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << centrum->getNaamCentrum() <<": "<< centrum->getAantalGevaccineerden() << " gevaccineerd"<< ", nog " <<
            centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd" <<std::endl;
    }
}

void Hub::transportToCentra(int dag) {
    transportToCentra(dag, std::cout);
}

void Hub::transportToCentra(int dag, std::ostream &out) {
    if (dag == 15) {
        std::cout<<"REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
    }

    REQUIRE(this->correctlyInitialized(), "Hub is niet geinitializeerd bij oproep van transportToCentra");
    Vaccinatiecentrum* centrum;
    int aantal_ladingen;
    std::map<std::string, int> tot_lading_per_type;
    int tot_lading;
    int aantal_vaccins_hub_start = this->get_aantal_vac(); ;
    int aantal_vaccins_centrum_start;
    int aantal_ger = getAantalGer();
    int volg_leveringsdag = this->nextLevDag(dag);
    int tot_lading_per_dag_centrum;
    int max_cap_volg_levering = 0;
    int aantal_vac = this->get_aantal_vac();
    bool not_cap = false;
    bool cap = false;
    bool two_cap = false;
    double perc;
    for(std::map<std::string,Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end(); it++){
        max_cap_volg_levering += it->second->getCapaciteit() * (volg_leveringsdag);
    }
    if((aantal_vac- aantal_ger)< max_cap_volg_levering){
        tot_lading_per_dag = (aantal_vac-aantal_ger)/(volg_leveringsdag);
        not_cap = true;
    }
    else if ((aantal_vac-aantal_ger) < 2*max_cap_volg_levering){
        tot_lading_per_dag = (aantal_vac-aantal_ger)/(volg_leveringsdag);
        cap =true;
    }
    else {
        two_cap = true;
    }
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        if (not_cap||cap) {
            perc =  ((double) (it->second->getCapaciteit()) / (double) max_cap_volg_levering);
            tot_lading_per_dag_centrum = round((double) tot_lading_per_dag * perc);
        }
        centrum = it->second;
        aantal_vaccins_centrum_start = centrum->getAantalVaccins();
        tot_lading_per_type.clear();
        tot_lading = 0;
        aantal_ladingen = 0;
        for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
            aantal_ger = centrum->getAantalGeres(type_it->first,dag);
            while (aantal_ger > tot_lading_per_type[type_it->first]) {
                tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                tot_lading += type_it->second->getTransport();
                aantal_ladingen++;
            }
        }
        for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
            //warme temperaturen
            if (type_it->second->gettemperatuur() >= 0) {
                while (((centrum->getCapaciteit() > tot_lading + centrum->getAantalVaccins())&&(two_cap) )||
                        (tot_lading<tot_lading_per_dag_centrum&&(not_cap||cap)) ){
                    if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
                        break;
                    }
                    if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
                        tot_lading_per_type[type_it->first] +type_it->second->getTransport() ){
                        break;
                    }
                    tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                    tot_lading += type_it->second->getTransport();
                    aantal_ladingen++;
                }
            }
                //gekoelde vaccins
            else {
                if (centrum->getCapaciteit() < tot_lading + centrum->getAantalVaccins()) {
                    break;
                }
                while (((centrum->getCapaciteit() >= tot_lading + centrum->getAantalVaccins() )&&(two_cap) )||
                (tot_lading<tot_lading_per_dag_centrum&&(not_cap||cap))) {
                    if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
                        break;
                    }
                    if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
                        tot_lading_per_type[type_it->first] +type_it->second->getTransport()){
                        break;
                    }
                    tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                    tot_lading += type_it->second->getTransport();
                    aantal_ladingen++;
                }
                if (centrum->getCapaciteit() < tot_lading + centrum->getAantalVaccins()){
                    aantal_ladingen -= 1;
                    tot_lading -= type_it->second->getTransport();
                    tot_lading_per_type[type_it->first] -= types[type_it->first]->getTransport();
                }
            }
        }
        ENSURE(tot_lading <= 2 * centrum->getCapaciteit(), "2* capaciteit overeschreven van centrum overschreven");
        for (std::map<std::string, int>::iterator ite = tot_lading_per_type.begin(); ite != tot_lading_per_type.end(); ite++) {
            centrum->addVaccins(ite->second, ite->first);
            this->types[ite->first]->substractVaccins((ite->second));
        }
        out << "Er werden " << aantal_ladingen << " ladingen (" << tot_lading << " vaccins) getransporteerd naar " <<
            centrum->getNaamCentrum() << "." << std::endl;
        ENSURE(centrum->getAantalVaccins() >= aantal_vaccins_centrum_start, "Aantal vaccins in centrum is gezakt na transport naar centra");
    }
    ENSURE(this->get_aantal_vac() <= aantal_vaccins_hub_start, "Aantal vaccins in hub gestegen na transport naar centra");
}

void Hub::vaccineren(int dag) {
    vaccineren(dag, std::cout);
}

void Hub::vaccineren(int dag, std::ostream &out) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van vaccineren");
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        Vaccinatiecentrum* centrum = it->second;
        int aantal_vaccins_start = centrum->getAantalVaccins();
        int gevaccineerden = centrum->getAantalGevaccineerden()+centrum->getAantalVolGevaccineerden();
        centrum->vaccineren(dag, out);
        ENSURE(centrum->getAantalVaccins() <= aantal_vaccins_start, "Aantal vaccins is gestegen na vaccineren" );
        ENSURE((centrum->getAantalGevaccineerden()+centrum->getAantalVolGevaccineerden()) >= gevaccineerden, "Gevaccineerden is gezakt na vaccineren" );
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
    unsigned int startsize = types.size();
    types[type->getName()]=type;
    ENSURE(this->types.find(type->getName()) != this->types.end(), "Het Vaccintype is niet juist toegevoegd aan de types map");
    ENSURE(this->types.size() == startsize + 1, "Er is geen Vaccintype toegevoegd aan de map types na addType");
}

int Hub::get_aantal_vac() const {
    REQUIRE(this->correctlyInitialized(), "Hub is verkeerd geinitialiseerd");
    int aantal_vac = 0;
    for(std::map<std::string,VaccinType*>::const_iterator it = types.begin(); it != types.end(); it++){
        aantal_vac += it->second->getAantalVaccins();
    }
    return aantal_vac;
}

void Hub::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "Hub was niet correct geinitializeerd bij oproep van impressie");
    REQUIRE(this->completelyInitialized(), "Hub was niet compleet geinitializeerd bij oproep van impressie");
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        it->second->impressie(out);
    }
}

void Hub::setCentrumTypes() const  {
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin(); it != this->vaccinatiecentra.end(); it++){
        it->second->setTypes(this->types);
    }
}

void Hub::vacLeveringen(int dag) {
    for (std::map<std::string,VaccinType*>::iterator type_it = types.begin(); type_it!=types.end();type_it++){
        if (type_it->second->isLeveringsDag(dag)){
            type_it->second->leveringVanTypeToHub();
        }
    }
}

int Hub::nextLevDag(int dag) {
    int min = std::numeric_limits<int>::max();
    int next;
    for (std::map<std::string, VaccinType *>::iterator type_it = types.begin(); type_it != types.end(); type_it++) {
        next = type_it->second->nextLeveringsDag(dag);
        if ((min > next)&&next !=0){
            min = next;
        }
    }
    return min;
}

int Hub::getAantalGer() {
    int ger = 0;
    for (std::map<std::string, VaccinType *>::iterator type_it = types.begin(); type_it != types.end(); type_it++) {
        ger += type_it->second->getGereserveerd();
    }
    return ger;
}





