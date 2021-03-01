//
// Created by User on 1/03/2021.
//

#ifndef PROJECT_VACCINATIECENTRUM_H
#define PROJECT_VACCINATIECENTRUM_H


#include <string>

class Vaccinatiecentrum {
    std::string naam_centrum;
    std::string adres_centrum;
    int aantal_inwoners;
    int capaciteit;
public:

    Vaccinatiecentrum(){};

    Vaccinatiecentrum(std::string naam, std::string adres, int inwoners, int capaciteit):
            naam_centrum(naam), adres_centrum(adres), aantal_inwoners(inwoners), capaciteit(capaciteit){};

    const std::string &getNaamCentrum() const {
        return naam_centrum;
    }

    void setNaamCentrum(const std::string &naamCentrum) {
        naam_centrum = naamCentrum;
    }

    const std::string &getAdresCentrum() const {
        return adres_centrum;
    }

    void setAdresCentrum(const std::string &adresCentrum) {
        adres_centrum = adresCentrum;
    }

    int getAantalInwoners() const {
        return aantal_inwoners;
    }

    void setAantalInwoners(int aantalInwoners) {
        aantal_inwoners = aantalInwoners;
    }

    int getCapaciteit() const {
        return capaciteit;
    }

    void setCapaciteit(int capaciteit1) {
        Vaccinatiecentrum::capaciteit = capaciteit1;
    }
};


#endif //PROJECT_VACCINATIECENTRUM_H
