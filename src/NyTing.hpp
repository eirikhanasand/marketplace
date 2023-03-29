/**
 *  Definisjon av funksjoner i NyTing klassen
 *
 *  @file      NyTing.h
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __NYTING_H
#define __NYTING_H

#include <iostream>
#include <fstream>

class NyTing {
public:
    NyTing(int Nummer);

    NyTing(ofstream & tingFil); // kan denne være virtual? Trengs mtp bruktting

    ~NyTing();

    virtual void settData();

    virtual void skrivData() const;

    std::string hentNavn() const;
    int hentKundeNummer() const;


    void endreNavn(std::string nyttNavn);
    void endrePris(int nyPris);
    void endreAntall(int nyttAntall);
    void endreBeskrivelse(std::string nyBeskrivelse);

    virtual void skrivTilFil(ofstream & tingFil);
    void endreTing();
    
private:
    int nummer;
    int pris;
    int antall;

    std::string navn;
    std::string beskrivelse;
};

#endif