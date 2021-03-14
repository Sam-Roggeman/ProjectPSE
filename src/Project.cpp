//
// Created by User on 1/03/2021.
//

#include "Project.h"

int initializeSimulation(const char *filename, Hub &hub){
    int hubcounter = 0;
    int vaccinatiecentracounter = 0;
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
            vaccinatiecentracounter += 1;
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
            hub.addcentrum(centrum);
        } else if (elem_name == "HUB") {
            hubcounter += 1;
            //loop over alle kinderelementen
            for (TiXmlElement *hub_elem = cdElement->FirstChildElement(); hub_elem != NULL; hub_elem = hub_elem->NextSiblingElement()) {
                elem_name = hub_elem->Value();
                //herken het element
                if (elem_name == "levering") {
                    hub.setLevering(atoi(hub_elem->FirstChild()->Value()));
                    hub.leveringToHub();
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
    REQUIRE(hub.correctlyInitialized(),"De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    REQUIRE((hubcounter == 1),"Je mag maar 1 hub hebben");
    REQUIRE((vaccinatiecentracounter > 0),"Je moet minstens 1 vaccinatiecentrum hebben");
    doc.Clear();
    return 0;
}

void outputSimulation(const Hub &hub, std::ostream &out) {
    hub.outputHub();
}

void outputSimulation(const Hub &hub) {
    outputSimulation(hub,std::cout);
}

void autoSimulation(Hub& hub, int start, int eind){
    autoSimulation(hub, start, eind, std::cout);
}

void autoSimulation(Hub& hub, int start, int eind, std::ostream &out){
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(hub.correctlyInitialized(), "Foutieve hub");

//    1.  WHILE huidige dag<eind dag

    for (int current = start; current < eind; current++) {
        out << "DAG " << current << ":" << std::endl;
        hub.outputHub(out);
//    1.1 IF er vaccins geleverd worden op de huidige dag
        if (hub.isLeveringsDag(current)){
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
            hub.leveringToHub();
        }

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub.transportToCentra(out);
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub.vaccineren(out);
        out << std::endl;
    }
}
