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
#include "kunde.h"

class Kunder {
    int sisteNr;

    public:
        std::list<Kunde*> kundeListe;
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

        // Sletter kunde
        void slettKunde();

        // Finner kunde
        Kunde* finnKunde(int kundeNummer);
};

#endif