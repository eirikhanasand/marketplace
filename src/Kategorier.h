/**
 *   Header for klassen Kategorier
 *
 *   @file      Kategorier.h
 *   @authors   todo
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <map>
#include "Kategori.h"

class Kategorier {
    int sisteNr;

    std::map <std::string, Kategori*> nytingMap;

    public:
        // Constructor
        Kategorier();

        // Destructor
        ~Kategorier();
        
        // Håndterer valg
        void handling(char valg);

        // Leser fra fil
        void lesFraFil();

        // Skriver til fil
        void skrivTilFil();
};

#endif