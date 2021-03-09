//
// Created by said2 on 1-3-2021.
//

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H
#include "Vaccinatiecentrum.h"
#include "vector"
#include <map>


class Hub {
    int levering;
    int interval;
    int transport;
    std::map<std::string,Vaccinatiecentrum*> vaccinatiecentra;
public:
    Hub(){}

    int getLevering() const {
        return levering;
    }

    void setLevering(int levering1) {
        Hub::levering = levering1;
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

    void addcentra(Vaccinatiecentrum* vaccinatiecentrum){
        vaccinatiecentra[vaccinatiecentrum->getNaamCentrum()] = vaccinatiecentrum;
    }

    bool correctlyInitialized() const;

    void outputHub(std::ostream &out) const;
};


#endif //PROJECT_HUB_H
