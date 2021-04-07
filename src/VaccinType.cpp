//
// Created by User on 7/04/2021.
//

#include "VaccinType.h"


int VaccinType::getAantalVaccins() const {
    REQUIRE(this->correctlyInitialized(),"Het hub object was niet geinitializeerd oproeping van getAantalVaccins");
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
    //TODO correctlyinitialized
    return name;
}

void VaccinType::setName(const std::string &name1) {
    //TODO correctlyinitialized
    //TODO name.size >0
    VaccinType::name = name1;
    //TODO this->name == name1
}

int VaccinType::getLevering() const {
    //TODO correctlyinitialized
    return levering;
}

void VaccinType::setLevering(int levering1) {
    //TODO correctlyinitialized
    //TODO levering1 >= 0
    VaccinType::levering = levering1;
    //TODO this->levering == levering
}

int VaccinType::getTransport() const {
    //TODO correctlyinitialized
    return transport;
}

void VaccinType::setTransport(int transport1) {
    //TODO correctlyinitialized
    //TODO transport1 >= 0
    VaccinType::transport = transport1;
    //TODO this->transport == transport1
}

int VaccinType::getInterval() const {
    //TODO correctlyinitialized
    return interval;
}

void VaccinType::setInterval(int interval1) {
    //TODO interval1 >= 0
    //TODO correctlyinitialized
    VaccinType::interval = interval1;
    //TODO this->interval == interval1
}

VaccinType::VaccinType() {
    this->name = "";
    this->levering = 0;
    this->transport = 0;
    this->interval = 0;
    this->init_check = this;

    //TODO:
    // this->name == ""
    // this->levering == 0
    // this->interval == 0
    // this->transport == 0
    // this-> levering == 0
    // this->correctlyinitialized


}

bool VaccinType::correctlyInitialized() const {
    return (this == init_check);
}

void VaccinType::leveringVanType() {
    REQUIRE(this->correctlyInitialized(),"Hub was niet geinitalizeerd bij oproep van leveringToHub");
    int old = aantal_vaccins;
    aantal_vaccins += levering;
    ENSURE(old == aantal_vaccins - levering, "Vaccins is incorrect afgetrokken van de hub");

}
