//
// Created by User on 19/05/2021.
//

#include "Gegevens.h"

Gegevens::Gegevens() {
    _init = this;
    ENSURE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd na afloop van de lege constructor");
    ENSURE(geleverd_type.empty(), "!getGeleverdType().empty() bij einde van de constructor");
    ENSURE(getGevaccineerden() == 0, "getGevaccineerden() != 0 bij einde van de constructor");
    ENSURE(getVolledigGevaccineerden() == 0, "getVolledigGevaccineerden() != 0 bij einde van de constructor");
}

void Gegevens::setGevaccineerden(int gevaccineerden2) {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van setGevaccineerden");
    REQUIRE(gevaccineerden2 >= 0 , "gevaccineerden2 < 0");
    gevaccineerden = gevaccineerden2;
    ENSURE(gevaccineerden == gevaccineerden2,
           "aantal gevaccineerden is niet correct gewijzigd bij afloop van setGevaccineerden");
}

void Gegevens::setVolledigGevaccineerden(int vol_gevaccineerden2){
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van setVolledigGevaccineerden");
    REQUIRE(vol_gevaccineerden2 >= 0 , "vol_gevaccineerden2 < 0");

    volledig_gevaccineerden = vol_gevaccineerden2;
    ENSURE(getVolledigGevaccineerden() == vol_gevaccineerden2, "getVolledigGevaccineerden() != vol_gevaccineerden2");
}

void Gegevens::addVaccinPerType(std::string vaccin_name, int aantal) {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van addVaccinPerType");
    REQUIRE(aantal >=0 , "aantal toe te voegen vaccins moet >=0 bij oproep van addVaccinPerType");
    REQUIRE(!vaccin_name.empty(),
           "de mee gegeven vaccin_name mag niet leeg zijn bij operoep van addVaccinPerType");
    int start = geleverd_type[vaccin_name];
    geleverd_type[vaccin_name] += aantal;
    ENSURE(getGeleverdType().at(vaccin_name) == start + aantal, "getGeleverdType().at(vaccin_name) != start + aantal");
}

bool Gegevens::correctlyInitialized() const  {
    return this == _init;
}

Gegevens::Gegevens(const Gegevens * const to_copy) {
    REQUIRE(to_copy->correctlyInitialized(),
           "te-kopieren gegevens niet correct geinitializeerd bij aanroep van de copy-constructor");
    _init = this;
    this->volledig_gevaccineerden = to_copy->volledig_gevaccineerden;
    this->gevaccineerden = to_copy->gevaccineerden;
    this->geleverd_type.clear();
    this->geleverd_type.insert(to_copy->geleverd_type.begin(), to_copy->geleverd_type.end());
    ENSURE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij afloop afloop van de copy-constructor");
    ENSURE(volledig_gevaccineerden == to_copy->volledig_gevaccineerden,
                   "volledig gevaccineerden is niet juist gecopieerd bij de copyconstructor");
    ENSURE(gevaccineerden == to_copy->gevaccineerden,
                   "gevaccineerden is niet juist gecopieerd bij de copyconstructor");
    ENSURE(geleverd_type == to_copy->geleverd_type,
           "geleverd aanal per type is niet juist gecopieerd bij de copyconstructor");
}

const void Gegevens::outputGegevens(std::ostream &out) const {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van outputGegevens");

    out<<'\t' << "Aantal geleverde vaccins per type:" << std::endl;
    for (std::map<std::string,int>::const_iterator it = this->geleverd_type.begin(); it != geleverd_type.end(); it++){
        out << "\t\t" << it->first << ": " << it->second << std::endl;
    }
    out << "\t Aantal onvolledig gevaccineerden:" << this->gevaccineerden <<std::endl;
    out << "\t Aantal volledig gevaccineerden:" << this->volledig_gevaccineerden << std::endl;
}

const int Gegevens::getGevaccineerden() const {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van getGevaccineerden");

    return gevaccineerden;
}

const int Gegevens::getVolledigGevaccineerden() const {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van getVolledigGevaccineerden");

    return volledig_gevaccineerden;
}

const std::map<std::string, int> &Gegevens::getGeleverdType() const {
    REQUIRE(correctlyInitialized(),
           "Gegevens niet correct geinitializeerd bij aanroep van getGeleverdType");
    return geleverd_type;
}




