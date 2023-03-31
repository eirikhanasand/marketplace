/**
 *  Definisjon av funksjoner i NyTing klassen
 *
 *  @file      nyTing.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __NYTING_H
#define __NYTING_H

#include <iostream>
#include <fstream>
#include <string>

class NyTing {
public:
    NyTing(int Nummer);

    NyTing(std::ifstream & tingFil);

    virtual void settData();
    virtual void settData(std::ifstream &tingFil);
    virtual void settRestData(std::ifstream &tingFil);
    virtual void skrivData() const;

    std::string hentNavn() const;
    int hentNummer() const;
    int hentAntall();
    void endreTing();
    int hentSelgernummer() const;
    void endreNavn(std::string nyttNavn);
    void endrePris(int nyPris);
    void endreAntall(int nyttAntall);
    void endreBeskrivelse(std::string nyBeskrivelse);

    virtual void skrivTilFil(std::ofstream & tingFil);

private:
    int selgernummer;
    int nummer;
    int pris;
    int antall;

    std::string navn;
    std::string beskrivelse;
};

#endif