//
// Created by User on 1/03/2021.
//

#include "Project.h"

int initializeSimulation(const char *filename, Hub &hub){
    Vaccinatiecentrum* centrum;
    TiXmlDocument doc;
    //open xml file indien: ASCII bestand met daarop een beschrijving van de vaccinatiecentra
    if (!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    //als er geen root element is
    if (root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        return 1;
    }
    //loop over alle child elementen zolang het bestand niet is ingelezen
    for (TiXmlElement *cdElement = root->FirstChildElement();
         cdElement != NULL; cdElement = cdElement->NextSiblingElement()) {
        std::string elem_name = cdElement->Value();
        //vindt het soort element
        if (elem_name == "VACCINATIECENTRUM") {
            centrum = new Vaccinatiecentrum();
            //loop over alle kinderelementen
            for (TiXmlElement *vac_elem = cdElement->FirstChildElement();
                 vac_elem != NULL; vac_elem = vac_elem->NextSiblingElement()) {
                elem_name = vac_elem->Value();
                //herken het element
                if (elem_name == "naam") {
                    centrum->setNaamCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "adres") {
                    centrum->setAdresCentrum(vac_elem->FirstChild()->Value());
                } else if (elem_name == "inwoners") {
                    centrum->setAantalInwoners(std::atoi(vac_elem->FirstChild()->Value()));
                } else if (elem_name == "capaciteit") {
                    centrum->setCapaciteit(std::atoi(vac_elem->FirstChild()->Value()));
                } else {
                    std::cerr << "element niet herkend" << std::endl;
                }
            }
            hub.addcentra(centrum);
        } else if (elem_name == "HUB") {
            //loop over alle kinderelementen
            for (TiXmlElement *hub_elem = cdElement->FirstChildElement(); hub_elem != NULL; hub_elem = hub_elem->NextSiblingElement()) {
                elem_name = hub_elem->Value();
                //herken het element
                if (elem_name == "levering") {
                    hub.setLevering(atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "interval") {
                    hub.setInterval(atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "transport") {
                    hub.setTransport(std::atoi(hub_elem->FirstChild()->Value()));
                } else if (elem_name == "CENTRA"){
                    continue;
                }
                    //element is niet herkent
                else {
                    std::cerr << "element niet herkend" << std::endl;
                }
            }
        }
            //element is geen hub of centrum
        else {
            std::cerr << "element niet herkend" << std::endl;
        }
    }
    doc.Clear();
    return 0;
}

void outputSimulation(const Hub &hub, std::ostream &out) {
    hub.outputHub(out);
}

void outputSimulation(const Hub &hub) {
    outputSimulation(hub,std::cout);
}

