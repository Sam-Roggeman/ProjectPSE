//============================================================================
// Name        : Hub.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Hub simulation in C++, Ansi-style
//============================================================================

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H
#include "Vaccinatiecentrum.h"
#include "vector"
#include <map>
#include "DesignByContract.h"
#include "VaccinType.h"


class Hub {

private:
    Hub * _initCheck;
    std::map<std::string,Vaccinatiecentrum*> vaccinatiecentra;
    std::map<std::string, VaccinType*> types;
public:
    /**Maakt een hub object aan, zet demembervariabelen op 0 en initializeerd geen vaccinatiecentrum
     *@returns hub object
     * @post this.levering = 0
     * @post this.interval = 0
     * @post this.transport = 0
     * @post this.aantal_vaccins = 0
     *@post: this->correctlyinitialized()
     * */
    Hub();


//GETTERS SETTERS


    //todo move to bedrijf
    /**Geeft het aantal vaccins in de hub terug
     *@returns aantal vaccins in de hub
     * @pre this->correctlyInitialized
     * */
    int getAantalVaccins() const;

    //todo move to bedrijf
    /**Zet het aantal vaccins in de hub op aantal_vaccins1
     * @param aantal_vaccins1 het nieuwe aantal vaccins in de hub
     * @pre aantal_vaccins1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setAantalVaccins(const int aantal_vaccins1);


    //todo move to bedrijf
    /**Geeft het aantal dagen tussen twee leveringen
     * @returns het interval
     * @pre this->correctlyinitialized()
     * */
    int getInterval() const;

    //todo move to bedrijf
    /**zet het aantal dagen tussen twee leveringen
     * @param het interval tussen twee leveringen
     * @pre interval1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setInterval(const int interval1);

    //todo move to bedrijf
    /**geeft het aantal vaccins per transport
     * @returns het aantal vaccins dat in een transport past
     * @pre this->correctlyinitialized()
     * */
    int getTransport() const;

    //todo move to bedrijf
    /**zet het aantal vaccins dat per transport past op de param transport1
     * @param transport1 het aantal vaccins dat in het transport past
     * @pre transport1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setTransport(const int transport1);

    /**voegt een centrum toe aan de hub
     * @param vaccinatiecentrum: het toe te voegen vaccinatiecentrum
     * @pre this->correctlyinitialized()
     * @pre vaccinatiecentrum->correctlyinitialized()
     * @pre vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end()
     * @post vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) != vaccinatiecentra.end()
     * @post this->vaccinatiecentra.size() += 1
     * */
    void addcentrum(Vaccinatiecentrum* const vaccinatiecentrum);

    //todo move to bedrijf
    /**trekt vaccins van aantal vaccins in de hub
     * @param vaccins: het aantal vaccins dat afgetrokken moet worden
     * @pre vaccins >=0
     * @pre this->correctlyInitialized()
     * @post aantal_vaccins -= vaccins
     * @post aantal_vaccins >= 0
     * */
    void substractVaccins(const int vaccins);

    /**kijkt na of de hub correct geinitialiseerd is
     * @return bool true als geinitializeerd
     * */
    bool correctlyInitialized() const;

    /**output de hub naar de meegegeven ostream
    * @param out: de stream waar de output heen gaat
    * @pre this->correctlyInitialized()
    * */
    void outputHub(std::ostream& out) const;

    /**output de hub naar std::cout
     * @pre this->correctlyInitialized()
     * */
    void outputHub() const;

    /**transport vaccins vanuit de hub naar alle centra, output in std::out
     * @pre this->correctlyInitialized()
     * @post voor centrum : centra geldt dat aantal_vaccins >= aantal_vaccins_start
     * @post aantal_vaccins_hub <= aantal_vaccins_hub_start
     * */
    void transportToCentra();

    /**transport vaccins vanuit de hub naar alle centra
     * @param out: de ostream waar outgeput wordt
     * @pre this->correctlyInitialized()
     * @post voor centrum : centra geldt dat aantal_vaccins_centrum >= aantal_vaccins_centrum_start
     * @post voor centrum : centra geldt dat aantal_vaccins_centrum <= 2* capaciteit
     * @post aantal_vaccins_hub <= aantal_vaccins_hub_start
     * */
    void transportToCentra(std::ostream& out);

    //todo move to bedrijf



    //todo move to bedrijf
    /**kijkt na of het momenteel een leveringsdag is
     * @param dag: het nummer van de huidige dag
     * @returns true als er geleverd wordt aan de hub
     * @pre dag >=0
     * @pre this->correctlyInitialized()
     */
    bool isLeveringsDag(const int dag) const;

    /**alle centra van de hub voeren vaccinaties uit
     * @param out: de output stream die de output binnenkrijgt
     * @pre this->correctlyInitialized()
     * @post voor elk centrum geldt dat aantal_vaccins <= aantal_vaccins_start
     * @post voor elk centrum geldt dat gevaccineerden >= gevaccineerden_start
     * * */
    void vaccineren(std::ostream& out);

    /**alle centra van de hub voeren vaccinaties uit, output gaat naar std::out
     * @pre this->correctlyInitialized()
     * @post voor elk centrum geldt dat aantal_vaccins <= aantal_vaccins_start
     * @post voor elk centrum geldt dat gevaccineerden >= gevaccineerden_start
     * */
    void vaccineren();

    //TODO delete
    /**Veranderd het aantal vaccins dat geleverd wordt op leveringsdag
     * @param int: het aantal vaccins dat aan de
     * @pre levering >= 0
     * @pre this->correctlyInitialized()
     * @post this->levering == levering1
    * */
    void setLevering(const int levering1);

    //TODO delete
    /**Vraagt de grote van eenlevering op
     * @return de grote van een levering
     * @pre this->correctlyInitialized()
     * */
    int getLevering() const;

    /**checkt of het vaccineren klaar is (iedereen is gevaccineerd)
     * @return true als er 0 ongevaccineerden meer zijn
     * @pre this->correctlyInitialized()
     * */
    bool notDone() const;

    /**berekent het aantal ongevaccineerden
     * @return som van alle ongevaccineerden in alle centra
     * @pre this->correctlyInitialized()
     * */
    int aantalOngevaccineerden() const;

    /**kijkt na of de hub compleet geinitializeerd is
     * @return true als compleet geinitalizeerd
     * @pre this->correctlyInitialized()
     * */
    bool completelyInitialized() const;

    /**cleart de hub
     *@pre this->correctlyInitialized
     * @post getTransport() >= 0
     * @post getInterval() >= 0
     * @post getAantalVaccins() >=0
     * @post getLevering() >= 0
     * */
    void clear();

    void addType(VaccinType *bedrijf1);
};


#endif //PROJECT_HUB_H
