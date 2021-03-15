//============================================================================
// Name        : Vaccinatiecentrum.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccinatiecentrum in C++, Ansi-style
//============================================================================

#include "Vaccinatiecentrum.h"

/**maakt een vaccinatiecentrum object aan
 * @return vaccinatiecentrum
 * @post this.correctlyInitialized()
 * */
Vaccinatiecentrum::Vaccinatiecentrum() {
    _initCheck = this;
    aantal_vaccins = 0;
    aantal_gevaccineerden = 0;
    naam_centrum = "";
    adres_centrum = "";
    aantal_inwoners = 0;
    capaciteit= 0;
    ENSURE(correctlyInitialized(),
           "constructor must end in properlyInitialized state");
}

/**veranderd de naam van het centrum naar naamCentrum
     * @param naamcentrum: nieuwe naam van het centrum
     * @pre this.correctlyInitialized()
     * */
void Vaccinatiecentrum::setNaamCentrum(const std::string &naamcentrum) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setNaamCentrum");
    naam_centrum = naamcentrum;
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
            "Vaccinatiecentrum wasn't initialized when calling setAdresCentrum");
    adres_centrum = adrescentrum;
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
int Vaccinatiecentrum::getAantalVaccins() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAantalVaccins");
    return aantal_vaccins;
}

/**zet het aantal vaccins in het centrum op aantal
 * @param het nieuwe aantal vaccins
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 */
void Vaccinatiecentrum::setAantalVaccins(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setAantalVaccins");
    REQUIRE(aantal >= 0, "aantal vaccins moet >= 0");
    aantal_vaccins = aantal;
}

/**zet de vaccinatiecapaciteit op capaciteit1
 * @param aantal: De nieuwe capaciteit van het centrum
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 * */
void Vaccinatiecentrum::setCapaciteit(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setCapaciteit");
    Vaccinatiecentrum::capaciteit = aantal;
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
 * */
void Vaccinatiecentrum::setAantalGevaccineerden(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling setAantalGevaccineerden");
    REQUIRE(aantal >= 0, "aantal gevaccineerden moet >= 0");
    aantal_gevaccineerden = aantal;
}

/**returt het aantal mensen dat gevaccineerd is
 * @return het aantal gevaccineerden
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::getAantalGevaccineerden() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling getAantalGevaccineerden");
    return aantal_gevaccineerden;
}

/**substract het aantal van het huidige aantal vaccins
 * @param aantal: het aantal vaccins dat geleverd werd werd
 * @pre this.correctlyInitialized()
 * @pre aantal >= 0
 * @post aantal_vaccins += aantal
 * */
void Vaccinatiecentrum::addVaccins(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling addVaccins");
    REQUIRE(aantal >= 0, "Amount of vaccins to add should be >= 0");
    int old = aantal_vaccins;
    aantal_vaccins += aantal;
    ENSURE(aantal_vaccins == old+aantal, "nieuw aantal is niet gelijk aan oud aantal + aantal");
}

/**substract het aantal van het huidige aantal vaccins
* @param aantal: het aantal vaccins dat gebruikt werd
* @pre this.correctlyInitialized()
* @pre aantal >= 0
* @post aantal_vaccins -= aantal
* @post aantal_vaccins >= 0
* */
void Vaccinatiecentrum::substractVaccins(int aantal) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling addGevaccineerden");
    REQUIRE(aantal >= 0, "Amount of vaccins to substract should be >= 0");
    int old = aantal_vaccins;
    this->aantal_vaccins -= aantal;
    ENSURE(aantal_vaccins == old-aantal, "nieuw aantal is niet gelijk aan oud aantal + aantal");

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
 * @returnt aantal_inwoners - aantal_gevaccineerden
 * @pre this.correctlyInitialized()
 * */
int Vaccinatiecentrum::aantalOngevaccineerden() const {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling aantalOngevaccineerden");
    return aantal_inwoners-aantal_gevaccineerden;
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
void Vaccinatiecentrum::vaccineren() {
    vaccineren(std::cout);
}

/**vaccinaties worden uitgevoerd en output gaat naar out
* @param out: de outputstream waarnaar de output gestuurt wordt
 * @pre this.correctlyInitialized()
 * @post aantal_vaccins <= aantal_vaccins_start
 * @post aantal_gevaccineerden >= aantal_gevaccineerden_start
 * */
void Vaccinatiecentrum::vaccineren(std::ostream& out) {
    REQUIRE(this->correctlyInitialized(),
            "Vaccinatiecentrum wasn't initialized when calling aantalOngevaccineerden");
    int aantal_gevaccineerden_start = aantal_gevaccineerden;
    int aantal_vaccins_start = aantal_vaccins;

    int aantal_nieuwe_gevaccineerden = std::min(aantal_vaccins, capaciteit);
    aantal_nieuwe_gevaccineerden = std::min(aantal_nieuwe_gevaccineerden, this->aantalOngevaccineerden());
    this->substractVaccins(aantal_nieuwe_gevaccineerden);
    this->addGevaccineerden(aantal_nieuwe_gevaccineerden);

    ENSURE(aantal_vaccins <= aantal_vaccins_start,
           "Aantal vaccins is gestegen na vaccineren");
    ENSURE(aantal_gevaccineerden >= aantal_gevaccineerden_start,
           "Aantal gevaccineerden is gezakt na vaccineren");


    out << "Er werden " << aantal_nieuwe_gevaccineerden <<" inwoners gevaccineerd in " <<
            this->naam_centrum << "." << std::endl;
}



