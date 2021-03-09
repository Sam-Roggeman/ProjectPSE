//
// Created by said2 on 1-3-2021.
//

#include "Hub.h"

bool Hub::correctlyInitialized() const {
//    for (std::map<std::string, Vaccinatiecentrum*>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end() ;it++){
//        if (! it->second->correctlyInitialized()){
//            return false;
//        }
//    }
    if (this->getInterval() < 0 || this->getLevering() < 0 || this->getTransport() <0){
        std::cerr << "levering, interval of transport < 0";
        return false;
    }
    return true;
}

const std::map<std::string, Vaccinatiecentrum *> &Hub::getVaccinatiecentra() const {
    return vaccinatiecentra;
}

