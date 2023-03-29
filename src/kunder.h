/**
 *   Header for klassen Kunder
 *
 *   @file      Kunder.h
 *   @authors   todo
 */

#ifndef __KUNDER_H
#define __KUNDER_H

#include <iostream>
#include <list>
#include "Kunde.h"

class Kunder {
public:
    // Constructor
    Kunder();

    // Destructor
    ~Kunder();

    // Håndterer valg
    void handling();

    // Skriver alle kunder
    void skrivAlle();

    // Leser fra fil
    void lesFraFil();

    // Skriver til fil
    void skrivTilFil();

    // Fjerner kunde
    void fjernKunde(int kundeNummer);

    // Finner kunde
    Kunde *finnKunde(int kundeNummer);

private:
    std::list<Kunde *> kundeListe;

    int sisteNummer;
};

#endif