//
// Created by User on 1/03/2021.
//

#ifndef PROJECT_VACCINATIECENTRUM_H
#define PROJECT_VACCINATIECENTRUM_H

#include "iostream"
#include <string>
#include <math.h>

class Vaccinatiecentrum {
    Vaccinatiecentrum * _initCheck;
    int aantal_vaccins;
    std::string naam_centrum;
    std::string adres_centrum;
    int aantal_inwoners;
    int capaciteit;
    int aantal_gevaccineerden;
public:

    /*maakt een niet vaccinatiecentrum object aan
     * @return vaccinatiecentrum
     * */
    Vaccinatiecentrum();

    /*returnt de naam van het centrum
     * */
    const std::string &getNaamCentrum() const;

    /*veranderd de naam van het centrum naar naamCentrum
     * */
    void setNaamCentrum(const std::string &naamcentrum);

    /*returnt het adres van het centrum
     * */
    const std::string &getAdresCentrum() const;

    /*verandert het adres van het centrum naar adrescentrum
     */
    void setAdresCentrum(const std::string &adrescentrum);

    /*returnt het aantal inwoners dat bij het centrum hoort
     * */
    int getAantalInwoners() const;

    /*zet het aantal inwoners dat bij het centrum hoort op aantal_inwoners
     * */
    void setAantalInwoners(int aanta_inwoners);

    /*returnt de vaccinatiecapaciteit per dag
     * */
    int getCapaciteit() const;

    /*zet de vaccinatiecapaciteit op capaciteit1
     * */
    void setCapaciteit(int capaciteit1);

    /*kijkt na of het cenrum correct geinitializeerd is
     * @returns true als correct
     * */
    bool correctlyInitialized() const;

    /*returnt het aantal vaccins in het centrum
     * */
    int getAantalVaccins() const;

    /*voeg vaccins toe aan het centrum
     * @param aantal_vaccins het aantal vaccins dat toegevoegd wordt
     * */
    void addVaccins(int aantal_vaccins);

    /*add aantal_gevaccineerden toe aan het totaal aantal gevaccineren
     * @param aantal_gevaccineerden: het aantal mensen dat gevaccineerd is
     * */
    void addGevaccineerden(int aantal_gevaccineerden);

    /*returt het aantal mensen dat gevaccineerd is
     * */
    int getAantalGevaccineerden() const;

    /*returnt het aantal ongevaccineerden
     * @returnt : aantal_inwoners - aantal_gevaccineerden
     * */
    int aantalOngevaccineerden() const;

    /*vaccinaties worden uitgevoerd en output gaat naar std::cout
     * */
    void vaccineren();

    void vaccineren(std::ostream& out);

    /*substract het aantal van het huidige aantal vaccins
     * */
    void substractVaccins(int aantal);

    /*vaccinaties worden uitgevoerd en output gaat naar out
     * @param out: de outstream waarnaar de output gestuurt wordt
     * */
//    void vaccineren(std::ostream &out);
};


#endif //PROJECT_VACCINATIECENTRUM_H
