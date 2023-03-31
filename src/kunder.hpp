/**
 *  Header for Kunder klassen
 *
 *  @file      kunder.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KUNDER_H
#define __KUNDER_H

#include <iostream>
#include <list>

#include "kunde.hpp"

class Kunder {
public:
    ~Kunder();

    void handling(char valg);

    void skrivAlle();

    void lesFraFil();

    void skrivAlleTilFil();

    void fjernKunde(int kundenummer);

    Kunde *hentKunde(int kundenummer);

    int antallKunder();

    void lagKunde();

private:
    std::list<Kunde *> kundeListe;

    int sistenummer;
};

#endif