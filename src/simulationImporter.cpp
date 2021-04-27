//
// Created by User on 31/03/2021.
//

#include "simulationImporter.h"
int simulationImporter::importSimulation(const char *filename, std::ostream &errstream, Simulation& sim) {
    sim.clear();
    int hubcounter = 0;
    int vaccinatiecentracounter = 0;
    int vaccincounter = 0;
    Vaccinatiecentrum* centrum;
    TiXmlDocument doc;
    VaccinType* bedrijf;
    //open xml file indien: ASCII bestand met daarop een beschrijving van de vaccinatiecentra

    if (!doc.LoadFile(filename)) {
        errstream << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement *root = doc.FirstChildElement();
    //als er geen root element is
    REQUIRE(root != NULL, "Failed to load file: No root element.");
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
                    errstream << "element niet herkend" << std::endl;
                }
            }
            sim.getHub()->addcentrum(centrum);
        } else if (elem_name == "HUB") {
            hubcounter += 1;
            //loop over alle kinderelementen
            for (TiXmlElement *hub_elem = cdElement->FirstChildElement(); hub_elem != NULL; hub_elem = hub_elem->NextSiblingElement()) {
                elem_name = hub_elem->Value();
                //herken het element
                if(elem_name == "VACCIN"){
                    bedrijf = new VaccinType();
                    vaccincounter += 1;
                    for (TiXmlElement *vac_elem = hub_elem->FirstChildElement(); vac_elem != NULL; vac_elem = vac_elem->NextSiblingElement()) {
                        std::string vac_name = vac_elem->Value();
                        if (vac_name == "levering") {
                            bedrijf->setLevering(atoi(vac_elem->FirstChild()->Value()));
                        } else if (vac_name == "interval") {
                            bedrijf->setInterval(atoi(vac_elem->FirstChild()->Value()));
                        } else if (vac_name == "transport") {
                            bedrijf->setTransport(std::atoi(vac_elem->FirstChild()->Value()));
                        }else if(vac_name == "type"){
                            bedrijf->setName(vac_elem->FirstChild()->Value());
                        }else if(vac_name == "hernieuwing"){
                            bedrijf->sethernieuwing(std::atoi(vac_elem->FirstChild()->Value()));
                        }else if(vac_name == "temperatuur"){
                            bedrijf->settemperatuur(std::atoi(vac_elem->FirstChild()->Value()));
                        }else{
                            errstream << "element" << vac_name << "niet herkend" << std::endl;
                        }
                    }
                    sim.getHub()->addType(bedrijf);
                }else if (elem_name == "CENTRA"){
                    continue;
                }
                    //element is niet herkent
                else {
                    errstream << "element niet herkend" << std::endl;
                }
            }
        }
            //element is geen hub of centrum
        else {
            errstream << "element niet herkend" << std::endl;
        }
    }
    sim.getHub()->setCentrumTypes();
    ENSURE(sim.getHub()->completelyInitialized(), "De hub en alle vaccinatiecentra moeten juist gesimuleerd zijn");
    ENSURE((hubcounter < 2),"Je mag maar 1 hub hebben");
    ENSURE((vaccinatiecentracounter > 0),"Je moet minstens 1 vaccinatiecentrum hebben");
    ENSURE(hubcounter > 0,"Je moet minstens 1 Hub hebben");
    ENSURE(vaccincounter > 0, "Je moet minstens 1 vaccintype hebben");
    doc.Clear();
    return 0;
}
