//============================================================================
// Name        : Simulation.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================
#include "Simulation.h"

Simulation::Simulation(Hub *hub1) {
    REQUIRE(hub1->correctlyInitialized(),"hub niet geinitializeerd bij aanroep simulatie constructor");
    hub = hub1;
    _initcheck = this;
    dag =0;
    ENSURE(this->getHub() != NULL, "Geen hub toegevoegd");
    ENSURE(this->getHub()->correctlyInitialized(), "hub niet geinitializeerd bij einde simulatie constructor");
    ENSURE(this->correctlyInitialized(), "simulatie niet geinitializeerd bij einde simulatie constructor");
}


Hub * Simulation::getHub() const {
    REQUIRE(correctlyInitialized(),"simulatie niet geinitializeerd bij aanroep getHub");
    REQUIRE(hub->correctlyInitialized(),"hub niet geinitializeerd bij aanroep getHub");
    return hub;
}

bool Simulation::correctlyInitialized() const {
    return this == _initcheck;
}

void Simulation::setHub(Hub *h) {
    REQUIRE(h->correctlyInitialized(),"meegegeven hub niet geinitializeerd bij aanroep setHub");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep setHub");
    Simulation::hub = h;
}



void Simulation::outputSimulation(std::ostream &out) {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep outputSimulation");
    REQUIRE(getHub()->correctlyInitialized(),"meegegeven hub niet geinitializeerd bij aanroep outputSimulation");
    hub->outputHub(out);
}

void Simulation::outputSimulation() {
    outputSimulation(std::cout);
}

void Simulation::autoSimulation(int start, int eind) {
    REQUIRE(getHub()->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autosimulation");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    autoSimulation(start, eind, std::cout);
}

void Simulation::autoSimulation(int start, int eind, std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(start>=0, "startdag <0");
    REQUIRE(eind >start, "einddag <=startdag");
    REQUIRE(getHub()->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autosimulation");
    REQUIRE(getHub()->completelyInitialized(), "hub niet compleet geinitializeerd bij aanroep autoSimulation");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    dag = start;
//    1.  WHILE huidige dag<eind dag
    std::ostringstream oss;
    while (dag < eind) {
        out << "DAG " << dag << ":" << std::endl;
//    1.1 IF er vaccins geleverd worden op de huidige dag
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
        hub->vacLeveringen(dag);
        hub->outputHub(out);
        oss.str("");
        oss.clear();
        oss << "dag" << dag;
//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra2(dag,std::cout);
        this->graphicIntegration("./src/engine","./graphics1",oss.str());
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(dag,out);
        nextDay();
        out << std::endl;
    }
    ENSURE(getDag() == eind, "de autosimulation eindigde niet op de einddag");
}

void Simulation::autoSimulationUntilDone() {
    autoSimulationUntilDone(std::cout);
}


void Simulation::autoSimulationUntilDone(std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(getHub()->correctlyInitialized(), "hub niet geinitializeerd bij aanroep autoSimulationUntilDone");
    REQUIRE(getHub()->completelyInitialized(), "hub niet compleet geinitializeerd bij aanroep autoSimulationUntilDone");
    REQUIRE(this->correctlyInitialized(), "centrum niet geinitializeerd bij aanroep autoSimulationUntilDone");
//    1.  WHILE not done
    std::ostringstream oss;
    while (hub->notDone()){
        out << "DAG " << dag << ":" << std::endl;
//    1.1 IF er vaccins geleverd worden op de huidige dag
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
        hub->vacLeveringen(dag);
        hub->outputHub(out);
//        this->impressie(std::cout);
        oss.str("");
        oss.clear();
        oss << "dag" << dag;

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit
        hub->transportToCentra2(dag,out);
//        this->graphicIntegration("./src/engine","./graphics",oss.str());

//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
        hub->vaccineren(dag,out);
        out << std::endl;
        nextDay();

    }
    hub->outputHub(out);
    ENSURE(this->getHub()->aantalOngevaccineerden() == 0,"Aantal ongevaccineerden was niet 0 bij afloop van autoSimulationUntillDone");
}

void Simulation::addcentrum(Vaccinatiecentrum *v) {
    REQUIRE(v->correctlyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(v->completelyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep addcentrum");
    hub->addcentrum(v);
}

void Simulation::nextDay(){
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep nextDay");
    int startdag = dag;
    dag += 1;
    ENSURE(getDag() == startdag+1, "dag was niet verghoogt met 1 na oproep van nextDay()");
}

int Simulation::getDag() const {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep getDag");
    ENSURE(dag >= 0, "De dag mag niet negatief zijn");
    return dag;
}

void Simulation::setDag(int d) {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep setDag");
    REQUIRE(d > 0, "De dag mag niet negatief zijn");
    Simulation::dag = d;
}

void Simulation::clear() {
    hub->clear();
}

void Simulation::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van impressie");
    this->getHub()->impressie(out);
}

void Simulation::graphicIntegration(std::string path_to_engine, std::string path_to_safe_dir, std::string name) {
    //veranderbare variabelen
    //ZBufferedWireframe of ZBuffering
    std::string soort = "ZBufferedWireframe";
    int aantal_vr_rij = 12;
    int y_offs;
    int y_afstand_tussen_vr = 1;
    double vr_Scale = 0.5;
    int x_afstand_vr = 3;
    //

    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van graphicIntegration");
    std::ofstream o;
    o.open((path_to_safe_dir+"/"+name+".ini").c_str());
    o.precision(10);
    o << "[General]" << std::endl << "size = 1024" << std::endl << "backgroundcolor = ("
      << ((double) 135/(double) 255) << "," << ((double) 206/(double) 255) <<"," << ((double) 235/(double) 255) << ")"
      << std::endl<< "type = ZBufferedWireframe" << std::endl << "eye = (-200,0,200)" << std::endl;
    std::map<Vaccinatiecentrum*, int> ladingmap = hub->getAantalLadingenVorigeDag();
    int nr_fig = 1;
    int totaal_inw = 0;
    for (std::map<Vaccinatiecentrum*, int>::const_iterator it = ladingmap.begin(); it != ladingmap.end(); it++){
        nr_fig += it->second+1;
        totaal_inw += it->first->getAantalInwoners();
    }
    o << "nrFigures =" << nr_fig<<std::endl;
    int current = 0;
    //hub
    o << "[Figure0]" <<std::endl << "type = Cylinder" << std::endl << "scale = 2" <<std::endl << "rotateX = 0"
      <<std::endl << "rotateY = 0" <<std::endl << "rotateZ = 0" <<std::endl << "center = (0,25,0)" << std::endl
      <<"color = (1,1,0)" <<std::endl <<"n = 20"<< std::endl<< "height = 5" <<std::endl;
    current++;
    double inw_verhouding;
    Vaccinatiecentrum* centrum;
    int y;
    int x;
    double gevac_ver;
    double r;
    double g;
    int centrum_nr = 0;

    for (std::map<Vaccinatiecentrum*, int>::const_iterator it = ladingmap.begin(); it != ladingmap.end(); it++){
        centrum = it->first;
        inw_verhouding = (double) centrum->getAantalInwoners()/(double) totaal_inw;
        y = (centrum_nr+1)/2*20;
        if ((centrum_nr%2) == 0){
            y = -y;
        }
        gevac_ver = (double) centrum->getAantalVolGevaccineerden()/ (double) centrum->getAantalInwoners();
        r = 1-gevac_ver;
        g = gevac_ver;
        //centra
        o << "[Figure"<<current <<"]" <<std::endl << "type = Cube" << std::endl << "scale =" << inw_verhouding*3
          << std::endl << "rotateX = 0"<<std::endl << "rotateY = 0" <<std::endl << "rotateZ = 0" <<std::endl
          << "center = (" << y << ",-30,0)" << std::endl <<
          "color = (" << r << "," << g << ",0)" <<std::endl;
        current++;
        y_offs= 0;
        //vrachtwagens
        for (int i = 0; i < it->second; i++ ){
            if (i%aantal_vr_rij == 0&& i%(2*aantal_vr_rij) != 0 && i != 0){
                y_offs = abs(y_offs) + y_afstand_tussen_vr;
            }
            if (i%(2*aantal_vr_rij) == 0&& i !=0){
                y_offs = -y_offs;
            }
            x = (i%aantal_vr_rij)*x_afstand_vr-20;
            o << "[Figure" << current << "]" << std::endl << "type = Vrachtwagen" << std::endl << "scale =" << vr_Scale
              << std::endl << "rotateX = 0" << std::endl << "rotateY = 0" << std::endl << "rotateZ = 0" << std::endl
              << "center = (" << y_offs+y << "," << x << ",0)" << std::endl
              << "color = (" << (((double) (rand()%256))/(double) 255) << "," << (((double) (rand()%256))/(double) 255) << ","
              << (((double) (rand()%256))/(double) 255) << ")" <<std::endl;
            current++;
        }
        centrum_nr++;
    }
    o.close();
    system((path_to_engine + " " + path_to_safe_dir+"/"+name+".ini").c_str());
}

void Simulation::addHub(Hub *hub1) {
    this->getHubs().push_back(hub1);
}

std::vector<Hub *> Simulation::getHubs() {
    return hubs;
}

Simulation::Simulation() {
    dag = 0;
    _initcheck = this;
}

