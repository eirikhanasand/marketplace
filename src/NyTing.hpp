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

    void settData();

    void kjopTing();

    std::string hentNavn() const;

private:
    int nummer;
    int pris;
    int antall;

    std::string navn;
    std::string beskrivelse;
};

#endif