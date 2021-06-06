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
     * @return this->getAantalVaccins-getGereserveerd()
     * @pre correctlyinitialized
     */
    int aantalNietGer();

    /**
     * vraagt het aantal gereserveerde vaccins op
     * @return gereserveerd aantal vaccins
     * @pre correctlyinitialized
     */
    int getGereserveerd() const;

    /**
     * veranderd het aantal gereserveerde vaccins naar gereserveerd
     * @param gereserveerd aantal dat gereserveerd is voor hernieuwing
     * @pre correctlyinitialized
     * @pre gereserveerd >= 0
     * @post gereserveerd == this->getGereserveerd()
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
     * @post this->getHernieuwing() == h
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
     * @post this->getTemperatuur() == t
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
     * @param name1 de nieuwe naam van het type
     * @pre correctlyinitialized
     * @pre getName().size() > 0
     * @post getName() == name1
     */
    void setName(const std::string &name1);

    /**Vraagt de grote van een levering op
     * @return de grote van een levering
     * @pre this->correctlyInitialized()
     * */
    int getLevering() const;

    /**Veranderd het aantal vaccins dat geleverd wordt op leveringsdag
     * @param int: het aantal vaccins dat aan de
     * @pre getLevering() >= 0
     * @pre this->correctlyInitialized()
     * @post this->getLevering() == levering1
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
     * @post this->getTransport() == transport1
     * */
    void setTransport(int transport1);

    /**Geeft het aantal dagen tussen twee leveringen
     * @returns het interval
     * @pre this->correctlyinitialized()
     * */
    int getInterval() const;

    /**zet het aantal dagen tussen twee leveringen
     * @param het interval tussen twee leveringen
     * @pre interval1 >= 0
     * @pre this->correctlyinitialized()
     * @post this->getInterval == interval1
     * */
    void setInterval(int interval);

    /**Zet het aantal vaccins in de hub op aantal_vaccins1
     * @param aantal_vaccins1 het nieuwe aantal vaccins in de hub
     * @pre aantal_vaccins1 >= 0
     * @pre this->correctlyinitialized()
     * @post this->getAantalVaccins() == aantal_vaccins1
     * */
    void setAantalVaccins(const int aantal_vaccins1);

    /**
     * initializeerd een vaccintype
     * @post getLevering() == getTransport() == getInterval() == getAantalVaccins() == getHernieuwing() == getGereserveerd() == 0
     * @post getTemperatuur() == 27
     * @post getName() == ""
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
     * @post getAantalVaccins() -= vaccins
     * @post getAantalVaccins() >= 0
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
    * @post getAantalVaccins() == getAantalVaccins()_start + levering
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
     * @return (getInterval()+1)-(dag % (getInterval()+1)) oftewel het aantal dagen tot de volgende levering
     */
    int nextLeveringsDag(const int dag) const;

    /**add gereserveerd aantal vaccins van dit type in de hub
     * @param aantal: het aantal vaccins dat gereserveerd moet worden
     * @pre aantal >= 0
     * @pre this->correctlyInitialized()
     * @post getGereserveerd() += aantal
     * */
    void addGereserveerd(int aantal);

    /**trekt aantal af van aantal gereserveerde vaccins van dit type in de hub
     * @param aantal: het aantal gereserveerde vaccins dat afgetrokken moet worden
     * @pre aantal >=0
     * @pre this->correctlyInitialized()
     * @post getGereserveerd() -= vaccins
     * @post getGereserveerd() >= 0
     * */
    void subGereserveerd(int aantal);

    /**
     * copy constructor voor vaccintype
     * @pre v2.correctlyInitialized()
     * @param v2 vaccinType to-copy
     * @post getLevering()== v2.getLevering()
     * @post getAantalVaccins()== v2.getAantalVaccins()
     * @post getTransport()== v2.getTransport()
     * @post getInterval()== v2.getInterval()
     * @post getGereserveerd()== v2.getGereserveerd()
     * @post gettemperatuur()== v2.gettemperatuur()
     * @post getName()== v2.getName()
     * @post correctlyInitialized()
     */
    VaccinType(const VaccinType& v2);
};


#endif //PROJECT_VACCINTYPE_H
