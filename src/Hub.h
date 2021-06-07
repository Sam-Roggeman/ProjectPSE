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
#include "Gegevens.h"
#include <string>
#include <limits>
#include <map>
#include <cmath>
#include <iterator>

class Hub {

private:
    Hub * _initCheck;
    std::map<std::string,Vaccinatiecentrum*> vaccinatiecentra;
    std::map<std::string, VaccinType*> types;
    std::map<Vaccinatiecentrum*,int> aantal_ladingen_vorige_dag;
    const int _hub_ID;
public:
    /**Maakt een hub object aan, zet demembervariabelen op 0 en initializeerd geen vaccinatiecentrum
     *@returns hub object
     *@pre ID >= 0
     *@param ID het id van de hub
     *@post: this->correctlyinitialized()
     *@post this->getTypes().size == 0
     *@post this->getVaccinatiecentra().size == 0
     *@post this->getID() == ID
     * */
    Hub(int ID);

    /**
     * berekend het totaal aantal gereserveerde vaccins van alle types in de hub
     * @return totaal aantal gereserveerde vaccins
     * @post returnvalue >= 0
     * */
    int getAantalGer();


    /**voegt een centrum toe aan de hub
     * @param const vaccinatiecentrum: het toe te voegen vaccinatiecentrum
     * @pre this->correctlyinitialized()
     * @pre vaccinatiecentrum->correctlyinitialized()
     * @pre getVaccinatiecentra().find(vaccinatiecentrum->getNaamCentrum()) == getVaccinatiecentra().end()
     * @post getVaccinatiecentra().find(vaccinatiecentrum->getNaamCentrum()) != getVaccinatiecentra().end()
     * @post this->getVaccinatiecentra().size() += 1
     * @post getAantalLadingenVorigeDag().at(vaccinatiecentrum) == 0
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
     * @post aantal hernieuwingen + gekoelde vaccins dat naar centrum gestuurd wordt <= capaciteit van centrum
     * @post voor centrum : centra geldt dat aantal_vaccins >= aantal_vaccins_start voor elk type
     * @post aantal_vaccins_hub <= aantal_vaccins_hub_start
     * */
    void transportToCentra2(int dag, Gegevens *gegevens);

    /**transport vaccins vanuit de hub naar alle centra
     * @param out: de ostream waar outgeput wordt
     * @pre this->correctlyInitialized()
     * @post aantal hernieuwingen + gekoelde vaccins dat naar centrum gestuurd wordt <= capaciteit van centrum
     * @post voor centrum : centra geldt dat aantal_vaccins >= aantal_vaccins_start voor elk type
     * @post aantal_vaccins_hub <= aantal_vaccins_hub_start
     * */
    void transportToCentra2(int dag, std::ostream &out, Gegevens *gegevens);

    /**alle centra van de hub voeren vaccinaties uit
     * @param out: de output stream die de output binnenkrijgt
     * @pre this->correctlyInitialized()
     * @post voor elk centrum geldt dat aantal_vaccins <= aantal_vaccins_start
     * @post voor elk centrum geldt dat gevaccineerden >= gevaccineerden_start
     * * */
    void vaccineren(int dag, std::ostream &out);

    /**alle centra van de hub voeren vaccinaties uit, output gaat naar std::out
     * @pre this->correctlyInitialized()
     * @post voor elk centrum geldt dat aantal_vaccins <= aantal_vaccins_start
     * @post voor elk centrum geldt dat gevaccineerden >= gevaccineerden_start
     * */
    void vaccineren(int dag);

    /**checkt of het vaccineren klaar is (iedereen is gevaccineerd)
     * @return true als er 0 volledig ongevaccineerden meer zijn
     * @pre this->correctlyInitialized()
     * */
    bool notDone() const;

    /**berekent het aantal ongevaccineerden
     * @return som van alle ongevaccineerden in alle centra
     * @pre this->correctlyInitialized()
     * */
    int aantalOngevaccineerden() const;

    /**Kijkt na of de hub compleet geinitializeerd is (centra compleet geinitializeerd + minstens een centrum)
     * @return true als compleet geinitalizeerd
     * @pre this->correctlyInitialized()
     * */
    bool completelyInitialized() const;

    /**cleart de hub
     *@pre this->correctlyInitialized()
     * @post this->getTypes().size == 0
     * @post this->getVaccinatiecentra().size == 0
     * */
    void clear();

    /**
     * voegt een vaccintype toe aan de hub
     * @param type het type vaccin dat toegevoegd wordt aan de hub
     * @pre type->completlyInitialized()
     * @pre type->correctlyInitialized()
     * @pre this->getTypes().find(type->getName()) == this->getTypes().end()
     * @post this->getTypes().find(type->getName()) != this->getTypes().end()
     * @post this->getTypes().size_start +1 == this->getTypes().size
     */
    void addType(VaccinType *type);

    /** geeft het totaal aantal vaccins terug dat in de hub zit
     * @pre this->correctlyinitialized()
     * @return som van aantal vaccins van elk type in de hub
     */
    int getAantalVac() const;

    /** maakt een grafische impressie van de huidige staat van de hub
     * @param out de ostream waarnaar de impressie wordt gestuurd
     * @pre this->correctlyinitialized()
     * @pre this->completlyinitialized()
     */
    void impressie(std::ostream &out);


    /**
     * zet een kopie van de map met getTypes() in elk centrum
     * @pre this->correctlyinitialized()
     * @post vaccinatiecentrum->getTypes().size() += getTypes().size() voor elk vaccinatiecentrum
     */
    void insertCentrumTypes() const;

    /**
     * vaccins worden geleverd aan de hub indien het een leveringsdag is
     * @param dag de huidige dag
     * @pre dag >=0
     * @pre this->correctlyInitialized()
     * @post voor elk type in getTypes() geld dat type->getAantalVaccins() >= type->getAantalVaccins() bij de start
     */
    void vacLeveringen(int dag);

    /**
     * kijkt na wat het kortste interval is tot de volgende levering
     * @param dag de huidige dag
     * @pre dag >=0
     * @return het aantal dagen tot de volgende levering
     */
    int nextLevDag(int dag) const;

    /**
     * berekent het aantal onvolledig gevaccineerden (inwoners - volledig gevaccinneerden)
     * @pre correctlyInitialized()
     * @return  som van aantal ongevaccinneerden in alle centra
     */
    int aantalOnvolledigGev() const;

    /**
     * @pre correctlyInitialized()
     * geeft een map terug die de centra bevat
     * @return map met vaccinecentrum name naar vaccinatie centrum pointer
     */
    const std::map<std::string, Vaccinatiecentrum *> &getVaccinatiecentra() const;

    /**
    * @pre correctlyInitialized()
    * geeft een map terug die de VaccinTypes bevat
    * @return map met VaccinType name naar VaccinType pointer
    */
    const std::map<std::string, VaccinType *> &getTypes() const;

    /**
     * @pre correctlyInitialized()
     * vraagt een map op die vaccinatiecentrum pointer linkt met het aantal ladingen dat de vorige dag getransporteerd werd
     * @return map met key vaccinatiecentrum* en value aantal ladingen van de vorige dag
     */
    const std::map<Vaccinatiecentrum *, int> &getAantalLadingenVorigeDag() const;

    /**
     * stelt de map aaantalLadingenVorigeDag in in de hub
     * @pre correctlyInitialized()
     * @param aantalLadingenVorigeDag de meegegeven map
     * @post aantalLadingenVorigeDag.size() == getAantalLadingenVorigeDag().size()
     */
    void setAantalLadingenVorigeDag(const std::map<Vaccinatiecentrum *, int> &aantalLadingenVorigeDag);

    /**
     * @pre correctlyInitialized()
     * @return ID van de hub
     */
    int getID();

    /**
     * @pre correctlyInitialized()
     * berekent het aantal mensen dat 1 (onvolledig) gevaccineerd is
     * @return aantal deels gevaccineerden in de hub
     */
    int getAantalEnkelGevaccineerden();

    /**
     * @pre correctlyInitialized()
     * berekent het aantal mensen dat volledig gevaccineerd is
     * @return aantal gevaccineerden in de hub
     */
    int getAantalVolGevaccineerden();

    /**
     * copy constructor
     * @pre pHub->correctlyInitialized()
     * @post correctlyInitialized()
     * @param pHub de te-kopieren hub
     * @param vaccinatiecentra_vector vector met pointers naar alle centra
     * @post pHub->getID() == getID()
     * @post pHub->getTypes().size() == getTypes().size()
     * @post pHub->getVaccinatiecentra().size() == getVaccinatiecentra().size()
     * @post pHub->getAantalLadingenVorigeDag().size() == getAantalLadingenVorigeDag().size()
     */
    Hub(Hub *const pHub, std::map<std::string, Vaccinatiecentrum *> vaccinatiecentra_vector);

    /**
     * @pre correctlyInitialized()
     * @pre vaccins > = 0
     * @pre name_centrum.length() >=0
     * @param vaccins het aantal dat toegevoegd wordt
     * @param name_centrum naam van het centrum
     * @return bool true als de capaciteit deze hoeveelheid toelaat
     */
    bool isAllowed(const int vaccins, const std::string name_centrum);

    /**
     * @pre correctlyInitialized()
     * @pre vaccins > = 0
     * @pre name_centrum.length() >=0
     * @param vaccins aantal dat verstuurd wordt
     * @param name_centrum naam van het centrum waarnaar verstuurd wordt
     * @param dag de huidige dag
     * @param out outstream
       */
    void sendVaccins(const int vaccins, const std::string name_centrum, const int dag, std::ostream &out);
};


#endif //PROJECT_HUB_H
