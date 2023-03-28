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

        // First customer
        void sisteKunde();

        // Håndterer valg
        void handling();

        void skrivAlle();

        // Reads from file
        void lesFraFil();

        // Writes to file
        void skrivTilFil();

        // Deletes customer
        void slettKunde(int kundeNummer);

        // Checks if customer exists
        Kunde* finnKunde(int kundeNummer);
};

#endif