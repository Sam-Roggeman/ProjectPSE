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
    if (this != this->_initCheck){
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
        out << centrum->getNaamCentrum() <<": "<<centrum->getAantalVolGevaccineerden() <<" inwoners volledig gevaccineerd, "<< centrum->getAantalGevaccineerden() << " enkel gevaccineerd"<< ", nog " <<
            centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd"<<std::endl;
    }
}

void Hub::transportToCentra(int dag) {
    transportToCentra(dag, std::cout);
}


void Hub::transportToCentra(int dag, std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "Hub is niet geinitializeerd bij oproep van transportToCentra");
    Vaccinatiecentrum* centrum;
    int aantal_ladingen;
    std::map<std::string, int> tot_lading_per_type;
    int tot_lading;
    int aantal_vaccins_hub_start = this->get_aantal_vac(); ;
    int aantal_vaccins_centrum_start ;
    int aantal_ger;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        centrum = it->second;
        aantal_vaccins_centrum_start = centrum->getAantalVaccins();
        tot_lading_per_type.clear();
        tot_lading = 0;
        aantal_ladingen = 0;
        for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
            centrum = it->second;
            aantal_ger = centrum->getAantalGeres(type_it->first,dag);
            while (aantal_ger > tot_lading_per_type[type_it->first]) {
                tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                tot_lading += type_it->second->getTransport();
                aantal_ladingen++;
            }
            //warme temperaturen
            if (type_it->second->gettemperatuur() >= 0) {
                while (centrum->getCapaciteit() > tot_lading + centrum->getAantalVaccins()) {
                    if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
                        break;
                    }
                    if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
                        tot_lading_per_type[type_it->first] ){
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
                while (centrum->getCapaciteit() >= tot_lading + centrum->getAantalVaccins()) {

                    if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
                        break;
                    }
                    if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
                        tot_lading_per_type[type_it->first] ){
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
            if(ite->second < 0){
                std::cout << "hi";
            }
            centrum->addVaccins(ite->second, ite->first);
            this->types[ite->first]->substractVaccins((ite->second));
        }
        out << "Er werden " << aantal_ladingen << " ladingen (" << tot_lading << " vaccins) getransporteerd naar " <<
            centrum->getNaamCentrum() << "." << std::endl;
        ENSURE(centrum->getAantalVaccins() >= aantal_vaccins_centrum_start, "Aantal vaccins in centrum is gezakt na transport naar centra");
    }
    ENSURE(this->get_aantal_vac() <= aantal_vaccins_hub_start, "Aantal vaccins in hub gestegen na transport naar centra");
}



void Hub::transportToCentrafucked(int dag, std::ostream &out) {
    for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
        if (type_it->second->aantalNietGer()< 0 ){
            std::cout<<"";
        }
    }
        if (dag == 14){
       std::cout<<"";
    }
    REQUIRE(this->correctlyInitialized(), "Hub is niet geinitializeerd bij oproep van transportToCentra");
    Vaccinatiecentrum* centrum;
    int aantal_ladingen;
    std::map<std::string, int> tot_lading_per_type;
    int tot_lading;
    int aantal_vaccins_hub_start = this->get_aantal_vac(); ;
    int aantal_vaccins_centrum_start;
    int volg_leveringsdag = this->nextLevDag(dag);
//    int tot_lading_per_dag_centrum;
    double max_cap_volg_levering = 0;
    double vac_tot_volg_levering = 0;
    double max_cap_algemeen = 0;
    double max_cap_cap_slimme_verdeling = 0;
    bool niet_genoeg = false;
    std::map<std::string,double> centra_trans;
    std::map<std::string,double> vaccin_trans;
    int tl;
    //    int aantal_vac = this->get_aantal_vac();
//    int tot_lading_per_dag;
//    bool not_cap = false;
//    bool cap = false;
//    bool two_cap = false;
//    double perc;
    for(std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++){
        vac_tot_volg_levering += type_it->second->aantalNietGer();
    }
    for(std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++){
        vaccin_trans[type_it->second->getName()] = type_it->second->getAantalVaccins()/volg_leveringsdag;
    }
    for(std::map<std::string,Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end(); it++){
        max_cap_volg_levering += it->second->getCapaciteit() * (volg_leveringsdag);
        max_cap_algemeen += it->second->getCapaciteit();
    }
    if(get_aantal_vac() < max_cap_volg_levering){
        niet_genoeg = true;
    }

    if(niet_genoeg){
        double vac_per_dag = vac_tot_volg_levering/volg_leveringsdag;
        for(std::map<std::string,Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end(); it++){
            centra_trans[it->second->getNaamCentrum()] = ((double)it->second->getCapaciteit()/(double)max_cap_algemeen) * (double)vac_per_dag;
        }
        for(std::map<std::string,double>::const_iterator it = centra_trans.begin(); it != centra_trans.end();it++){
            max_cap_cap_slimme_verdeling += it->second;
        }
    }
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
        centrum = it->second;
        aantal_vaccins_centrum_start = centrum->getAantalVaccins();
        tot_lading_per_type.clear();
        tot_lading = 0;
        aantal_ladingen = 0;
        //hernieuwingen
        for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
            tl = 0;
            while (centrum->getAantalGeres(type_it->first,dag) > tot_lading_per_type[type_it->first]) {
                tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                tot_lading += type_it->second->getTransport();
                aantal_ladingen++;
                tl += type_it->second->getTransport();
            }
            type_it->second->setGereserveerd(type_it->second->getGereserveerd()-tl);
            centrum->addVaccins(tl, type_it->first);
            this->types[type_it->first]->substractVaccins((tl));
        }
        if(!niet_genoeg){
            for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
                tl = 0;
                //warme temperaturen
                if (type_it->second->gettemperatuur() >= 0) {
                    while (((centrum->getCapaciteit() > tot_lading + centrum->getAantalVaccins()+
                    centrum->getAantalHernieuwing(dag+type_it->second->gethernieuwing())))){
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
                        tl += type_it->second->getTransport();
                    }
                }
                    //gekoelde vaccins
                else {
                    if (centrum->getCapaciteit() < tot_lading + centrum->getAantalVaccins()) {
                        break;
                    }
                    while (((centrum->getCapaciteit() >= tot_lading + centrum->getAantalVaccins() +
                    centrum->getAantalHernieuwing(dag+type_it->second->gethernieuwing())))) {
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
                        tl +=type_it->second->getTransport();
                    }
//                    if (centrum->getCapaciteit() < tot_lading + centrum->getAantalVaccins()){
//                        aantal_ladingen -= 1;
//                        tot_lading -= type_it->second->getTransport();
//                        tot_lading_per_type[type_it->first] -= types[type_it->first]->getTransport();
//                    }
                }
//                type_it->second->setVooradVoorHern(type_it->second->getVooradVoorHern()+tl);
                centrum->addVaccins(tl, type_it->first);
                type_it->second->setGereserveerd(type_it->second->getGereserveerd()+tl);
                this->types[type_it->first]->substractVaccins((tl));
            }
        }
        else{
            for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
                tl = 0;
                double lad = ((double)centra_trans[centrum->getNaamCentrum()]/(double)max_cap_cap_slimme_verdeling) * (double)vaccin_trans[type_it->second->getName()];
                lad /=2;
                while ((lad > tl + centrum->getAantalVaccinsVanType(type_it->first)+type_it->second->getTransport()+
                centrum->getAantalHernieuwing(dag+type_it->second->gethernieuwing()))&&!
                (type_it->second->gettemperatuur()<=0 && (tl+type_it->second->getTransport()) > centrum->getCapaciteit())){
                    if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
                        break;
                    }
                    if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
                        tot_lading_per_type[type_it->first] +type_it->second->getTransport()){
                        break;
                    }
                    tot_lading += type_it->second->getTransport();
                    tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
                    tl += type_it->second->getTransport();
                    aantal_ladingen++;
//                    type_it->second->setVooradVoorHern(type_it->second->getVooradVoorHern()+tl);
                }
                centrum->addVaccins(tl, type_it->first);
                type_it->second->setGereserveerd(type_it->second->getGereserveerd()+tl);
                this->types[type_it->first]->substractVaccins((tl));
//                centrum->addVaccins(tl,type_it->second->getName());
            }
//            for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
//                aantal_ger = centrum->getAantalGeres(type_it->first,dag);
//                while (aantal_ger > tot_lading_per_type[type_it->first]) {
//                    tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
//                    tot_lading += type_it->second->getTransport();
//                    aantal_ladingen++;
//                }
//            }
//            for (std::map<std::string, VaccinType*>::const_iterator type_it = types.begin(); type_it != types.end(); type_it++) {
//                //warme temperaturen
//                if (type_it->second->gettemperatuur() >= 0) {
//                    while (((centra_trans[centrum->getNaamCentrum()] > tot_lading + centrum->getAantalVaccins()))){
//                        if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
//                            break;
//                        }
//                        if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
//                            tot_lading_per_type[type_it->first] +type_it->second->getTransport() ){
//                            break;
//                        }
//                        tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
//                        tot_lading += type_it->second->getTransport();
//                        aantal_ladingen++;
//                    }
//                }
//                    //gekoelde vaccins
//                else {
//                    if (centrum->getCapaciteit() < tot_lading + centrum->getAantalVaccins()) {
//                        break;
//                    }
//                    while (((centra_trans[centrum->getNaamCentrum()] >= tot_lading + centrum->getAantalVaccins() ))) {
//                        if (type_it->second->getAantalVaccins() < type_it->second->getTransport()) {
//                            break;
//                        }
//                        if (types[type_it->first]->getAantalVaccins() - type_it->second->getGereserveerd() <=
//                            tot_lading_per_type[type_it->first] +type_it->second->getTransport()){
//                            break;
//                        }
//                        tot_lading_per_type[type_it->first] += types[type_it->first]->getTransport();
//                        tot_lading += type_it->second->getTransport();
//                        aantal_ladingen++;
//                    }
//                    if (centra_trans[centrum->getNaamCentrum()] < tot_lading + centrum->getAantalVaccins()&&
//                    tot_lading_per_type[type_it->second->getName()] != 0){
//                        aantal_ladingen -= 1;
//                        tot_lading -= type_it->second->getTransport();
//                        tot_lading_per_type[type_it->first] -= types[type_it->first]->getTransport();
//                    }
//                }
//            }
        }
        ENSURE(tot_lading <= 2 * centrum->getCapaciteit(), "2* capaciteit overeschreven van centrum overschreven");
//        for (std::map<std::string, int>::iterator ite = tot_lading_per_type.begin(); ite != tot_lading_per_type.end(); ite++) {
//
//        }
        out << "Er werden " << aantal_ladingen << " ladingen (" << tot_lading << " vaccins) getransporteerd naar " <<
            centrum->getNaamCentrum() << "." << std::endl;
        ENSURE(centrum->getAantalVaccins() >= aantal_vaccins_centrum_start, "Aantal vaccins in centrum is gezakt na transport naar centra");
    }
    ENSURE(this->get_aantal_vac() <= aantal_vaccins_hub_start, "Aantal vaccins in hub gestegen na transport naar centra");
}

void Hub::transportToCentra2(int dag, std::ostream &out){
    std::map<int,VaccinType*> transport_sorted_types;


    //capaciteit*2 van alle centra tesamen
    double max_cap_all_cent_tot_lev = 0;
    for (std::map<std::string, VaccinType *>::iterator type_it = types.begin(); type_it != types.end(); type_it++) {
        transport_sorted_types[type_it->second->getTransport()] = type_it->second;
    }


    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin(); it != this->vaccinatiecentra.end(); it++) {
        if (it->second->aantalOngevaccineerden() > 0) {
            max_cap_all_cent_tot_lev += 2 * ((it->second->getCapaciteit()) * nextLevDag(dag));
        }
    }
    //als er meer vaccins zijn dan 2 (reserveerd +gestuurd) keer de max capaciteit
    bool genoeg_vaccins = (get_aantal_vac()-getAantalGer()>=(max_cap_all_cent_tot_lev*2));
    //aantal ladingen dat verstuurd wordt
    int aantal_ladingen;
    bool gecapped = false;
    int aantal_vac_start = get_aantal_vac();

    int totale_lading;
    Vaccinatiecentrum* centrum;
    double max_vaccins;
    VaccinType* type;
    int lading_type_centrum;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
    it != this->vaccinatiecentra.end() && aantalOnvolledigGev() > 0; it++) {
        centrum = it->second;
        max_vaccins = centrum->getCapaciteit() * 2;
        totale_lading = 0;
        aantal_ladingen = 0;
        if (!genoeg_vaccins) {
            gecapped = true;
            max_vaccins = std::min(max_vaccins, ((double) centrum->getCapaciteit() *
                                                 ((double) aantal_vac_start - (double) getAantalGer())) /
                                                (double) max_cap_all_cent_tot_lev);
        }
        //hernieuwingen
        for (std::map<int, VaccinType *>::reverse_iterator type_it = transport_sorted_types.rbegin();
             type_it != transport_sorted_types.rend(); type_it++) {
            lading_type_centrum = 0;
            type = type_it->second;
            int geres = centrum->getAantalGeres(type->getName(), dag);
//            int geres2 = geres;
            while (geres > 0) {
                totale_lading += type->getTransport();
                aantal_ladingen++;
                lading_type_centrum += type->getTransport();
                centrum->getAantalGeres(type->getName(), dag);
                geres -= type->getTransport();
            }
            if (type_it->second->gethernieuwing() > 0) {
                type->subGereserveerd(lading_type_centrum);
            }
            centrum->addVaccins(lading_type_centrum, type->getName());
            type->substractVaccins((lading_type_centrum));
        }
        if (centrum->aantalOngevaccineerden() > 0) {
            for (std::map<int, VaccinType *>::reverse_iterator type_it = transport_sorted_types.rbegin();
                 type_it != transport_sorted_types.rend(); type_it++) {
                type = type_it->second;
                lading_type_centrum = 0;
                if (type->gettemperatuur() < 0) {
                    gecapped = true;
                    max_vaccins = std::min(max_vaccins, (double) centrum->getCapaciteit()-centrum->getAantalHernieuwing(dag));
                }
                while ((//genoeg vaccins en er past nog een lading bij
                               (!gecapped && (2 * centrum->getCapaciteit() >
                                              totale_lading + centrum->getAantalVaccins() + type->getTransport()))
                               // of niet genoeg vaccins en max = max_vaccins
                               || (gecapped && (max_vaccins > totale_lading + type->getTransport()) &&
                                   2 * centrum->getCapaciteit() >
                                   totale_lading + centrum->getAantalVaccins() + type->getTransport())
                       )//en er moet genoeg van dat type vrij zijn
                       && (type->aantalNietGer() > (lading_type_centrum + type->getTransport()) * 2)
                       && (centrum->getAantalHernieuwing(type->gethernieuwing() + dag) + type->getTransport() <=
                           centrum->getCapaciteit())
                        ) {
                    lading_type_centrum += type->getTransport();
                    totale_lading += type->getTransport();
                    aantal_ladingen++;
                }
                centrum->addVaccins(lading_type_centrum, type->getName());
                if (type_it->second->gethernieuwing() > 0) {
                    type_it->second->addGereserveerd(lading_type_centrum);
                }
                type->substractVaccins((lading_type_centrum));
            }
        }

        out << "Er werden " << aantal_ladingen << " ladingen (" << totale_lading << " vaccins) getransporteerd naar " <<
            centrum->getNaamCentrum() << "." << std::endl;
//        ENSURE(centrum->getAantalVaccins() >= aantal_vaccins_centrum_start, "Aantal vaccins in centrum is gezakt na transport naar centra");
    }
//    ENSURE(this->get_aantal_vac() <= aantal_vaccins_hub_start, "Aantal vaccins in hub gestegen na transport naar centra");
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
    if (this->aantalOnvolledigGev() > 0 ){
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

int Hub::aantalOnvolledigGev() const{
    REQUIRE(this->correctlyInitialized(),"de hub was niet correct geinitalizeerd bij oproep van aantalOngevaccineerden");
    int aantal = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++) {
        aantal += it->second->getAantalInwoners() - it->second->getAantalVolGevaccineerden();
    }
    return aantal;
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



