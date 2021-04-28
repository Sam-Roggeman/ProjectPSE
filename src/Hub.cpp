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
    types.clear();
    vaccinatiecentra.clear();

    ENSURE(this->correctlyInitialized(),
           "Het hub object was niet goed geinitializeerd bij het einde van de constructor");
    ENSURE(this->types.size() == 0, "De map types is niet correct geinitialiseerd");
    ENSURE(this->vaccinatiecentra.size() == 0, "De map types is niet correct geinitialiseerd");
}

bool Hub::correctlyInitialized() const {
    //is hub correct geinitializeerd
    if (this != this->_initCheck){
        return false;
    }
    //is elk centrum correct geinitializeerd
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin()
            ; it != vaccinatiecentra.end() ;it++) {
        if (!it->second->correctlyInitialized()){
            return false;
        }
    }
    //is elk type correct geinitializeerd
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

    out << "Hub (" << this->getAantalVac() << " vaccins)" << std::endl;
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin()
            ; it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << "\t-> " << centrum->getNaamCentrum() << " (" << centrum->getAantalVaccins() << " vaccins)" << std::endl;
    }
    for (std::map<std::string,Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin();
         it != this->vaccinatiecentra.end(); it++){
        Vaccinatiecentrum* centrum = it->second;
        out << centrum->getNaamCentrum() <<": "<<centrum->getAantalVolGevaccineerden() <<
            " inwoners volledig gevaccineerd, "<< centrum->getAantalGevaccineerden() << " enkel gevaccineerd"<< ", nog "
            << centrum->aantalOngevaccineerden() <<" inwoners niet gevaccineerd"<<std::endl;
    }
}

void Hub::transportToCentra2(int dag, std::ostream &out){
    //map gesorteerd op grootte van het transport voor efficientie
    std::map<int,VaccinType*> transport_sorted_types;

    for (std::map<std::string, VaccinType *>::iterator type_it = types.begin(); type_it != types.end(); type_it++) {
        //voeg alle types toe
        transport_sorted_types[type_it->second->getTransport()] = type_it->second;
    }

    //capaciteit*2 van alle centra tesamen
    double max_cap_all_cent_tot_lev = 0;
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin()
            ; it != this->vaccinatiecentra.end(); it++) {
        if (it->second->aantalOngevaccineerden() > 0) {
            max_cap_all_cent_tot_lev += 2 * ((it->second->getCapaciteit()) * nextLevDag(dag));
        }
    }
    //als er meer vaccins zijn dan 2 (reserveerd +gestuurd) keer de max capaciteit
    bool genoeg_vaccins = (getAantalVac() - getAantalGer() >= (max_cap_all_cent_tot_lev * 2));
    //aantal ladingen dat verstuurd wordt
    int aantal_ladingen;
    //wordt er gecapped door slimme verdeling/temperatuur
    bool gecapped = false;
    //totaal aantal vaccins bij de start
    int aantal_vac_start = getAantalVac();
    //totale lading van alle types naar een centrum
    int totale_lading;
    //huidig type
    VaccinType* type;
    //huidig centrum
    Vaccinatiecentrum* centrum;
    //max aantal vaccins dat verstuurd mag worden naar een centrum indien gecapped true is
    double max_vaccins;
    //lading die verstuurd wordt van een type naar een centrum
    int lading_type_centrum;
    //aantal gekoelde vaccins dat die dag naar centrum wordt gestuurd
    int aantal_gekoeld;
    //loop over alle centra
    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin()
            ; it != this->vaccinatiecentra.end(); it++) {
        centrum = it->second;
        //als niet iedereen volledig gevaccineerd
        if (centrum->aantalOnvolledigGev() > 0) {
            //gekoeld voor het centrum vandaag is 0
            aantal_gekoeld = 0;

            totale_lading = 0;
            aantal_ladingen = 0;

            //hernieuwingen
            for (std::map<int, VaccinType *>::reverse_iterator type_it = transport_sorted_types.rbegin();
                 type_it != transport_sorted_types.rend(); type_it++) {
                lading_type_centrum = 0;
                type = type_it->second;
                int geres = centrum->getAantalGeres(type->getName(), dag);
                //transportgrootte van type
                int transport_type = type->getTransport();
                //zolang dat er meer vaccins gereserveerd zijn van type op dag => stuur ladingen
                while (geres-centrum->getAantalVaccinsVanType(type->getName()) > 0) {
                    totale_lading += transport_type;
                    aantal_ladingen++;
                    lading_type_centrum += transport_type;
                    geres -= transport_type;
                }
                //gereserveerd aftrekken
                type->subGereserveerd(lading_type_centrum);
                //toevoegen in centrum
                centrum->addVaccins(lading_type_centrum, type->getName());
                //aftrekken van hub
                type->substractVaccins((lading_type_centrum));
            }
            //als er nog mensen zijn zonder eerste prik
            if (centrum->aantalOngevaccineerden() > 0) {
                //loop over de types van groot naar klein transport
                for (std::map<int, VaccinType *>::reverse_iterator type_it = transport_sorted_types.rbegin();
                     type_it != transport_sorted_types.rend(); type_it++) {
                    type = type_it->second;
                    lading_type_centrum = 0;
                    //maximum is 2 keer de capaciteit
                    max_vaccins = centrum->getCapaciteit() * 2;
                    //als er niet genoeg vaccins zijn
                    if (!genoeg_vaccins) {
                        //is er een cap
                        gecapped = true;
                        //maximum is het min(huidige max, (aantal_vac_start-aantal_gereserveerd)
                        // *(verhouding capaciteit met maximum capaciteit tot volgende levering))
                        max_vaccins = std::min(max_vaccins, ((double) centrum->getCapaciteit() *
                                                             ((double) aantal_vac_start - (double) getAantalGer())) /
                                                            (double) max_cap_all_cent_tot_lev);
                    }
                    //als het vaccin gekoeld moet blijven
                    if (type->gettemperatuur() < 0) {
                        gecapped = true;
                        //max vaccins is de capaciteit - het aantal hernieuwingen dat vandaag plaatsvindt
                        max_vaccins = std::min(max_vaccins,
                                               (double) centrum->getCapaciteit() - centrum->getAantalHernieuwing(dag));
                        max_vaccins = std::min(max_vaccins,
                                               (double) centrum->getCapaciteit() - centrum->getAantalHernieuwing(dag+type->gethernieuwing()));
                    }
                    while ((//genoeg vaccins en er past nog een lading bij
                                   (!gecapped && (2 * centrum->getCapaciteit() >
                                                  totale_lading + centrum->getAantalVaccins() + type->getTransport()))
                                   // of niet genoeg vaccins en max = max_vaccins
                                   || (gecapped && (max_vaccins > totale_lading + type->getTransport()) &&
                                       2 * centrum->getCapaciteit() >
                                       totale_lading + centrum->getAantalVaccins() + type->getTransport()))
                           //en er moet genoeg van dat type vrij zijn
                           && (type->aantalNietGer() > (lading_type_centrum + type->getTransport()) * 2)
                           //en hernieuwing mag de capaciteit op dag hernieuwing+dag niet overschrijven
                           && (centrum->getAantalHernieuwing(type->gethernieuwing() + dag) + type->getTransport() <=
                               centrum->getCapaciteit())
                            ) {
                        lading_type_centrum += type->getTransport();
                        totale_lading += type->getTransport();
                        aantal_ladingen++;
                    }
                    centrum->addVaccins(lading_type_centrum, type->getName());
                    //als er hernieuwing wordt gedaan
                    if (type_it->second->gethernieuwing() > 0) {
                        //add gereserveerden
                        type_it->second->addGereserveerd(lading_type_centrum);
                    }
                    //als het vaccin gekoeld moet blijven
                    if (type->gettemperatuur() < 0) {
                        //tel het op bij aantal_gekoeld
                        aantal_gekoeld += lading_type_centrum;
                    }
                    type->substractVaccins((lading_type_centrum));
                }
            }
            out << "Er werden " << aantal_ladingen << " ladingen (" << totale_lading
                << " vaccins) getransporteerd naar " <<
                centrum->getNaamCentrum() << "." << std::endl;
                aantal_ladingen_vorige_dag[centrum] = aantal_ladingen;
            ENSURE(centrum->getCapaciteit() >= centrum->getAantalHernieuwing(dag) + aantal_gekoeld,
                   "Capaciteit van centrum < geplande hernieuwingen + gekoelde vaccins na transportToCentra");
        }
    }
}

const std::map<Vaccinatiecentrum *, int> &Hub::getAantalLadingenVorigeDag() const {
    return aantal_ladingen_vorige_dag;
}

void Hub::setAantalLadingenVorigeDag(const std::map<Vaccinatiecentrum *, int> &aantalLadingenVorigeDag) {
    aantal_ladingen_vorige_dag = aantalLadingenVorigeDag;
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
    this->aantal_ladingen_vorige_dag[vaccinatiecentrum] = 0;
    ENSURE(this->aantal_ladingen_vorige_dag[vaccinatiecentrum] == 0,
           "aantal ladingen van de vorige dag van het centrum moet 0 zijn na addcentrum");
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
    if (vaccinatiecentra.empty()){
        return false;
    }
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

int Hub::getAantalVac() const {
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
    ENSURE(ger >=0,"gereserveerden < 0 bij getAantalGer van hub");
    return ger;
}

void Hub::transportToCentra2(int dag) {
    transportToCentra2(dag,std::cout);
}



