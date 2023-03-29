/**
 *  Header for Kunder klassen
 *
 *  @file      Kunder.h
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KUNDER_H
#define __KUNDER_H

#include <iostream>
#include <list>

#include "Kunde.hpp"

class Kunder {
public:
    Kunder();

    ~Kunder();

    void handling();

    void skrivAlle();

    void lesFraFil();

    void skrivAlleTilFil();

    void fjernKunde(int kundeNummer);

    Kunde *finnKunde(int kundeNummer);

    int antallKunder();

    void lagKunde();

private:
    std::list<Kunde *> kundeListe;

    int sisteNummer;
};

#endif