//============================================================================
// Name        : Vaccinatiecentrum.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccinatiecentrum in C++, Ansi-style
//============================================================================

#ifndef PROJECT_VACCINATIECENTRUM_H
#define PROJECT_VACCINATIECENTRUM_H

#include "DesignByContract.h"
#include "iostream"
#include <string>
#include <math.h>
#include <map>

class Vaccinatiecentrum {
    Vaccinatiecentrum * _initCheck;
    std::map<std::string,int> vaccins;
    std::string naam_centrum;
    std::string adres_centrum;
    int aantal_inwoners;
    int capaciteit;
    int aantal_gevaccineerden;
public:

    /**maakt een vaccinatiecentrum object aan
     * @return vaccinatiecentrum
     * @post this.correctlyInitialized()
     * */
    Vaccinatiecentrum();

//GETTERS SETTERS
    /**veranderd de naam van het centrum naar naamCentrum
     * @param naamcentrum: nieuwe naam van het centrum
     * @pre this.correctlyInitialized()
     * */
    void setNaamCentrum(const std::string &naamcentrum);

    /**returnt de naam van het centrum
     * @return de naam van het centrum
     * @pre this.correctlyInitialized()
     * */
    const std::string &getNaamCentrum() const;

    /**verandert het adres van het centrum naar adrescentrum
     * @param naamcentrum: nieuwe adres van het centrum
     * @pre this.correctlyInitialized()
     */
    void setAdresCentrum(const std::string &adrescentrum);

    /**returnt het adres van het centrum
     * @return het adres van het centrum
     * @pre this.correctlyInitialized()
     * */
    const std::string &getAdresCentrum() const;

    /**zet het aantal inwoners dat bij het centrum hoort op aantal_inwoners
     * @param aantal: nieuwe aantal inwoners
     * @pre aantal_inwoners >= 0
     * @pre this.correctlyInitialized()
     * */
    void setAantalInwoners(int aantal);

    /**returnt het aantal inwoners dat bij het centrum hoort
     * @return het aantal inwoners
     * @pre this.correctlyInitialized()
     * */
    int getAantalInwoners() const;

    /**returnt het aantal vaccins in het centrum
     * @return het aantal vaccins in het centrum
     * @pre this.correctlyInitialized()
     * */
    int getAantalVaccinsVanType(std::string naam_type) const;

    /**zet het aantal vaccins in het centrum op aantal
     * @param het nieuwe aantal vaccins
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post this->vaccins[naam_type] == aantal
     */
    void setAantalVaccins(std::string naam_type, int aantal);

    /**zet de vaccinatiecapaciteit op capaciteit1
     * @param aantal: De nieuwe capaciteit van het centrum
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * */
    void setCapaciteit(int aantal);

    /**returnt de vaccinatiecapaciteit per dag
     * @return de capaciteit van het centrum
     * @pre this.correctlyInitialized()
     * */
    int getCapaciteit() const;

    /**zet de gevaccineerden op aantalGevaccineerden
     * @param aantal: het nieuwe aantal gevaccineerden
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * */
    void setAantalGevaccineerden(int aantal);

    /**returt het aantal mensen dat gevaccineerd is
     * @return het aantal gevaccineerden
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * */
    int getAantalGevaccineerden() const;

//VACCIN OPERATIONS
    /**substract het aantal van het huidige aantal vaccins van dat type
     * @param aantal: het aantal vaccins dat geleverd werd werd
     * @param naam_type de naam van het type dat geleverd wordt
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post vaccins[naam_type] += aantal
     * */
    void addVaccins(int aantal, std::string naam_type);

    /**substract het aantal van het huidige aantal vaccins van dat type
     * @param naam_type de naam van het type dat geleverd wordt
     * @param aantal: het aantal vaccins dat gebruikt werd
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post vaccins[naam_type] -= aantal
     * @post aantal_vaccins >= 0
     * */
    void substractVaccins(int aantal, std::string naam_type);

// GEVACCINEERDEN OPERATIONS
    /**add aantal_gevaccineerden toe aan het totaal aantal gevaccineren
     * @param aantal_gevaccineerden: het aantal mensen dat gevaccineerd werd
     * @pre this.correctlyInitialized()
     * @pre aantal_gevaccineerden >= 0
     * @post gevaccineerden += aantal_gevaccineerden
     * */
    void addGevaccineerden(int aantal_gevaccineerden);

    /**returnt het aantal ongevaccineerden
     * @returnt : aantal_inwoners - aantal_gevaccineerden
     * @pre this.correctlyInitialized()
     * */
    int aantalOngevaccineerden() const;

//METHODS
    /**kijkt na of het cenrum correct geinitializeerd is
     * @returns true als correct
     * */
    bool correctlyInitialized() const;

    /**vaccinaties worden uitgevoerd en output gaat naar std::cout
    * @param out: de outstream waarnaar de output gestuurt wordt
     * @pre this.correctlyInitialized()
     * @post aantal_vaccins <= aantal_vaccins_start
     * @post aantal_gevaccineerden <= aantal_gevaccineerden_start
     * */
    void vaccineren(std::string naam_type);

    /**vaccinaties worden uitgevoerd en output gaat naar out
    * @param out: de outputstream waarnaar de output gestuurt wordt
     * @pre this.correctlyInitialized()
     * @post aantal_vaccins <= aantal_vaccins_start
     * @post aantal_gevaccineerden >= aantal_gevaccineerden_start
     * */
    void vaccineren(std::string naam_type, std::ostream &out);

    /**kijkt na of een centrum volledig geinitializeerd is
     * @pre this.correctlyInitialized()
     *  @return true als completelyInitialized (strikt positieve capaciteit, een naam, een adres en strikt positief aantal inwoners)
     * */
    bool completelyInitialized() const;

    int getAantalVac()const;

    void impressie(std::ostream &out);
};


#endif //PROJECT_VACCINATIECENTRUM_H
