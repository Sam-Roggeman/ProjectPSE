//============================================================================
// Name        : Vaccinatiecentrum.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccinatiecentrum in C++, Ansi-style
//============================================================================

#include "Vaccinatiecentrum.h"


Vaccinatiecentrum::Vaccinatiecentrum() {
    _initCheck = this;
    aantal_gevaccineerden = 0;
    naam_centrum = "";
    adres_centrum = "";
    aantal_inwoners = 0;
    capaciteit= 0;
    aantal_vol_gevaccineerden = 0;
    hernieuwingen.clear();
    ENSURE(correctlyInitialized(),
           "constructor must end in correctlyInitialized state");
    ENSURE(this->aantal_gevaccineerden == 0, "Aantal gevaccineerden was niet nul bij het einde van de constructor");
    ENSURE(this->getAantalInwoners() == 0, "Aantal inwoners was niet nul bij het einde van de constructor");
    ENSURE(this->getCapaciteit() == 0, "Capaciteit was niet nul bij het einde van de constructor");
    ENSURE(this->aantal_vol_gevaccineerden == 0, "aantal_vol_gevaccineerden was niet nul bij het einde van de constructor");
    ENSURE(this->hernieuwingen.empty(), "hernieuwingen waren niet leeg bij het einde van de constructor");
    
    ENSURE(getNaamCentrum().size() == 0, "naam van centrum was niet leeg bij het einde van de constructor");
    ENSURE(getAdresCentrum().size() == 0, "adres van centrum was niet leeg bij het einde van de constructor");
}


void Vaccinatiecentrum::setNaamCentrum(const std::string &naamcentrum) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setNaamCentrum");
    REQUIRE(!naamcentrum.empty(),"nieuwe naam mag niet leeg zijn bij setNaamCentrum");
    naam_centrum = naamcentrum;
    ENSURE(naamcentrum==naam_centrum,"nieuwe naam is niet gelijk aan de naam van het centrum bij einde van setNaamCentrum");
}

/**returnt de naam van het centrum
 * @return de naam van het centrum
 * @pre this.correctlyInitialized()
 * */
const std::string &Vaccinatiecentrum::getNaamCentrum() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getNaamCentrum");
    return naam_centrum;
}

/**verandert het adres van het centrum naar adrescentrum
 * @param naamcentrum: nieuwe adres van het centrum
 * @pre this.correctlyInitialized()
 */
 void Vaccinatiecentrum::setAdresCentrum(const std::string &adrescentrum) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setadrescentrum");
    REQUIRE(!adrescentrum.empty(),"nieuw adres mag niet leeg zijn bij setadrescentrum");
    adres_centrum = adrescentrum;
    ENSURE(adrescentrum==adres_centrum,"nieuw adres is niet gelijk aan het adres van het centrum bij einde van setadrescentrum");
}

/**returnt het adres van het centrum
 * @return het adres van het centrum
 * @pre this.correctlyInitialized()
 * */
const std::string &Vaccinatiecentrum::getAdresCentrum() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAdresCentrum");
    return adres_centrum;
}

/**zet het aantal inwoners dat bij het centrum hoort op aantal
 * @param aantal: nieuw aantal inwoners
 * @pre aantal >= 0
 * @pre this.correctlyInitialized()
 * */
void Vaccinatiecentrum::setAantalInwoners(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setAantalInwoners");
    REQUIRE(aantal >= 0, "Aantal inwoners moet >= 0");
    aantal_inwoners = aantal;
    ENSURE(    getAantalInwoners() == aantal, "Aantal inwoners is niet correct gewijzigd na setAantalInwoners");
}

/**returnt het aantal inwoners dat bij het centrum hoort
 * @return het aantal inwoners
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::getAantalInwoners() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAantalInwoners");
    return aantal_inwoners;
}

/**returnt het aantal vaccins in het centrum
 * @return het aantal vaccins in het centrum
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::getAantalVaccinsVanType(std::string naam_type) const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAantalVaccinsVanType");
    return this->vaccins.at(naam_type);
}

/**zet het aantal vaccins in het centrum op aantal
 * @param het nieuwe aantal vaccins
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 */
void Vaccinatiecentrum::setAantalVaccins(std::string naam_type, int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setAantalVaccins");
    REQUIRE(aantal >= 0, "aantal vaccins moet >= 0");
    this->vaccins[naam_type] = aantal;
    ENSURE(this->vaccins[naam_type] == aantal,
           "aantal vaccins is niet juist aangepast bij setAantalVaccins in centrum");
}

/**zet de vaccinatiecapaciteit op capaciteit1
 * @param aantal: De nieuwe capaciteit van het centrum
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 * */
void Vaccinatiecentrum::setCapaciteit(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setCapaciteit");
    REQUIRE(aantal >=0,"capaciteit moet >= 0 zijn");
    Vaccinatiecentrum::capaciteit = aantal;
    ENSURE(this->getCapaciteit() == aantal,
           "aantal vaccins is niet juist aangepast bij setAantalVaccins in centrum");
}

/**returnt de vaccinatiecapaciteit per dag
 * @return de capaciteit van het centrum
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::getCapaciteit() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getCapaciteit");
    return capaciteit;
}

/**zet de gevaccineerden op aantalGevaccineerden
 * @param aantal: het nieuwe aantal gevaccineerden
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 * @post aantal_gevaccineerden = aantal
 * */
void Vaccinatiecentrum::setAantalGevaccineerden(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setAantalGevaccineerden");
    REQUIRE(aantal >= 0, "aantal gevaccineerden moet >= 0");
    aantal_gevaccineerden = aantal;
    ENSURE(aantal_gevaccineerden == aantal,
           "aantal gevaccineerden is niet juist veranderd bij oproep van setAantalGevaccineerden");
}

/**returt het aantal mensen dat gevaccineerd is
 * @return het aantal gevaccineerden
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::getAantalGevaccineerden() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAantalEnkelGevaccineerden");
    return aantal_gevaccineerden;
}

/**substract het aantal van het huidige aantal vaccins
 * @param aantal: het aantal vaccins dat geleverd werd werd
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 * @post aantal_vaccins += aantal
 * */
void Vaccinatiecentrum::addVaccins(int aantal, std::string naam_type) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling addVaccins");
    REQUIRE(aantal >= 0, "Amount of vaccins to add should be >= 0");
    int old = vaccins[naam_type];
    vaccins[naam_type] += aantal;
    ENSURE(vaccins[naam_type] == old+aantal, "nieuw aantal is niet gelijk aan oud aantal + aantal");
}

/**substract het aantal van het huidige aantal vaccins
* @param aantal: het aantal vaccins dat gebruikt werd
* @pre this.correctlyInitialized()
* @pre aantal >= 0
* @post aantal_vaccins -= aantal
* @post aantal_vaccins >= 0
* */
void Vaccinatiecentrum::substractVaccins(int aantal, std::string naam_type) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling addGevaccineerden");
    REQUIRE(aantal >= 0, "Amount of vaccins to substract should be >= 0");
    int old = vaccins[naam_type];
    this->vaccins[naam_type] -= aantal;
    ENSURE(vaccins[naam_type] == old-aantal, "nieuw aantal is niet gelijk aan oud aantal + aantal");
    ENSURE(vaccins[naam_type] >= 0, "nieuw aantal is niet >=0");

}

/**add aantal_gevaccineerden toe aan het totaal aantal gevaccineren
 * @param aantal_gevaccineerden: het aantal mensen dat gevaccineerd werd
 * @pre this.correctlyInitialized()
 * @pre aantal_gevaccineerden >= 0
 * @post gevaccineerden += aantal_gevaccineerden
 * */
void Vaccinatiecentrum::addGevaccineerden(int aantal_gevaccineerden1) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling addGevaccineerden");
    REQUIRE(aantal_gevaccineerden1 >= 0, "Amount of aantal_gevaccineerden to add should be >= 0");
    int old = aantal_gevaccineerden;
    aantal_gevaccineerden += aantal_gevaccineerden1;
    ENSURE(aantal_gevaccineerden == old+aantal_gevaccineerden1, "nieuw aantal is niet gelijk aan oud aantal + aantal");
}

/**returnt het aantal ongevaccineerden
 * @returnt getAantalInwoners() - aantal_gevaccineerden
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::aantalOngevaccineerden() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling aantalOngevaccineerden");
    int out = getAantalInwoners()-aantal_gevaccineerden-aantal_vol_gevaccineerden;
    ENSURE(out >= 0, "aantal ongevaccineerden moet >= 0 zijn");
    return out;
}

/**kijkt na of het cenrum correct geinitializeerd is
 * @returns true als correct
 * */
bool Vaccinatiecentrum::correctlyInitialized() const {
    return this == _initCheck;
}

/**vaccinaties worden uitgevoerd en output gaat naar std::cout
* @param out: de outstream waarnaar de output gestuurt wordt
 * @pre this.correctlyInitialized()
 * @post aantal_vaccins <= aantal_vaccins_start
 * @post aantal_gevaccineerden <= aantal_gevaccineerden_start
 * */
void Vaccinatiecentrum::vaccineren(int dag) {
    vaccineren(dag, std::cout);
}

void Vaccinatiecentrum::vaccineren(int dag, std::ostream &out) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling aantalOngevaccineerden");
    REQUIRE(dag >=0, "dag moet positief zijn bij vaccineren");
    int aantal_vaccins_start = this->getAantalVaccins();
    int aantal_gevaccineerden_start = aantal_gevaccineerden+aantal_vol_gevaccineerden;
    int aantal_nieuwe_gevaccineerden = 0;
    int current_cap = this->capaciteit;
    int aantal;
    for(std::map<std::string, std::map<int, int> >::iterator hernieuwing_it = hernieuwingen.begin();
        hernieuwing_it != hernieuwingen.end(); hernieuwing_it++ ){
        aantal = hernieuwing_it->second[dag];

        vaccins[hernieuwing_it->first] -= aantal;
        aantal_vol_gevaccineerden +=  aantal;
        aantal_gevaccineerden -=  aantal;
        current_cap -= aantal;
        hernieuwing_it->second[dag] -= aantal;
    }
    //gekoelde vaccins eerst
    for (std::map<std::string, VaccinType*>::const_iterator vac_it = this->types.begin(); vac_it != types.end(); vac_it++){
        if (types[vac_it->first]->gettemperatuur() < 0 ) {
            int temp = std::min(this->vaccins[vac_it->first], current_cap);
            aantal_nieuwe_gevaccineerden = std::min(temp, this->aantalOngevaccineerden());
            if (hernieuwingen.find(vac_it->first) != hernieuwingen.end()
                &&hernieuwingen[vac_it->first].find(types[vac_it->first]->gethernieuwing()+dag) != hernieuwingen[vac_it->first].end()
                &&capaciteit< getAantalHernieuwing(types[vac_it->first]->gethernieuwing()+dag)+aantal_nieuwe_gevaccineerden){
                aantal_nieuwe_gevaccineerden = capaciteit-getAantalHernieuwing(types[vac_it->first]->gethernieuwing()+dag);
            }
            this->substractVaccins(aantal_nieuwe_gevaccineerden, vac_it->first);
            current_cap -= aantal_nieuwe_gevaccineerden;
            if (vac_it->second->gethernieuwing() > 0) {
                this->addGevaccineerden(aantal_nieuwe_gevaccineerden);
                hernieuwingen[vac_it->first][types[vac_it->first]->gethernieuwing() +
                                             dag] += aantal_nieuwe_gevaccineerden;
                vac_it->second->addGereserveerd(aantal_nieuwe_gevaccineerden % vac_it->second->getTransport());
            }
            else{
                this->aantal_vol_gevaccineerden += aantal_nieuwe_gevaccineerden;
            }
        }
    }
    //ongekoelde vaccins
    for (std::map<std::string, VaccinType*>::const_iterator vac_it = this->types.begin(); vac_it != types.end(); vac_it++) {
        int temp = std::min(this->vaccins[vac_it->first], current_cap);
        aantal_nieuwe_gevaccineerden = std::min(temp, this->aantalOngevaccineerden());
        if (hernieuwingen.find(vac_it->first) != hernieuwingen.end()
            && hernieuwingen[vac_it->first].find(types[vac_it->first]->gethernieuwing() + dag) !=
               hernieuwingen[vac_it->first].end()
            && capaciteit <
               getAantalHernieuwing(types[vac_it->first]->gethernieuwing() + dag) + aantal_nieuwe_gevaccineerden) {
            aantal_nieuwe_gevaccineerden =
                    capaciteit - getAantalHernieuwing(types[vac_it->first]->gethernieuwing() + dag);
        }
        this->substractVaccins(aantal_nieuwe_gevaccineerden, vac_it->first);
        current_cap -= aantal_nieuwe_gevaccineerden;
        if (vac_it->second->gethernieuwing() > 0) {
            this->addGevaccineerden(aantal_nieuwe_gevaccineerden);
            hernieuwingen[vac_it->first][types[vac_it->first]->gethernieuwing() + dag] += aantal_nieuwe_gevaccineerden;
            vac_it->second->addGereserveerd(aantal_nieuwe_gevaccineerden % vac_it->second->getTransport());
        }
        else{
            this->aantal_vol_gevaccineerden += aantal_nieuwe_gevaccineerden;
        }
    }
    for (std::map<std::string, VaccinType*>::const_iterator vac_it = this->types.begin(); vac_it != types.end(); vac_it++) {
        if (vac_it->second->gettemperatuur()<0){
            ENSURE(vaccins[vac_it->first]== 0, "Niet alle gekoelde vaccins zijn opgebruikt bij einde van vaccineren") ;
        }
    }

    ENSURE(this->getAantalVaccins() <= aantal_vaccins_start,
           "Aantal vaccins is gestegen na vaccineren");
    ENSURE(aantal_gevaccineerden+aantal_vol_gevaccineerden >= aantal_gevaccineerden_start,
           "Aantal gevaccineerden is gezakt na vaccineren");
    ENSURE(this->getAantalHernieuwing(dag)==0,"aantal geplande herniuwingen is niet volbracht na vaccineren");

    out << "Er werden " << this->capaciteit - current_cap <<" inwoners gevaccineerd in " <<
        this->naam_centrum << "." << std::endl;
}

bool Vaccinatiecentrum::completelyInitialized() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling completelyInitialized");
    if (this->getCapaciteit()<=0){
        return false;
    }
    else if (this->getAdresCentrum().empty()){
        return false;
    }
    else if (this->getAantalInwoners()<=0) {
        return false;
    }
    else if (this->getNaamCentrum().empty()){
        return false;
    }
    return true;
}

int Vaccinatiecentrum::getAantalVaccins()const{
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum niet geinitializeerd bij oproep van getAantalVaccins");
    int aantal_vac = 0 ;
    for(std::map<std::string,int>::const_iterator it = vaccins.begin(); it != vaccins.end(); it++){
        aantal_vac += it->second;
    }
    ENSURE(aantal_vac >=0, "aantal_vac moet >= 0");
    return aantal_vac;
}

void Vaccinatiecentrum::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van impressie");
    ENSURE(this->completelyInitialized(), "Vaccinatiecentrum was niet compleet geinitializeerd bij oproep van impressie");
    int vac_verhouding = 100 * this->getAantalVaccins() / (this->getCapaciteit() * 2);
    int gevac_verhouding = 100*this->getAantalGevaccineerden()/this->getAantalInwoners();
    int vol_gevac_verhouding = 100*this->getAantalVolGevaccineerden()/this->getAantalInwoners();
    out << this->getNaamCentrum() << ':' << std::endl << "    "  << "- vaccins               ";

    out << '[';
    for(int i = 0; i < vac_verhouding/5; i++){
        out << '=';
    }
    for(int i = vac_verhouding/5; i < 20; i++ ){
        out << " ";
    }
    out << ']' << " " << vac_verhouding << '%' << std::endl;

    out << "    " << "- gevaccineerd          ";
    out << '[';
    for(int i = 0; i < gevac_verhouding/5; i++){
        out << '=';
    }
    for(int i = gevac_verhouding/5; i < 20; i++ ){
        out << " ";
    }
    out << ']' << " " << gevac_verhouding << '%' << std::endl;

    out << "    " << "- volledig gevaccineerd ";
    out << '[';
    for(int i = 0; i < vol_gevac_verhouding/5; i++){
        out << '=';
    }
    for(int i = vol_gevac_verhouding/5; i < 20; i++ ){
        out << " ";
    }
    out << ']' << " " << vol_gevac_verhouding << '%' << std::endl;
}

void Vaccinatiecentrum::insertTypes(std::map<std::string, VaccinType*> types1) {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van setTypes");
    types.insert(types1.begin(),types1.end());
    for (std::map<std::string,VaccinType*>::iterator type_it = types.begin(); type_it!=types.end();type_it++) {
        vaccins[type_it->first] = 0;
        ENSURE(vaccins[type_it->first]==0, "aantal van vaccintype moet geinitializeerd worden bij setTypes");
    }
//    ENSURE(types == types1,"types en types1 moeten gelijk zijn na settypes");
}

int Vaccinatiecentrum::getAantalGeres(std::string naam_type, int dag) {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van getAantalGeres");
    REQUIRE(dag>=0, "dag moet >=0 zijn");
    if (types.find(naam_type) ==types.end()){
        return 0;
    }
    return this->hernieuwingen[naam_type][dag];
}

void Vaccinatiecentrum::substractAantalGeres(std::string naam_type, int dag, int aantal) {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van substractAantalGeres");
    REQUIRE(dag>=0, "dag moet >=0 zijn");
    REQUIRE(types.find(naam_type) !=types.end(), "type met naam_type zit niet in types");
    REQUIRE(aantal >= 0, "aantal moet >= 0 bij substractAantaGeres");
    this->hernieuwingen[naam_type][dag] -= std::min(hernieuwingen[naam_type][dag],aantal);
}

int Vaccinatiecentrum::getAantalVolGevaccineerden() {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van getAantalVolGevaccineerden");
    return aantal_vol_gevaccineerden;
}

int Vaccinatiecentrum::getAantalHernieuwing(int dag) {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van getAantalHernieuwing");
    REQUIRE(dag>=0, "dag moet >=0 zijn");
    int ret_val = 0;
    for (std::map<std::string,VaccinType*>::iterator type_it = types.begin(); type_it!=types.end();type_it++) {
        ret_val += hernieuwingen[type_it->first][dag];
    }
    return ret_val;
}

int Vaccinatiecentrum::aantalOnvolledigGev() {
    REQUIRE(this->correctlyInitialized(), "Vaccinatiecentrum was niet correct geinitializeerd bij oproep van aantalOnvolledigGev");
    return getAantalInwoners()-aantal_vol_gevaccineerden;
}

const std::map<std::string, int> &Vaccinatiecentrum::getVaccins() const {
    return vaccins;
}

const std::map<std::string, VaccinType *> &Vaccinatiecentrum::getTypes() const {
    return types;
}

const std::map<std::string, std::map<int, int > > &Vaccinatiecentrum::getHernieuwingen() const {
    return hernieuwingen;
}

Vaccinatiecentrum::Vaccinatiecentrum(Vaccinatiecentrum *const pVaccinatiecentrum) {
    this->_initCheck = this;
    this->hernieuwingen.insert(pVaccinatiecentrum->hernieuwingen.begin(),pVaccinatiecentrum->hernieuwingen.end());
    this->vaccins.insert(pVaccinatiecentrum->vaccins.begin(),pVaccinatiecentrum->vaccins.end());
    this->aantal_gevaccineerden = pVaccinatiecentrum->aantal_gevaccineerden;
    this->aantal_vol_gevaccineerden = pVaccinatiecentrum->aantal_vol_gevaccineerden;
    this->capaciteit = pVaccinatiecentrum->capaciteit;
    this->aantal_inwoners = pVaccinatiecentrum->aantal_inwoners;
    this->naam_centrum = pVaccinatiecentrum->naam_centrum;
    this->adres_centrum = pVaccinatiecentrum->adres_centrum;

}

bool Vaccinatiecentrum::isAllowed(const int _vaccins) {
    return 2*this->capaciteit + getAantalVaccins() >= _vaccins;
}

void Vaccinatiecentrum::sendVaccins(const std::string name_type, int aantal, std::ostream &out, int aantal_ladingen) {
}

void Vaccinatiecentrum::setTypes(std::map<std::string, VaccinType *> map) {
    this->types = map;
}




