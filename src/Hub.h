//
// Created by said2 on 1-3-2021.
//

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H
#include "Vaccinatiecentrum.h"
#include "vector"
#include <map>
#include "DesignByContract.h"


class Hub {

private:
    int aantal_vaccins;
    int levering;
    int interval;
    int transport;
    std::map<std::string,Vaccinatiecentrum*> vaccinatiecentra;
public:
    /*Maakt een hub object aan, zonder de membervariabelen te initializeren
     *@returns hub object
     * */
    Hub();

    /*Geeft het aantal vaccins in de hub terug
     *@returns aantal vaccins in de hub
     * */
    int getAantalVaccins() const;

    /*Geeft het aantal dagen tussen twee leveringen
     * @returns het interval
     * */
    int getInterval() const;

    /*zet het aantal dagen tussen twee leveringen
     * @param het interval tussen twee leveringen
     * */
    void setInterval(int interval1);

    /*geeft het aantal vaccins per transport
     * @returns het aantal vaccins dat in een transport past
     * */
    int getTransport() const;

    /*zet het aantal vaccins dat per transport past op de param transport1
     * */
    void setTransport(int transport1);

    /*voegt een centrum toe aan de hub
     * @param vaccinatiecentrum: het toe te voegen vaccinatiecentrum
     * */
    void addcentrum(Vaccinatiecentrum* vaccinatiecentrum);

    /*trekt vaccins van aantal vaccins in de hub
     * @param vaccins: het aantal vaccins dat afgetrokken moet worden
     * */
    void substractVaccins(int vaccins);

    /*kijkt na of de hub correct geinitializeerd is
     * */
    bool correctlyInitialized() const;

    /*output de hub naar de meegegeven ostream
     * @param out: de stream waar de output heen gaat
     * */
    void outputHub() const;

    /*transport vaccins vanuit de hub naar alle centra, output in std::out
     * */
    void transportToCentra();

    /*transport vaccins vanuit de hub naar alle centra
     * @param out: de ostream waar outgeput wordt
     * */
//    void transportToCentra(std::ostream &out);

    /*er wordt een lading aan de hub geleverd
     * */
    void leveringToHub();

    /*kijkt na of het momenteel een leveringsdag is
     * @param dag: het nummer van de huidige dag
     * @returns true als er geleverd wordt aan de hub
     */
    bool isLeveringsDag(int dag);

    /*alle centra van de hub voeren vaccinaties uit
     * @param out: de output stream die de output binnenkrijgt
     * */
//    void vaccineren(std::ostream out);

    /*alle centra van de hub voeren vaccinaties uit, output gaat naar std::out
     * */
    void vaccineren();

    /*Veranderd het aantal vaccins dat geleverd wordt op leveringsdag
     * @param int: het aantal vaccins dat aan de
     * */
    void setLevering(int levering);

};


#endif //PROJECT_HUB_H
