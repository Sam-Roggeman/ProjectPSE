//
// Created by User on 19/05/2021.
//


#ifndef PROJECT_GEGEVENS_H
#define PROJECT_GEGEVENS_H
#include <iostream>
#include <map>
#include <string>

class Gegevens {
    int gevaccineerden = 0;
    int totaal_gevaccineerden = 0;
    std::map<std::string, int> geleverd_type;
    Gegevens* _init;
public:
    Gegevens();

    bool correctlyInitialized();

    void set_gevaccineerden(int gev);

    void set_totaal_gevaccineerden(int gev);

    void add_vaccin_per_type(std::string vaccin, int aantal);

    Gegevens(const Gegevens& gegevens);

    void outputGegevens(std::ostream& out) const;
};


#endif //PROJECT_GEGEVENS_H
