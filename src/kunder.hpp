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
    Kunde *hentKunde(int kundenummer) const;
    int sisteKunde() const;
    void fjernKunde(int kundenummer);
    void handling(char valg);
    void lagKunde();
    void lesFraFil();
    void skrivAlle() const;
    void skrivAlleTilFil() const;
    int hentAntallKunder() const;

 private:
    std::list<Kunde *> kundeListe;
    int sisteKundenummer = 0;
};

#endif