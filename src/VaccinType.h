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
    VaccinType* _init_check;
public:

    /**
     * berekend het aantal niet gereserveerde vaccins in de hub
     * @return aantal vaccins-gereserveerd
     * @pre correctlyinitialized
     */
    int aantalNietGer();

    /**
     * vraagt het aantal gereserveerde vaccins op
     * @return gereserveerd
     * @pre correctlyinitialized
     */
    int getGereserveerd() const;

    /**
     * zet this->gereserveerd op int gereserveerd
     * @param gereserveerd aantal dat gereserveerd is voor hernieuwing
     * @pre correctlyinitialized
     * @pre gereserveerd >= 0
     * @post gereserveerd == this->gereserveerd
     */
    void setGereserveerd(int gereserveerd);

    /**
     * vraagt de naam van het type op
     * @return naam van het type
     * @pre correctlyinitialized
     */
    const std::string &getName() const;

    /**
     * zet het vernieuwingsinterval op h
     * @param h de nieuwe hernieuwing
     * @pre correctlyinitialized
     * @post this->hernieuwing == h
     */
    void sethernieuwing(const int h);

    /**
     * geeft het hernieuwingsinterval van het type terug
     * @pre correctlyinitialized
     * @return het hernieuwingsinterval
     */
    int gethernieuwing();

    /**
     * zet de bewaringtemperatuur op t
     * @param t de nieuwe bewaringstemperatuur
     * @pre correctlyinitialized
     * @post this->temperatuur == t
     */
    void settemperatuur(const int t);

    /**
     * geeft het hernieuwingsinterval van het type terug
     * @pre correctlyinitialized
     * @return het hernieuwingsinterval
     */
    int gettemperatuur() const;

    /**
     * veranderd de naam van het type naar name
     * @param name de nieuwe naam van het type
     * @pre correctlyinitialized
     * @pre name.size() > 0
     * @post name == name1
     */
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

    /**
     * initializeerd een vaccintype
     * @post levering == transport == interval == aantal_vaccins == hernieuwing == gereserveerd == 0
     * @post temperatuur == 27
     * @post name == ""
     * @post correctlyInitialized
     */
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

    /**
     * Checkt of het object Vaccintype juist is geinitialiseerd
     * @return: True als het object juist is geinitialiseerd en False als niet
     */
    bool correctlyInitialized() const;

    /**
    * er wordt een lading vaccins van type aan de hub geleverd
    * @pre this->correctlyInitialized()
    * @post aantal_vaccins == aantal_vaccins_start + levering
    * */
    void leveringVanTypeToHub();

    /**
     * Kijkt na of het object Vaccintype compleet geinitialiseerd is
    * @return true als compleet geinitaliseerd
    * @pre this->correctlyInitialized()
    * */
    bool completelyInitialized();

    /**
     * Deze functie kijkt of de gegeven dag een leveringsdag is
     * @pre this->correctlyInitialized()
     * @pre dag >= 0
     * @param dag: De meegegeven dag waarop wordt getest of het de leveringsdag is
     * @return: True als dag een leveringsdag is en False als niet
     */
    bool isLeveringsDag(const int dag) const;

    /**
     * berekend het aantal dagen tot de volgende levering naar de hub
     * @pre this->correctlyInitialized()
     * @pre dag >= 0
     * @param dag de huidige dag
     * @return (interval+1)-(dag % (interval+1)) oftewel het aantal dagen tot de volgende levering
     */
    int nextLeveringsDag(const int dag) const;

    /**add gereserveerd aantal vaccins van dit type in de hub
     * @param aantal: het aantal vaccins dat gereserveerd moet worden
     * @pre aantal >= 0
     * @pre this->correctlyInitialized()
     * @post gereserveerd += aantal
     * */
    void addGereserveerd(int aantal);

    /**trekt aantal af van aantal gereserveerde vaccins van dit type in de hub
     * @param aantal: het aantal gereserveerde vaccins dat afgetrokken moet worden
     * @pre aantal >=0
     * @pre this->correctlyInitialized()
     * @post gereserveerd -= vaccins
     * @post gereserveerd >= 0
     * */
    void subGereserveerd(int aantal);
};


#endif //PROJECT_VACCINTYPE_H
