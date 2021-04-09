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
     *@post: this->correctlyinitialized()
     *@post this->types.size == 0
     *@post this->vaccinatiecentra.size == 0
     * */
    Hub();


//GETTERS SETTERS

    /**voegt een centrum toe aan de hub
     * @param vaccinatiecentrum: het toe te voegen vaccinatiecentrum
     * @pre this->correctlyinitialized()
     * @pre vaccinatiecentrum->correctlyinitialized()
     * @pre vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end()
     * @post vaccinatiecentra.find(vaccinatiecentrum->getNaamCentrum()) != vaccinatiecentra.end()
     * @post this->vaccinatiecentra.size() += 1
     * */
    void addcentrum(Vaccinatiecentrum* const vaccinatiecentrum);


    /**kijkt na of de hub correct geinitialiseerd is (= zowel hub als centra als types )
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
    void transportToCentra(std::string naam_type);

    /**transport vaccins vanuit de hub naar alle centra
     * @param out: de ostream waar outgeput wordt
     * @pre this->correctlyInitialized()
     * @post voor centrum : centra geldt dat aantal_vaccins_centrum >= aantal_vaccins_centrum_start
     * @post voor centrum : centra geldt dat aantal_vaccins_centrum <= 2* capaciteit
     * @post aantal_vaccins_hub <= aantal_vaccins_hub_start
     * */
    void transportToCentra(std::string naam_type, std::ostream &out);




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

    /**Kijkt na of de hub compleet geinitializeerd is
     * @return true als compleet geinitalizeerd
     * @pre this->correctlyInitialized()
     * */
    bool completelyInitialized() const;

    /**cleart de hub
     *@pre this->correctlyInitialized
     * @post this->types.size == 0
     * @post this->vaccinatiecentra.size == 0
     * */
    void clear();

    /**
     * voegt een vaccintype toe aan de hub
     * @param type het type vaccin dat toegevoegd wordt aan de hub
     * @pre type->completlyInitialized
     * @pre type->correctlyInitialized
     * @pre this->types.find(type->getName()) == this->types.end()
     * @post this->types.find(type->getName()) != this->types.end()
     * @post this->types.size_start +1 == this->types.size
     */
    void addType(VaccinType *type);
};


#endif //PROJECT_HUB_H
