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
    this->init_check = this;

    ENSURE(this->name == "", "De naam is verkeerd geinitialiseerd");
    ENSURE(this->levering == 0, "De levering is verkeerd geinitialiseerd");
    ENSURE(this->interval == 0, "Het interval is verkeerd geinitialiseerd");
    ENSURE(this->transport == 0, "De transport is verkeerd geinitialiseerd");
    ENSURE(this->levering == 0, "De levering is verkeerd geinitialiseerd");
    ENSURE(this->correctlyInitialized(), "Het object Vaccintype is verkeerd geinitialiseerd");
}

bool VaccinType::correctlyInitialized() const {
    return (this == init_check);
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
    if (aantal_vaccins<0||levering<0||interval<0||transport<0){
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

void VaccinType::setAantalVaccins(const int aantal_vaccins1) {
    aantal_vaccins = aantal_vaccins1;
}