/**
 *  Definisjon av funksjoner i NyTing klassen
 *
 *  @file      NyTing.h
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __NYTING_H
#define __NYTING_H

#include <iostream>

class NyTing {
public:
    NyTing(int Nummer);

    ~NyTing();

    virtual void settData();

    virtual std::string skrivData() const;

    std::string hentNavn() const;

    void endreNavn(std::string nyttNavn);
    void endrePris(int nyPris);
    void endreAntall(int nyttAntall);
    void endreBeskrivelse(std::string nyBeskrivelse);

private:
    int nummer;
    int pris;
    int antall;

    std::string navn;
    std::string beskrivelse;
};

#endif