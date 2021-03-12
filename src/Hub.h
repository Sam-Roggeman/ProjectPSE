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
    int aantal_vaccins;
    int levering;
    int interval;
    int transport;
    std::map<std::string,Vaccinatiecentrum*> vaccinatiecentra;
public:
    Hub(){}

    int getAantalVaccins() const {
        return aantal_vaccins;
    }

    void setAantalVaccins(int levering1) {
        Hub::aantal_vaccins = levering1;
    }

    int getInterval() const {
        return interval;
    }

    void setInterval(int interval1) {
        Hub::interval = interval1;
    }

    int getTransport() const {
        return transport;
    }

    void setTransport(int transport1) {
        Hub::transport = transport1;
    }
    
    const std::map<std::string, Vaccinatiecentrum *> &getVaccinatiecentra() const;

    void setVaccinatiecentra(const std::vector<Vaccinatiecentrum*> &vaccinatiecentra1) {
        for (unsigned int i = 0; i<vaccinatiecentra1.size();i++ ){
            Vaccinatiecentrum* centrum = vaccinatiecentra1[i];
            vaccinatiecentra[centrum->getNaamCentrum()] = centrum;
        }
    }

    void addcentrum(Vaccinatiecentrum* vaccinatiecentrum){
        vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;
    }

    void substractVaccins(int vaccins);

    bool correctlyInitialized() const;

    void outputHub(std::ostream &out) const;

    void transportToCentra();

    void transportToCentra(std::ostream &out);

    void leveringToHub();

    bool isLeveringsDag(int dag);

    void vaccineren(std::ostream out);

    void vaccineren();
};


#endif //PROJECT_HUB_H
