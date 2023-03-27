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
    int sisteNr;

    std::list<Kunde*> kundeListe;

    public:
        // Constructor
        Kunder();

        // Destructor
        ~Kunder();

        // Håndterer valg
        void handling();

        void skrivAlleKunder();

        // Leser fra fil
        void lesFraFil();

        // Skriver til fil
        void skrivTilFil();

};

#endif