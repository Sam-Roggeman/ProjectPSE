//
// Created by User on 19/05/2021.
//

#include "Gegevens.h"

Gegevens::Gegevens() {
    _init = this;
}

void Gegevens::set_gevaccineerden(int gev) {
    gevaccineerden = gev;
}

void Gegevens::set_totaal_gevaccineerden(int gev){
    totaal_gevaccineerden = gev;
}

void Gegevens::add_vaccin_per_type(std::string vaccin, int aantal) {
    geleverd_type[vaccin] += aantal;
}

bool Gegevens::correctlyInitialized() {
    return this == _init;
}

Gegevens::Gegevens(const Gegevens & gegevens) {
    _init = this;
    this->totaal_gevaccineerden = gegevens.totaal_gevaccineerden;
    this->gevaccineerden = gegevens.gevaccineerden;
    this->geleverd_type.clear();
    this->geleverd_type.insert(gegevens.geleverd_type.begin(),gegevens.geleverd_type.end());
}

void Gegevens::outputGegevens(std::ostream &out) const {
    out<<'\t' << "Aantal geleverde vaccins per type:" << std::endl;
    for (std::map<std::string,int>::const_iterator it = this->geleverd_type.begin(); it != geleverd_type.end(); it++){
        out << "\t\t" << it->first << ": " << it->second << std::endl;
    }
    out << "\t Aantal onvolledig gevaccineerden:" << this->gevaccineerden <<std::endl;
    out << "\t Aantal volledig gevaccineerden:" << this->totaal_gevaccineerden<<std::endl;


}




