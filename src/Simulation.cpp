//============================================================================
// Name        : Simulation.cpp
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccin distribution simulation in C++, Ansi-style
//============================================================================
#include "Simulation.h"

//Simulation::Simulation(Hub *hub1) {
//    REQUIRE(hub1->correctlyInitialized(),"hub niet geinitializeerd bij aanroep simulatie constructor");
//    hub = hub1;
//    _initcheck = this;
//    dag =0;
//    ENSURE(this->getHub() != NULL, "Geen hub toegevoegd");
//    ENSURE(this->getHub()->correctlyInitialized(), "hub niet geinitializeerd bij einde simulatie constructor");
//    ENSURE(this->correctlyInitialized(), "simulatie niet geinitializeerd bij einde simulatie constructor");
//}


//Hub * Simulation::getHub() const {
//    REQUIRE(correctlyInitialized(),"simulatie niet geinitializeerd bij aanroep getHub");
//    REQUIRE(hub->correctlyInitialized(),"hub niet geinitializeerd bij aanroep getHub");
//    return hub;
//}

bool Simulation::correctlyInitialized() const {
    for(unsigned int i = 0; i < hubs.size(); i++){
        if (!hubs[i]->correctlyInitialized()){
            return false;
        }
    }
    return this == _initcheck;
}

//void Simulation::setHub(Hub *h) {
//    REQUIRE(h->correctlyInitialized(),"meegegeven hub niet geinitializeerd bij aanroep setHub");
//    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep setHub");
//    Simulation::hub = h;
//}



void Simulation::outputSimulation(std::ostream &out) {
    REQUIRE(correctlyInitialized(), "simulatie niet correct geinitialiseerd bij aanroep outputSimulation");
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        (*it)->outputHub(out);
    }
}

void Simulation::outputSimulation() {
    outputSimulation(std::cout);
}

void Simulation::autoSimulation(int start, int eind) {
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    autoSimulation(start, eind, std::cout);
}

void Simulation::autoSimulation(int start, int eind, std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(start>=0, "startdag <0");
    REQUIRE(eind >start, "einddag <=startdag");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep autosimulation");
    Gegevens gegevens = Gegevens();
    dag = start;
//    1.  WHILE huidige dag<eind dag
    std::ostringstream oss;
    while (dag < eind) {
        simulateDay(out);
    }
    ENSURE(getDag() == eind, "de autosimulation eindigde niet op de einddag");
    this->outputGegevens(out);
}



void Simulation::autoSimulationUntilDone() {
    autoSimulationUntilDone(std::cout);
}


void Simulation::autoSimulationUntilDone(std::ostream &out) {
// Het systeem bevat een simulatie met de verschillende vaccinatiecentra
    REQUIRE(this->correctlyInitialized(), "centrum niet geinitializeerd bij aanroep autoSimulationUntilDone");
//    1.  WHILE not done
    std::ostringstream oss;
    while (notDone()) {
        simulateDay(out);
    }
    for (std::vector<Hub *>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        (*it)->outputHub(out);
        ENSURE((*it)->aantalOngevaccineerden() == 0,
               "Aantal ongevaccineerden was niet 0 bij afloop van autoSimulationUntilDone");
    }
    this->outputGegevens(out);
}

void Simulation::addcentrum(Vaccinatiecentrum *v, Hub * h) {
    REQUIRE(v->correctlyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(v->completelyInitialized(),"De vaccinatiecentrum moet correct geinitialiseerd zijn");
    REQUIRE(correctlyInitialized(), "simulatie niet geinitializeerd bij aanroep addcentrum");
    h->addcentrum(v);
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
    initializeTmp();
    dag = 0;
    for (std::vector<Hub *>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        delete *it;
    }
    hubs.clear();
    for (std::vector<Vaccinatiecentrum *>::const_iterator it = vaccinatiecentra.begin(); it != vaccinatiecentra.end(); it++) {
        delete *it;
    }
    vaccinatiecentra.clear();
    for (std::map<int, Gegevens *>::const_iterator it = statistische_gegevens.begin(); it != statistische_gegevens.end(); it++) {
        delete it->second;
    }
    statistische_gegevens.clear();
    statistische_gegevens[-1] = new Gegevens();
}

void Simulation::impressie(std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van impressie");
    out << "DAG " <<dag << " :" <<std::endl;
    for (std::vector<Hub *>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        (*it)->impressie(out);
    }
}

void Simulation::graphicIntegration(std::string path_to_engine, std::string path_to_safe_dir, std::string name) {
    //veranderbare variabelen
    //ZBufferedWireframe/ZBuffering/LightedZBuffering
    std::string soort = "LightedZBuffering";
    int aantal_vr_rij = 12;
    int y_offs;
    int y_afstand_tussen_vr = 1;
    double vr_Scale = 0.5;
    int x_afstand_vr = 3;
    //
    std::vector<double> random_color;
    double inw_verhouding;
    Vaccinatiecentrum *centrum;
    int y;
    int x;
    double gevac_ver;
    double r;
    double g;
    int centrum_nr;
    int current = 0;
    centrum_nr = 0;
    int nr_fig = 0;
    std::map<Vaccinatiecentrum* , int> centrum_to_nummer;
    int totaal_inw = 0;

    REQUIRE(DirectoryExists(path_to_safe_dir), "Directory ./tmp bestaat niet");
    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van graphicIntegration");
    std::ofstream o;
    o.open((path_to_safe_dir+"/"+name+".ini").c_str());
    o.precision(10);

    o << "[General]" << std::endl << "size = 1024" << std::endl << "backgroundcolor = ("
      << ((double) 255/(double) 255) << "," << ((double) 255/(double) 255) <<"," << ((double) 255/(double) 255) << ")"
      << std::endl<< "type = \""<<soort << "\""<< std::endl << "eye = (-200,0,200)" << std::endl << "nrLights = 1"  << std::endl;

    for (unsigned int hub_id = 0 ; hub_id < getHubs().size(); hub_id++) {
        std::map<Vaccinatiecentrum *, int> ladingmap = hubs[hub_id]->getAantalLadingenVorigeDag();
        nr_fig++;
        for (std::map<Vaccinatiecentrum *, int>::const_iterator it = ladingmap.begin(); it != ladingmap.end(); it++) {
            nr_fig += it->second + 1;
            totaal_inw += it->first->getAantalInwoners();
            centrum_to_nummer[it->first] = centrum_nr;
            centrum_nr++;
        }
    }
    o << "nrFigures =" << nr_fig << std::endl <<"\n[Light0]\n infinity = TRUE\n direction = (-1, -1, -1)" <<
      "\n ambientLight = (1, 1, 1)\n diffuseLight = (1, 1, 1)"<<"\n";
    for (unsigned int hub_id = 0 ; hub_id < getHubs().size(); hub_id++) {
        std::map<Vaccinatiecentrum *, int> ladingmap = hubs[hub_id]->getAantalLadingenVorigeDag();

        random_color.clear();
        for (int i =0; i<3; i++){
            random_color.emplace_back( ((double)( rand()% 206))/(double) 256);
        }


        y = (hub_id + 1) / 2 * 20;
        if ((hub_id % 2) == 0) {
            y = -y;
        }

        //hub
        o << "[Figure"<<current<<"]" << std::endl << "type = Cylinder" << std::endl << "scale = 2" << std::endl << "rotateX = 0"
      << std::endl << "rotateY = 0" << std::endl << "rotateZ = 0" << std::endl << "center = ("<<y<<",25,0)" << std::endl
      << "ambientReflection = ("<<random_color[0]<<","<<random_color[1]<<","<<random_color[2]<<")" << std::endl
      << "diffuseReflection = ("<<random_color[0]<<","<<random_color[1]<<","<<random_color[2]<<")" << std::endl <<
       "n = 20" << std::endl << "height = 5" << std::endl;
        current++;


        for (std::map<Vaccinatiecentrum *, int>::const_iterator it = ladingmap.begin(); it != ladingmap.end(); it++) {
            centrum = it->first;
            centrum_nr = centrum_to_nummer[centrum];
            inw_verhouding = (double) centrum->getAantalInwoners() / (double) totaal_inw;
            y = (centrum_nr + 1) / 2 * 20;
            if ((centrum_nr % 2) == 0) {
                y = -y;
            }
            gevac_ver = (double) centrum->getAantalVolGevaccineerden() / (double) centrum->getAantalInwoners();
            r = 1 - gevac_ver;
            g = gevac_ver;
            //centra
            o << "[Figure" << current << "]" << std::endl << "type = Cube" << std::endl << "scale ="
              << inw_verhouding * 3
              << std::endl << "rotateX = 0" << std::endl << "rotateY = 0" << std::endl << "rotateZ = 0" << std::endl
              << "center = (" << y << ",-30,0)" << std::endl <<
              "color = (" << r << "," << g << ",0)" << std::endl;
            current++;
            y_offs = 0;
            //vrachtwagens
            for (int i = 0; i < it->second; i++) {
                if (i % aantal_vr_rij == 0 && i % (2 * aantal_vr_rij) != 0 && i != 0) {
                    y_offs = abs(y_offs) + y_afstand_tussen_vr;
                }
                if (i % (2 * aantal_vr_rij) == 0 && i != 0) {
                    y_offs = -y_offs;
                }
                x = (i % aantal_vr_rij) * x_afstand_vr - 20;
                o << "[Figure" << current << "]" << std::endl << "type = Vrachtwagen" << std::endl << "scale ="
                  << vr_Scale
                  << std::endl << "rotateX = 0" << std::endl << "rotateY = 0" << std::endl << "rotateZ = 0" << std::endl
                  << "center = (" << y_offs + y << "," << x << ",0)" << std::endl
                  << "color = (" << (random_color[0]) << "," << (random_color[1]) << ","
                  << random_color[2] << ")" << std::endl;
                current++;
            }
//            centrum_nr++;
        }
    }
    o.close();
    system((path_to_engine + " " + path_to_safe_dir+"/"+name+".ini > /dev/null").c_str());
    ENSURE(FileExists((path_to_safe_dir+"/"+name+".ini")),"geen nieuwe .ini file bij afloop van graphicIntegration");
    ENSURE(FileExists((path_to_safe_dir+"/"+name+".bmp")),"geen nieuwe .bmp file bij afloop van graphicIntegration");

}

void Simulation::addHub(Hub *hub1) {
    REQUIRE(hub1->correctlyInitialized(), "hub1 was niet geinitializeerd bij aanroep van addhub");
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij aanroep van addhub" );
    REQUIRE(hub1->getID() == (int) getHubs().size() , "het hub ID matcht niet het nummer in de lijst");
    unsigned int start_size =  hubs.size();
    hubs.push_back(hub1);
    ENSURE(start_size +1 == getHubs().size(), "getHubs().size()_start +1 != getHubs().size() bij afloop van adhub"  );

}
void Simulation::addcentrumToSim(Vaccinatiecentrum* centrum){
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij aanroep van addcentrumToSim" );
    REQUIRE(centrum->correctlyInitialized(), "centrum was niet geinitializeerd bij aanroep van addcentrumToSim");
    unsigned int start_size =  getVaccinatiecentra().size();
    this->vaccinatiecentra.push_back(centrum);
    ENSURE(start_size +1 == getVaccinatiecentra().size(), "getHubs().size()_start +1 != getHubs().size() bij afloop van adhub"  );

}

const std::vector<Hub *>& Simulation::getHubs() const {
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij aanroep van getHubs" );

    return hubs;
}

Simulation::Simulation() {
    dag = 0;
    statistische_gegevens[-1] = new Gegevens();
    _initcheck = this;
    ENSURE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij afloop van de constructor" );
    ENSURE(getDag() == 0, "simulatie is niet gestart op dag 0" );
}

bool Simulation::notDone() {
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij aanroep van notDone" );
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++){
        if ((*it)->notDone()){
            return true;
        }
    }
    return false;
}

int Simulation::getAantalGevaccineerden(){
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij afloop van getAantalGevaccineerden" );
    int aantal = 0;
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++){
        aantal += (*it)->getAantalEnkelGevaccineerden();
    }
    return aantal;
}

int Simulation::getAantalVolGevaccineerden(){
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij afloop van getAantalVolGevaccineerden" );
    int aantal = 0;
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++){
        aantal += (*it)->getAantalVolGevaccineerden();
    }
    return aantal;
}

void Simulation::outputGegevens(std::ostream& rapportstream){
    REQUIRE(correctlyInitialized(), "Simulatie was niet geinitializeerd bij afloop van outputGegevens" );
    for (std::map<int,Gegevens*>::const_iterator it = statistische_gegevens.begin()
            ; it != statistische_gegevens.end(); it++){
        if (it->first == -1){
            rapportstream << "Start:" << std::endl;
        }
        else {
            rapportstream << "DAG " << it->first << ":" << std::endl;
        }
        it->second->outputGegevens(rapportstream);
    }
}

Simulation::Simulation(const Simulation* const sim) {
    REQUIRE(sim->correctlyInitialized(), "sim was niet geinitializeerd bij oproep van de copy constructor");
    _initcheck = this;
    for (std::map<int, Gegevens*>::const_iterator it = sim->statistische_gegevens.begin(); it != sim->statistische_gegevens.end(); it++) {
        this->statistische_gegevens[it->first] = new Gegevens(it->second);
    }
//        statistische_gegevens.insert(sim->statistische_gegevens.begin(), sim->statistische_gegevens.end());
    this->dag = sim->getDag();
    std::map<std::string, Vaccinatiecentrum*> vac_map;

    const std::vector<Hub *> hubs_sim = sim->getHubs();
    const std::vector<Vaccinatiecentrum *> vac_sim = sim->getVaccinatiecentra();
    for (std::vector<Vaccinatiecentrum *>::const_iterator it = vac_sim.begin(); it != vac_sim.end(); it++) {
        vaccinatiecentra.push_back(new Vaccinatiecentrum(*it));
        vac_map.insert(std::make_pair(vaccinatiecentra.back()->getNaamCentrum(), vaccinatiecentra.back()));
    }
    for (std::vector<Hub *>::const_iterator it = hubs_sim.begin(); it != hubs_sim.end(); it++) {
        hubs.push_back(new Hub(*it, vac_map ));
    }
    ENSURE(correctlyInitialized(), "simulatie was niet geinitializeerd bij afloop van de copy constructor");
    ENSURE(getDag() == sim->getDag(), "dag is verkeerd gekopieerd" );
    ENSURE(getHubs().size() == sim->getHubs().size(), "hubs zijn verkeerd gekopieerd" );
    ENSURE(sim->getVaccinatiecentra().size() == getVaccinatiecentra().size(), "vaccinatiecentra zijn verkeerd gekopieerd");

}

Simulation::~Simulation() {
    REQUIRE(this->correctlyInitialized(),"simulatie was niet correct geinitializeerd bij oproep van de deconstructor" );
    for(unsigned int i = 0; i < hubs.size(); i++){
        if (hubs[i]->correctlyInitialized()){
            delete hubs[i];
        }
    }
    for(unsigned int i = 0; i < vaccinatiecentra.size(); i++){
        if (vaccinatiecentra[i]->correctlyInitialized()) {
            delete vaccinatiecentra[i];
        }
    }
    for (std::map<int,Gegevens*>::iterator it = statistische_gegevens.begin(); it != statistische_gegevens.end(); it++) {
        if (it->second->correctlyInitialized()) {
            delete it->second;
        }
    }
}

void Simulation::simulateDay(std::ostream &out) {
    REQUIRE(getStatistischeGegevens().find(getDag()-1) != getStatistischeGegevens().end(),"getDag()-1 zit niet in getStatistischeGegevens()");
    REQUIRE(correctlyInitialized(), "simulatie was niet correct geinitializeerd bij oproep van simulateDay");
    out << "DAG " << dag << ":" << std::endl;
    Gegevens *gegevens;
    gegevens = new Gegevens(statistische_gegevens.at(dag - 1));

//    1.1 IF er vaccins geleverd worden op de huidige dag
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        (*it)->vacLeveringen(dag);
        (*it)->outputHub(out);
    }
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
//        oss.str("");
//        oss.clear();
//        oss << "dag" << dag;

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit

        (*it)->transportToCentra2(dag, out, gegevens);
    }

//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++){
        (*it)->vaccineren(dag, out);
    }
    gegevens->setGevaccineerden(getAantalGevaccineerden());
    gegevens->setVolledigGevaccineerden(getAantalVolGevaccineerden());
    statistische_gegevens[dag] = gegevens;
    graphicIntegration("./src/engine","./tmp", ("Simulation_Day_" + std::to_string(dag)));
    nextDay();
    out << std::endl;
}

void Simulation::simulateManual(std::map<std::string, std::map<int, int>> vaccins_to_centra, std::ostream &out) {
    int tot_vac;
    int hub;
    for (std::map<std::string,std::map<int,int>>::const_iterator it = vaccins_to_centra.begin(); it!= vaccins_to_centra.end(); it++){
        tot_vac = 0;
        for(std::map<int,int>::const_iterator hub_it = (*it).second.begin(); hub_it != (*it).second.end(); hub_it++){
            tot_vac += hub_it->second;
            hub = hub_it->first;
        }
        REQUIRE(isAllowed(tot_vac, hub,it->first),"niet elke manuele versturing was toegestaan");
    }


    out << "DAG " << dag << ":" << std::endl;
    Gegevens* gegevens = new Gegevens(statistische_gegevens.at(dag-1));
//    1.1 IF er vaccins geleverd worden op de huidige dag
//    1.1.1 verhoog het aantal vaccins in de hub met het correcte aantal
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
        (*it)->vacLeveringen(dag);
        (*it)->outputHub(out);
    }
//    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++) {
//        oss.str("");
//        oss.clear();
//        oss << "dag" << dag;

//    1.2 FOR elk centrum verbonden met de hub
//    1.2.1 voer use case 3.1 uit

//        (*it)->transportToCentra2(dag, out, gegevens);
//    }
    for (std::map<std::string,std::map<int,int>>::const_iterator it = vaccins_to_centra.begin(); it!= vaccins_to_centra.end(); it++) {
        for (std::map<int, int>::const_iterator hub_it = (*it).second.begin(); hub_it != (*it).second.end(); hub_it++) {
            sendVaccins(hub_it->second, hub_it->first, it->first,out);
        }
    }


//        this->graphicIntegration("./src/engine","./graphics1",oss.str());
//    1.3 FOR elk centrum
//    1.3.1 voer use case 3.2 uit
    for (std::vector<Hub*>::const_iterator it = hubs.begin(); it != hubs.end(); it++){
        (*it)->vaccineren(dag, out);
    }
    gegevens->setGevaccineerden(getAantalGevaccineerden());
    gegevens->setVolledigGevaccineerden(getAantalVolGevaccineerden());
    statistische_gegevens[dag] = gegevens;
    nextDay();
    out << std::endl;
}

const std::vector<Vaccinatiecentrum *> &Simulation::getVaccinatiecentra() const {
    REQUIRE(correctlyInitialized(), "simulatie was niet correct geinitializeerd bij aanroep van getVaccinatiecentra");
    return vaccinatiecentra;
}

bool Simulation::isAllowed(const int vaccins, const int hub_id, const std::string name_centrum) {

    return hubs.at(hub_id)->isAllowed(vaccins,name_centrum);
}

void Simulation::sendVaccins(const int vaccins, const unsigned int hub_id, const std::string name_centrum, std::ostream &out) {
    REQUIRE(this->correctlyInitialized(), "simulatie was niet correct geinitializeerd bij aanroep van sendVaccins");
    REQUIRE(getHubs().size()>hub_id,"hub_id is te groot");
    REQUIRE(getHubs().at(hub_id)->getVaccinatiecentra().find(name_centrum) != getHubs().at(hub_id)->getVaccinatiecentra().end(), "de hub heeft geen verbinding met het meegegeven centrum" );
    hubs.at(hub_id)->sendVaccins(vaccins, name_centrum, this->getDag(),out);
}

int Simulation::getAantalInwoners(){
    REQUIRE(correctlyInitialized(),"simulatie was niet correct geinitializeerd bij aanroep van getAantalInwoners");
    int inwoners = 0;
    for (std::vector<Vaccinatiecentrum*>::const_iterator it = this->vaccinatiecentra.begin(); it != this->vaccinatiecentra.end(); it++ ) {
        inwoners += (*it)->getAantalInwoners();
    }
    return inwoners;
}

const Gegevens* Simulation::getGegevens(int _dag){
    REQUIRE(correctlyInitialized(),"simulatie was niet correct geinitializeerd bij aanroep van getGegevens");
    REQUIRE(_dag >= -1, "de dag moet >= -1 zijn" );
    return this->statistische_gegevens.at(_dag);
}

const std::map<int, Gegevens *> &Simulation::getStatistischeGegevens() const {
    REQUIRE(correctlyInitialized(),"simulatie was niet correct geinitializeerd bij aanroep van getStatistischeGegevens");
    return statistische_gegevens;
}

void Simulation::exportToGif(std::string filepath,std::string path_to_safe_dir){
    std::string command = "convert -delay 100 " + path_to_safe_dir+'/'+"*.bmp " + filepath;
    system(command.c_str());
}