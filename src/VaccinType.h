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
    VaccinType* init_check;
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    int getLevering() const;

    void setLevering(int levering);

    int getTransport() const;

    void setTransport(int transport);

    int getInterval() const;

    void setInterval(int interval);

    //TODO correctlyinitialized
    //TODO completlyinitialized
    //TODO isLeveringsDag

    VaccinType();

    /**Geeft het aantal vaccins in de hub terug
     *@returns aantal vaccins in de hub
     * @pre this->correctlyInitialized
     * */
    int getAantalVaccins() const;

    /**trekt vaccins van aantal vaccins in de hub
     * @param vaccins: het aantal vaccins dat afgetrokken moet worden
     * @pre vaccins >=0
     * @pre this->correctlyInitialized()
     * @post aantal_vaccins -= vaccins
     * @post aantal_vaccins >= 0
     * */
    void substractVaccins(const int vaccins);

    bool correctlyInitialized() const;

    /**er wordt een lading aan de hub geleverd
    * @pre this->correctlyInitialized()
    * @post aantal_vaccins == aantal_vaccins_start + levering
    * */
    void leveringVanType();
};


#endif //PROJECT_VACCINTYPE_H
