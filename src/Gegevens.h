//
// Created by User on 19/05/2021.
//


#ifndef PROJECT_GEGEVENS_H
#define PROJECT_GEGEVENS_H
#include <iostream>
#include <map>
#include "DesignByContract.h"
#include <string>

class Gegevens {
    int gevaccineerden = 0;
    int volledig_gevaccineerden = 0;
    std::map<std::string, int> geleverd_type;
    Gegevens* _init;
public:

    /**
     * Constructor van gegevens, bevat gegevens voor een dag
     * @post correctlyInitialized()
     * @post getGevaccineerden() = getVolledigGevaccineerden() = 0
     * @post getGeleverdType().empty() = true
     */
    Gegevens();

    /**
     * vraagt het aantal (enkel) gevaccineerden op
     * @pre correctlyInitialized()
     * @return het aantal gevaccineerden
     */
    const int getGevaccineerden() const;

    /**
     * vraagt het aantal volledig gevaccineerden op
     * @pre correctlyInitialized()
     * @return het aantal volledig gevaccineerden
     */
    const int getVolledigGevaccineerden() const;

    /**
     * vraagt het aantal geleverde vaccins op per type
     * @pre correctlyInitialized()
     * @return vaccinmap met key vaccinnaam en int het aantal geleverde vaccins van dat type
     */
    const std::map<std::string, int> &getGeleverdType() const;

    /**
     * kijkt na of het gegevensobject correct geinitializeerd is
     * @return true als correct geinitializeerd
     */
    bool correctlyInitialized() const;

    /**
     * veranderd het aantal gevaccineerden naar gevaccineerden2
     * @pre correctlyInitialized()
     * @pre gevaccineerden2 >= 0
     * @param gevaccineerden2
     * @post getGevaccineerden() = gevaccineerden2
     */
    void setGevaccineerden(int gevaccineerden2);

    /**
     * veranderd het aantal volledig gevaccineerden naar vol_gevaccineerden2
     * @pre correctlyInitialized()
     * @pre vol_gevaccineerden2 >= 0
     * @param vol_gevaccineerden2
     * @post getVolledigGevaccineerden() = vol_gevaccineerden2
     */
    void setVolledigGevaccineerden(int vol_gevaccineerden2);

    /**
     * adds "aantal" vaccins bij het huidige aantal van vaccin met naam "vaccin"
     * @pre vaccins >= 0
     * @pre !vaccin_name.empty()
     * @param vaccin_name de naam van het vaccin
     * @param aantal het aantal vaccins dat toegevoegd is
     */
    void addVaccinPerType(std::string vaccin_name, int aantal);

    /**
     * constructs een copy van "to_copy"
     * @pre to_copy.correctlyInitialized()
     * @param to_copy het te kopieren object
     * @post correctlyInitialized()
     * @post getGevaccineerden() = to_copy.getGevaccineerden()
     * @post getVolledigGevaccineerden() = to_copy.getVolledigGevaccineerden()
     * @post getGeleverdType() = to_copy.getGeleverdType()
     */
    Gegevens(const Gegevens* const to_copy);

    /**
     *  output de gegevens in out
     * @post correctlyInitialized()
     * @param out de outstream
     */
    const void outputGegevens(std::ostream& out) const;
};


#endif //PROJECT_GEGEVENS_H
