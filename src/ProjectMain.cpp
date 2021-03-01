//============================================================================
// Name        : TicTacToeMain.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tinyxml.h"
#include "Vaccinatiecentrum.h"
#include "Hub.h"
#include <sstream>
#include "DesignByContract.h"

using namespace std;

int main(int argc, char **argv) {
    Hub hub = Hub();
    Vaccinatiecentrum *centrum = NULL;
    TiXmlDocument doc;
    //open xml file indien: ASCII bestand met daarop een beschrijving van de vaccinatiecentra
    if (!doc.LoadFile("test.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }
    for (TiXmlElement *cdElement = root->FirstChildElement();
         cdElement != NULL; cdElement = cdElement->NextSiblingElement()) {
        std::string elem_name = cdElement->Value();
        if (elem_name == "VACCINATIECENTRUM") {
            for (TiXmlElement *vac_elem = cdElement->FirstChildElement();
                 vac_elem != NULL; vac_elem = vac_elem->NextSiblingElement()) {
                elem_name = vac_elem->Value();
                *centrum = Vaccinatiecentrum();
                if (elem_name == "naam") {
                    centrum->setNaamCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "adres") {
                    centrum->setAdresCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "inwoners") {
                    centrum->setAantalInwoners(std::atoi(vac_elem->FirstChild()->Value()));
                } else if (elem_name == "capaciteit") {
                    centrum->setCapaciteit(std::atoi(vac_elem->FirstChild()->Value()));
                }
                else {
                    std::cerr << "element niet herkend" << std::endl;
                }
            }
            hub.addcentra(centrum);
        } else if (elem_name == "HUB") {
            for (TiXmlElement *hub_elem = cdElement->FirstChildElement();
                 hub_elem != NULL; hub_elem = hub_elem->NextSiblingElement()) {
                if (elem_name == "levering") {
                    hub.setLevering(atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "interval") {
                    hub.setInterval(atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "transport") {
                    hub.setTransport(std::atoi(hub_elem->FirstChild()->Value()));
                }
                else {
                    std::cerr << "element niet herkend" << std::endl;
                }
            }
        }
        else {
            std::cerr << "element niet herkend" << std::endl;
        }
    }
}