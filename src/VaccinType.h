//
// Created by User on 7/04/2021.
//

#ifndef PROJECT_VACCINTYPE_H
#define PROJECT_VACCINTYPE_H

#include <string>
#include "DesignByContract.h"

class VaccinType {
    std::string name;
    int levering;
    int transport;
    int interval;
    int aantal_vaccins;
    int hernieuwing;
    int temperatuur;
    int gereserveerd;


private:
    VaccinType* init_check;
public:
    int getGereserveerd() const;

    void setGereserveerd(int gereserveerd);

    const std::string &getName() const;

    void sethernieuwing(const int h);

    int gethernieuwing();

    void settemperatuur(const int t);

    int gettemperatuur() const;

    void setName(const std::string &name);

    /**Vraagt de grote van eenlevering op
     * @return de grote van een levering
     * @pre this->correctlyInitialized()
     * */
    int getLevering() const;

    /**Veranderd het aantal vaccins dat geleverd wordt op leveringsdag
     * @param int: het aantal vaccins dat aan de
     * @pre levering >= 0
     * @pre this->correctlyInitialized()
     * @post this->levering == levering1
    * */
    void setLevering(int levering);

    /**geeft het aantal vaccins per transport
     * @returns het aantal vaccins dat in een transport past
     * @pre this->correctlyinitialized()
     * */
    int getTransport() const;

    /**zet het aantal vaccins dat per transport past op de param transport1
     * @param transport1 het aantal vaccins dat in het transport past
     * @pre transport1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setTransport(int transport);

    /**Geeft het aantal dagen tussen twee leveringen
     * @returns het interval
     * @pre this->correctlyinitialized()
     * */
    int getInterval() const;

    /**zet het aantal dagen tussen twee leveringen
     * @param het interval tussen twee leveringen
     * @pre interval1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setInterval(int interval);

    /**Zet het aantal vaccins in de hub op aantal_vaccins1
     * @param aantal_vaccins1 het nieuwe aantal vaccins in de hub
     * @pre aantal_vaccins1 >= 0
     * @pre this->correctlyinitialized()
     * */
    void setAantalVaccins(const int aantal_vaccins1);

    //todo contract + ensure geres
    VaccinType();

    /**Geeft het aantal vaccins van dit type in de hub terug
     *@returns aantal vaccins van dit type in de hub
     * @pre this->correctlyInitialized
     * */
    int getAantalVaccins() const;

    /**trekt vaccins van aantal vaccins van dit type in de hub
     * @param vaccins: het aantal vaccins dat afgetrokken moet worden
     * @pre vaccins >=0
     * @pre this->correctlyInitialized()
     * @post aantal_vaccins -= vaccins
     * @post aantal_vaccins >= 0
     * */
    void substractVaccins(const int vaccins);

    /**Checkt of het object Vaccintype juist is geinitialiseerd
     *
     * @return: True als het object juist is geinitialiseerd en False als niet
     */
    bool correctlyInitialized() const;

    /**er wordt een lading vaccins van type aan de hub geleverd
    * @pre this->correctlyInitialized()
    * @post aantal_vaccins == aantal_vaccins_start + levering
    * */
    void leveringVanTypeToHub();

    /**Kijkt na of het object Vaccintype compleet geinitialiseerd is
    * @return true als compleet geinitaliseerd
    * @pre this->correctlyInitialized()
    * */
    bool completelyInitialized();

    /**Deze functie kijkt of de gegeven dag een leveringsdag is
     *
     * @param dag: De meegegeven dag waarop wordt getest of het de leveringsdag is
     * @return: True als dag een leveringsdag is en False als niet
     */
    bool isLeveringsDag(const int dag) const;

    int nextLeveringsDag(const int dag) const;
};


#endif //PROJECT_VACCINTYPE_H
