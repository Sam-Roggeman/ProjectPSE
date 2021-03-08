//
// Created by said2 on 1-3-2021.
//

#include "Hub.h"

bool Hub::correctlyInitialized() {
//    for (unsigned int i = 0; i < getVaccinatiecentra().size();i++){
//        if (!this->getVaccinatiecentra()[i]->correctlyInitialized()){
//            return false;
//        }
//    }
    if (this->getInterval() < 0 || this->getLevering() < 0 || this->getTransport() <0){
        std::cerr << "levering, interval of transport < 0";
        return false;
    }
    return true;
}
