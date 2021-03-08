//
// Created by User on 1/03/2021.
//

#include "Vaccinatiecentrum.h"


bool Vaccinatiecentrum::correctlyInitialized() const {
    if (this->getCapaciteit()<0){
        std::cerr << "capaciteit 0\n";
        return false;
    }
    else if (this->getAdresCentrum().size()<=0){
        std::cerr << "leeg adres \n";
        return false;
    }
    else if (this->getAantalInwoners()<0) {
        std::cerr << "aantal inwoners 0\n";
        return false;
    }
    else if (this->getNaamCentrum().size() <= 0){
        std::cerr << "lege naam \n";
        return false;
    }
    return true;
}
