//
// Created by User on 7/04/2021.
//

#include "VaccinType.h"

int VaccinType::getAantalVaccins() const {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van getAantalVaccinsVanType");
    return aantal_vaccins;
}
void VaccinType::substractVaccins(int vaccins) {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van substractVaccins");
    REQUIRE(vaccins >= 0, "substractVaccins accepteerd geen negatieve getallen");
    int old = aantal_vaccins;
    this->aantal_vaccins -= vaccins;
    ENSURE(aantal_vaccins >= 0, "aantal overgebleven vaccins is minder dan 0 na substracting");
    ENSURE(aantal_vaccins == old -vaccins,
           "oud aantal vaccins - verschil is niet gelijk aan nieuw aantal na substracting");
}


const std::string &VaccinType::getName() const {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    return name;
}

void VaccinType::setName(const std::string &name1) {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    REQUIRE(name1.size() > 0, "Er is geen geldige naam ingegeven");
    VaccinType::name = name1;
    ENSURE(this->name == name1, "De naam is verkeerd geinitialiseerd");
}

int VaccinType::getLevering() const {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    return levering;
}

void VaccinType::setLevering(int levering1) {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    REQUIRE(levering1 >= 0, "De levering kan niet negatief zijn");
    VaccinType::levering = levering1;
    ENSURE(this->levering == levering1, "De levering is verkeerd geinitialiseerd");
}

int VaccinType::getTransport() const {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    return transport;
}

void VaccinType::setTransport(int transport1) {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    REQUIRE(transport1 >= 0, "De transport kan niet negatief zijn");
    VaccinType::transport = transport1;
    ENSURE(this->transport == transport1, "De transport is verkeerd geinitialiseerd");
}

int VaccinType::getInterval() const {
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    return interval;
}

void VaccinType::setInterval(int interval1) {
    REQUIRE(interval1 >= 0, "Het interval kan niet negatief zijn");
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype is verkeerd geinitialiseerd");
    VaccinType::interval = interval1;
    ENSURE(this->interval == interval1, "Het interval kan niet negatief zijn");
}

VaccinType::VaccinType() {
    this->name = "";
    this->levering = 0;
    this->transport = 0;
    this->interval = 0;
    this->_init_check = this;
    this->aantal_vaccins = 0;
    this->hernieuwing = 0;
    this->temperatuur = 27;
    this->gereserveerd = 0;

    ENSURE(this->getName() == "", "De naam is verkeerd geinitialiseerd");
    ENSURE(this->getLevering() == 0, "De levering is verkeerd geinitialiseerd");
    ENSURE(this->getInterval() == 0, "Het interval is verkeerd geinitialiseerd");
    ENSURE(this->getTransport() == 0, "De transport is verkeerd geinitialiseerd");
    ENSURE(this->getLevering() == 0, "De levering is verkeerd geinitialiseerd");
    ENSURE(this->getGereserveerd() == 0, "De levering is verkeerd geinitialiseerd");
    ENSURE(this->getAantalVaccins() == 0, "Het aantal_vaccins is verkeerd geinitialiseerd");
    ENSURE(this->gethernieuwing()== 0, "De hernieuwing is verkeerd geinitialiseerd");
    ENSURE(this->gettemperatuur() == 27, "De temperatuur is verkeerd geinitialiseerd");
    ENSURE(this->correctlyInitialized(), "Het object Vaccintype is verkeerd geinitialiseerd");
}

bool VaccinType::correctlyInitialized() const {
    return (this == _init_check);
}

void VaccinType::leveringVanTypeToHub() {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitalizeerd bij oproep van leveringToHub");
    int old = aantal_vaccins;
    aantal_vaccins += levering;
    ENSURE(old == aantal_vaccins - levering, "Vaccins is incorrect afgetrokken van de hub");

}

bool VaccinType::completelyInitialized(){
    REQUIRE(this->correctlyInitialized(),"Het object Vaccintype was niet correct geinitalizeerd bij oproep van completelyInitialized");
    bool out = true;
    if (aantal_vaccins<0||levering<0||interval<0||transport<0||gereserveerd<0){
        out = false;
    }
    return out;
}

bool VaccinType::isLeveringsDag(const int dag) const {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van isLeveringDag");
    REQUIRE(dag >= 0, "Dag kan geen negatief getal zijn");
    if (dag % (interval+1) == 0)
        return true;
    else
        return false;
}

int VaccinType::nextLeveringsDag(const int dag) const {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van nextLeveringDag");
    REQUIRE(dag >= 0, "Dag kan geen negatief getal zijn");
    return (interval+1)-(dag % (interval+1));
}

void VaccinType::setAantalVaccins(const int aantal_vaccins1) {
    aantal_vaccins = aantal_vaccins1;
}

int VaccinType::gettemperatuur() const {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van gettemperatuur");
    return temperatuur;
}

void VaccinType::sethernieuwing(const int h) {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van setHernieuwing");
    hernieuwing = h;
    ENSURE(hernieuwing == h, "hernieuwing is niet juist veranderd bij setHernieuwing");
}

int VaccinType::gethernieuwing() {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van getHernieuwing");
    return hernieuwing;
}

void VaccinType::settemperatuur(const int t) {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van settemperatuur");
    temperatuur = t;
    ENSURE(temperatuur == t, "temperatuur is niet juist veranderd bij settemperatuur");
}

int VaccinType::getGereserveerd() const {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van getGereserveerd");
    return gereserveerd;
}

void VaccinType::setGereserveerd(int gereserveerd1) {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van getGereserveerd");
    REQUIRE(gereserveerd >=0,"gereserveerden1 moet >= 0 bij setGereserveerd");
    VaccinType::gereserveerd = gereserveerd1;
    ENSURE(gereserveerd == gereserveerd1, "gereserveerd is niet juist veranderd bij setGereserveerd");
}

int VaccinType::aantalNietGer() {
    REQUIRE(this->correctlyInitialized(),"Vaccintype was niet geinitializeerd bij oproep van aantalNietGer");
    return aantal_vaccins-gereserveerd;
}

void VaccinType::addGereserveerd(int aantal) {
    REQUIRE(aantal>=0,"aantal moet >= 0 bij addGereserveerd ");
    int start = gereserveerd;
    gereserveerd +=aantal;
    ENSURE(gereserveerd>=0, "gereserveerd moet >= 0 bij einde van addGereserveerd");
    ENSURE(start+aantal == gereserveerd, "gereserveerd != start+aantal bij einde van addGereserveerd");
}

void VaccinType::subGereserveerd(int aantal) {
    REQUIRE(aantal>=0,"aantal moet >= 0 bij subGereserveerd ");
    int start = gereserveerd;
    gereserveerd -=aantal;
    ENSURE(gereserveerd>=0, "gereserveerd moet >= 0 bij einde van subGereserveerd");
    ENSURE(start-aantal == gereserveerd, "gereserveerd != start-aantal bij einde van subGereserveerd");
}

VaccinType::VaccinType(const VaccinType& v2) : name(v2.name), levering(v2.levering),
                                                                             transport(v2.transport), interval(v2.interval),
                                                                             aantal_vaccins(v2.aantal_vaccins),
                                                                             hernieuwing(v2.hernieuwing),
                                                                             temperatuur(v2.temperatuur),
                                                                             gereserveerd(v2.gereserveerd) {
    REQUIRE(v2.correctlyInitialized(), "v2 was niet geinitializeerd bij oproep van de copy constructor ");
    this->_init_check = this;
    ENSURE(getLevering()== v2.getLevering(), "levering is niet hoed gekopieerd");
    ENSURE(getAantalVaccins()== v2.getAantalVaccins(),"aantal vaccins is niet hoed gekopieerd");
    ENSURE(getTransport()== v2.getTransport(),"transport is niet hoed gekopieerd");
    ENSURE(getInterval()== v2.getInterval(),"interval is niet hoed gekopieerd");
    ENSURE(getGereserveerd()== v2.getGereserveerd(),"gereserveerd is niet hoed gekopieerd");
    ENSURE(gettemperatuur()== v2.gettemperatuur(),"temperatuur is niet hoed gekopieerd");
    ENSURE(getName()== v2.getName(),"name is niet hoed gekopieerd");
    ENSURE(correctlyInitialized(),"type is niet correct geinitializeerd bij afloop van de copy constructor");
}
