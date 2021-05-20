//============================================================================
// Name        : Vaccinatiecentrum.h
// Author      : Sam Roggeman - Said Yandarbiev
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Sam Roggeman - Said Yandarbiev - University of Antwerp
// Description : Vaccinatiecentrum in C++, Ansi-style
//============================================================================

#ifndef PROJECT_VACCINATIECENTRUM_H
#define PROJECT_VACCINATIECENTRUM_H

#include "DesignByContract.h"
#include "iostream"
#include <string>
#include <math.h>
#include <map>
#include "VaccinType.h"



class Vaccinatiecentrum {
    Vaccinatiecentrum * _initCheck;
    std::map<std::string,int> vaccins;
    std::string naam_centrum;
    std::string adres_centrum;
    std::map<std::string, VaccinType*> types;
    int aantal_inwoners;
    int capaciteit;
    int aantal_gevaccineerden;
    int aantal_vol_gevaccineerden;
    std::map<std::string,std::map<int,int> > hernieuwingen;
public:
    const std::map<std::string, int> &getVaccins() const;

    const std::map<std::string, VaccinType *> &getTypes() const;

    const std::map<std::string, std::map<int, int> > &getHernieuwingen() const;


    /**maakt een vaccinatiecentrum object aan
     * @return vaccinatiecentrum
     * @post this->correctlyInitialized()
     * @post getAantalEnkelGevaccineerden() == 0
     * @post capaciteit == 0
     * @post aantal_inwoners == 0
     * @post getAantalVolGevaccineerden() ==0
     * @post getHernieuwingen().empty
     * @post naam_centrum is leeg
     * @post adres centrum is leeg
     * */
    Vaccinatiecentrum();

//GETTERS SETTERS

    void setHernieuwing(std::map<std::string,std::map<int,int> > h){
        hernieuwingen = h;
    }

    std::map<std::string,std::map<int,int> > getHernieuwing(){
        return hernieuwingen;
    }
    /**veranderd de naam van het centrum naar naamCentrum
     * @param naamcentrum: nieuwe naam van het centrum
     * @pre this.correctlyInitialized()
     * @pre naamcentrum.size > 0
     * @post naam_centrum == naamcentrum
     * */
    void setNaamCentrum(const std::string &naamcentrum);

    /**returnt de naam van het centrum
     * @return de naam van het centrum
     * @pre this.correctlyInitialized()
     * */
    const std::string &getNaamCentrum() const;

    /**veranderd het adres van het centrum naar adresCentrum
     * @param adrescentrum: nieuw adres van het centrum
     * @pre this.correctlyInitialized()
     * @pre adrescentrum.size > 0
     * @post adres_centrum == adrescentrum
     * */
    void setAdresCentrum(const std::string &adrescentrum);

    /**returnt het adres van het centrum
     * @return het adres van het centrum
     * @pre this.correctlyInitialized()
     * */
    const std::string &getAdresCentrum() const;

    /**zet het aantal inwoners dat bij het centrum hoort op aantal_inwoners
     * @param aantal: nieuwe aantal inwoners
     * @pre aantal >= 0
     * @pre this.correctlyInitialized()
     * @post aantal_inwoners == aantal
     * */
    void setAantalInwoners(int aantal);

    /**returnt het aantal inwoners dat bij het centrum hoort
     * @return het aantal inwoners
     * @pre this.correctlyInitialized()
     * */
    int getAantalInwoners() const;

    /**returnt het aantal vaccins in het centrum
     * @return het aantal vaccins in het centrum
     * @pre this.correctlyInitialized()
     * */
    int getAantalVaccinsVanType(std::string naam_type) const;

    /**zet het aantal vaccins in het centrum op aantal
     * @param het nieuwe aantal vaccins
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post this->getVaccins()[naam_type] == aantal
     */
    void setAantalVaccins(std::string naam_type, int aantal);

    /**zet de vaccinatiecapaciteit op capaciteit1
     * @param aantal: De nieuwe capaciteit van het centrum
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post capaciteit == aantal
     * */
    void setCapaciteit(int aantal);

    /**returnt de vaccinatiecapaciteit per dag
     * @return de capaciteit van het centrum
     * @pre this.correctlyInitialized()
     * */
    int getCapaciteit() const;

    /**zet de gevaccineerden op aantalGevaccineerden
     * @param aantal: het nieuwe aantal gevaccineerden
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * */
    void setAantalGevaccineerden(int aantal);

    /**returt het aantal mensen dat gevaccineerd is
     * @return het aantal gevaccineerden
     * @pre this.correctlyInitialized()
     * */
    int getAantalGevaccineerden() const;

//VACCIN OPERATIONS
    /**substract het aantal van het huidige aantal vaccins van dat type
     * @param aantal: het aantal vaccins dat geleverd werd werd
     * @param naam_type de naam van het type dat geleverd wordt
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post getVaccins()[naam_type] += aantal
     * */
    void addVaccins(int aantal, std::string naam_type);

    /**substract het aantal van het huidige aantal vaccins van dat type
     * @param naam_type de naam van het type dat geleverd wordt
     * @param aantal: het aantal vaccins dat gebruikt werd
     * @pre this.correctlyInitialized()
     * @pre aantal >= 0
     * @post getVaccins()[naam_type] -= aantal
     * @post getVaccins()[naam_type] >= 0
     * */
    void substractVaccins(int aantal, std::string naam_type);

// GEVACCINEERDEN OPERATIONS
    /**add aantal_gevaccineerden toe aan het totaal aantal gevaccineren
     * @param aantal_gevaccineerden: het aantal mensen dat gevaccineerd werd
     * @pre this.correctlyInitialized()
     * @pre aantal_gevaccineerden >= 0
     * @post getAantalEnkelGevaccineerden() += aantal_gevaccineerden
     * */
    void addGevaccineerden(int aantal_gevaccineerden);

    /**returnt het aantal ongevaccineerden
     * @returnt : aantal_inwoners - getAantalEnkelGevaccineerden()
     * @pre this.correctlyInitialized()
     * @post aantalOngevaccineerden >= 0
     * */
    int aantalOngevaccineerden() const;

//METHODS
    /**kijkt na of het cenrum correct geinitializeerd is
     * @returns true als correct
     * */
    bool correctlyInitialized() const;

    /**vaccinaties worden uitgevoerd en output gaat naar std::cout
    * @param out: de outstream waarnaar de output gestuurt wordt
     * @param dag de huidige dag
     * @pre this.correctlyInitialized()
     * @pre dag >= 0
     * @post aantal_vaccins voor elk type <= aantal_vaccins_start voor elk type
     * @post getAantalGevaccineerden() <= getAantalEnkelGevaccineerden()_start
     * @post hernieuwingen gepland voor vandaag == 0
     * */
    void vaccineren(int dag);

    /**vaccinaties worden uitgevoerd en output gaat naar out
     * @param out: de outputstream waarnaar de output gestuurt wordt
     * @param dag de huidige dag
     * @pre this.correctlyInitialized()
     * @pre dag >= 0
     * @post aantal_vaccins voor elk type <= aantal_vaccins_start voor elk type
     * @post getAantalGevaccineerden() <= getAantalEnkelGevaccineerden()_start
     * @post aantal gekoelde vaccins == 0
     * */
    void vaccineren(int dag, std::ostream &out);

    /**kijkt na of een centrum volledig geinitializeerd is
     * @pre this.correctlyInitialized()
     *  @return true als completelyInitialized (strikt positieve capaciteit, een naam, een adres en strikt positief aantal inwoners)
     * */
    bool completelyInitialized() const;

    /**
     * berekend het totaal aantal vaccins uit het centrum
     * @return het totaal aantal vaccins in het centrum
     * @pre this.correctlyInitialized()
     * @post aantal_vac >= 0
     */
    int getAantalVaccins()const;

    /**
     * maakt een grafische impressie van het centrum
     * @pre this->correctlyinitialized
     * @pre this->completelyinitialized
     * @param out de ostream waarnaar de impressie gestuurd wordt
     */
    void impressie(std::ostream &out);

    /**
     * zet de map met types die in de in het centrum
     * @pre this->correctlyinitialized
     * @post getVaccins()[type.getname] == 0;
     */
    void setTypes(std::map<std::string, VaccinType*> map);

    /**
     * vraagt het aantal gereserveerde vaccins op van type met naam naam_type
     * @return het aantal vaccins dat van dit type gereserveerd is
     * @param naam_type de naam van het vaccintype
     * @param dag de huidige dag
     * @pre this->correctlyinitialized
     * @pre dag >= 0
     */
    int getAantalGeres(std::string naam_type, int dag);

    /**
     * vraagt het aantal volledig gevaccineerden op
     * @pre this->correctlyinitialized
     * @return het aantal volledig gevaccineerden
     */
    int getAantalVolGevaccineerden();

    /**
     * returnt het aantal herniuwingen dat zal gebeuren op dag dag
     * @param dag de opgevraagde dag
     * @pre this->correctlyinitialized
     * @pre dag >= 0
     * @return
     */
    int getAantalHernieuwing(int dag);

    /**
     * vraagt het aantal gereserveerde vaccins op van type met naam naam_type
     * @return het aantal vaccins dat van dit type gereserveerd is
     * @param naam_type de naam van het vaccintype
     * @param dag de huidige dag
     * @pre this->correctlyinitialized
     * @pre getTypes().find(naam_type) != getTypes().end()
     * @pre dag >= 0
     * @pre aantal >= 0
     */
    void substractAantalGeres(std::string naam_type, int dag, int aantal);

    /**
     * berekend het aantal onvolledig gevaccineerden
     * @return totaal aantal inwoners - totaal aantal volledig gevacinneerden
     * @pre this->correctlyinitialized
     */
    int aantalOnvolledigGev();
};


#endif //PROJECT_VACCINATIECENTRUM_H
