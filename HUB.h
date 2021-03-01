//
// Created by said2 on 1-3-2021.
//

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H


class Hub {
public:
    int levering;
    int interval;
    int transport;
    vector<Vaccinatiecentrum*> vaccinatiecentra;
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

    const vector<Vaccinatiecentrum *> &getVaccinatiecentra() const {
        return vaccinatiecentra;
    }

    void setVaccinatiecentra(const vector<Vaccinatiecentrum*> &vaccinatiecentra1) {
        Hub::vaccinatiecentra = vaccinatiecentra1;
    }
    void addcentra(Vaccinatiecentrum* vaccinatiecentrum){
        vaccinatiecentra.pushback(vaccinatiecentrum);
    }
};


#endif //PROJECT_HUB_H
