//============================================================================
// Name        : Simulation.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================

#ifndef PROJECT_SIMULATION_H
#define PROJECT_SIMULATION_H
#include <iostream>
#include <fstream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include <string>
#include "DesignByContract.h"
#include <map>
#include "Gegevens.h"
#include <stdio.h>
#include <unistd.h>
#include "TicTacToeUtils.h"


class VaccinInterface;

class Simulation {
    Simulation *_initcheck;
    std::vector<Hub *> hubs;
    std::vector<Vaccinatiecentrum *> vaccinatiecentra;
    int dag;
    std::map<int, Gegevens*> statistische_gegevens;
public:
    /**Geeft de huidige dag van de simulatie terug
     * @returns Huidige dag
     * @pre this->correctlyinitialized()
     */
    int getDag() const;

    /**Zet de huidige dag in de variable "dag"
     *
     * @param dag: De huidige dag die in de simulatie wordt gezet
     * @pre this->correctlyinitialized()
     * @pre De dag is een natuurlijke getal
     */
    void setDag(int dag);

    /**Een functie die alles in de hub en het vaccinatiecentrum output door cout
     * @pre this->correctlyInitialized()
     * @pre this->getHub()->correctlyInitialized()
     */
    void outputSimulation();


    /**Een functie die alles in de hub en de vaccinatiecentra output naar een gegeven ostream
     * @param out: De ostream waar de gegeven output naartoe gaat
     * @pre this->correctlyInitialized()
     * @pre this->getHub()->correctlyInitialized()
     */
    void outputSimulation(std::ostream &out);

    /**Dit is een automatische simulatie van de transport van vaccins tot een
     * gegeven einddag en de output wordt bepaald door de gegeven ostream
     * @param start: De gegeven startdag
     * @param eind: De gegeven einddag
     * @param out: De ostream waar de output naartoe gaat
     * @pre this->getHub()->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @pre 0 <= start < eind
     * @post this->dag == eind
     */
    void autoSimulation(int start, int eind, std::ostream &out);

    /**Dit is een automatische simulatie van de transport van vaccins tot
     * een gegeven einddag en de output hiervan wordt gegeven door cout
     * @param start: De gegeven startdag
     * @param eind: De gegeven einddag
     * @pre this->getHub()->correctlyInitialized()
     * @pre 0 <= start < eind
     * @pre this->correctlyInitialized()
     * @post this->dag == eind
     */
    void autoSimulation(int start, int eind);

    /**Dit is een automatische simulatie van de transport van vaccins tot
     * elke persoon in elk vaccinatiecentrum gevaccineerd is en deze output met cout
     * @pre this->getHub()->correctlyInitialized()
     * @pre this->correctlyInitialized()
     * @pre this->getHub()->completelyInitialized()
     * @post this->getHub()->getAantalOngevaccineerden() == 0
     */
    void autoSimulationUntilDone();

    /**Dit is een automatische simulatie van de transport van vaccins tot elke
     * persoon in elk vaccinatiecentrum gevaccineerd is en de waar de output bepaald wordt door ostream
     * @param out: De ostream die bepaalt wat de locatie van de output wordt
     * @pre this->getHub()->correctlyInitialized()
     * @pre this->getHub()->completelyInitialized()
     * @pre this->correctlyInitialized()
     * @post this->getHub()->getAantalOngevaccineerden() == 0
     */
    void autoSimulationUntilDone(std::ostream &out);


    /**Voegt een gegeven vaccinatiecentra toe aan de simulatie
     *
     * @param v: Een gegeven vaccinatiecentrum die aan de simulatie wordt toegoegd
     * @pre v->correctlyInitialized()
     * @pre v->completelyInitialized()
     * @pre this->correctlyInitialized()
     * @pre this->getHub()->getVaccinatiecentra().find(vaccinatiecentrum->getNaamCentrum()) == vaccinatiecentra.end()
     * @post this->getHub()->getVaccinatiecentra().find(vaccinatiecentrum->getNaamCentrum()) != vaccinatiecentra.end()
     * @post this->getHub()->getVaccinatiecentra().size() += 1
     */
    void addcentrum(Vaccinatiecentrum *v, Hub *h);

    /**Zorgt ervoor dat de simulatie van de huidige dag naar de volgende dag gaat
     * @pre this->correctlyInitialized()
     * @post dag == startdag +1
     */
    void nextDay();

    /**Kijkt na of de simulatie correct geinitialiseerd is
     * @return Een boolean: True als de simulatie juist is geinitialiseerd
     */
    bool correctlyInitialized() const;

    /**Dit cleared heel de simulatie
     */
    void clear();

    /**Maakt een grafische impressie van de huidige staat van de simulatie
     * @param out de ostream waarnaar de impressie wordt uitgeput
     * @pre this->correctlyinitialized()
     * @pre this->getHub()->correctlyinitialized()
     * @pre this->getHub()->completlyInitialized()
     * */
    void impressie(std::ostream &out);

    /**
     * maakt een 3d-afbeelding van de simulatie
     * @pre correctlyInitialized()
     * @pre DirectoryExists(path_to_safe_dir)
     * @param path_to_engine pad naar de engine
     * @param path_to_safe pad waar de afbeelding opgeslagen moet worden
     * @param name naam die de file zal krijgen
     * @post FileExists((path_to_safe_dir+"/"+name+".ini"))
     * @post FileExists((path_to_safe_dir+"/"+name+".bmp"))
     */
    void graphicIntegration(std::string path_to_engine, std::string path_to_safe, std::string name);

    /**
     * @pre correctlyInitialized()
     * geeft een lijst met pointers naar alle hubs weer
     * @return vector met hub-pointers
     */
    const std::vector<Hub *> &getHubs() const;

    /**
     * voegt pointer toe als hub aan de simulatie, hubs moeten in volgorde worden toegevoegd startent met getID() == 0
     * @pre correctlyInitialized()
     * @pre hub1.correctlyInitialized()
     * @pre hub1->getID() == getHubs().size()
     * @param hub1 de pointer naar de toe te voegen hub
     * @post getHubs().size() += 1
     */
    void addHub(Hub *hub1);

    /**
     * voegt pointer toe als centrum aan de simulatie
     * @pre correctlyInitialized()
     * @pre centrum->correctlyInitialized()
     * @param centrum de pointer naar het toe te voegen centrum
     * @post getVaccinatiecentra().size() += 1
     */
    void addcentrumToSim(Vaccinatiecentrum *centrum);

    /**
     * @pre correctlyInitialized()
     * neemt de som van alle gevaccineerden uit alle centra
     * @return aantal gevaccineerden
     */
    int getAantalGevaccineerden();

    /**
     * @pre correctlyInitialized()
     * neemt de som van alle volledig-gevaccineerden uit alle centra
     * @return aantal gevaccineerden
     */
    int getAantalVolGevaccineerden();

    /**
     * constructor van simulatie
     * @post correctlyInitialized()
     * @post getDag() ==0
     * @post getGegevens.at(-1) = een leeg gegevensobject
     */
    Simulation();

    /**
     * @pre correctlyInitialized()
     * @return vector met alle vaccinatiecentra van de simulatie
     */
    const std::vector<Vaccinatiecentrum *> &getVaccinatiecentra() const;

    /**
     * @pre correctlyInitialized()
     * @return true als iedereen gevaccineerd is
     */
    bool notDone();

    /**
     * @pre correctlyInitialized()
     * output de gegevens naar out
     * @param out de ostream
     */
    void outputGegevens(std::ostream &out);

    /**
     * copy constructor voor simulatie
     * @pre sim->correctlyInitialized()
     * @param sim de te-kopieren simulatie
     * @post correctlyInitialized()
     * @post getDag() == sim->getDag()
     * @post getHubs().size() == sim->getHubs().size()
     * @post sim->getVaccinatiecentra().size() == getVaccinatiecentra().size()
     */
    Simulation(const Simulation* const sim);

    /**
     * deconstructor voor simulatie
     * @pre correctlyInitialized()
     */
    ~Simulation();

    /**
     * simuleert een dag (treansport + vaccineren + opslaan van gegevens)
     * @pre correctlyInitialized()
     * @pre getStatistischeGegevens().find(getDag()-1) != getStatistischeGegevens().end()
     * @param out de ostream
     */
    void simulateDay(std::ostream &out);

    /**
     * kijkt na of de hoeveelheid vaccins dat verstuurd zou moten worden toegestaan is
     * @param vaccins aantal vaccins dat gestuurd zou moeten worden
     * @param hub_id id van de hub
     * @param name_centrum naam van het centrum waarnaar vaccins gestuurd wordt
     * @return true als het centrum de transactie toestaat
     */
    bool isAllowed(const int vaccins, const int hub_id, const std::string name_centrum);

    /**
     * send de vaccins naar name_centrum vanuit hub_id
     * @pre getHubs().size()>hub_id
     * @pre getHubs().at(hub_id)->getVaccinatiecentra().find(name_centrum) != getHubs().at(hub_id)->getVaccinatiecentra().end()
     * @param vaccins de hoeveelheid vaccins
     * @param hub_id het id van de hub
     * @param name_centrum de naam van het centrum
     * @param out de outputstream
     */
    void sendVaccins(const int vaccins, const unsigned int hub_id, const std::string name_centrum, std::ostream &out);

    /**
     * siimuleert een dag met manuele input (die meegegeven wordt in een map)
     * @pre voor alle transacties geldt dat die toegestaan is
     * @param vaccins_to_centra map vaccinatiecentrum_naam -> hubID -> hoeveelheid
     * @param out de ostream
     */
    void simulateManual(std::map<std::string, std::map<int, int>> vaccins_to_centra, std::ostream &out);

    /**
     * @pre correctlyInitialized()
     * geeft de som van het aantal inwoners in de centra terug
     * @return
     */
    int getAantalInwoners();

    /**
     * @pre correctlyInitialized()
     * @return geeft een map terug met dag -> gegevens-object pointer
     */
    const std::map<int, Gegevens *> &getStatistischeGegevens() const;

    /**
     * vraagt een pointer naar het object van de gegevens van _dag op
     * @param _dag de dag
     * @pre _dag >= -1
     * @return pointer naar de gegevens van _dag
     */
    const Gegevens* getGegevens(int _dag);

    void exportToGif(std::string filepat,std::string path_to_bmps);
};

#endif //PROJECT_SIMULATION_H
