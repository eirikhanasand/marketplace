/**
 *   Header for klassen Kategorier
 *
 *   @file      Kategorier.h
 *   @authors   todo
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include "Kategori.h"
#include <iostream>
#include <map>

struct Kategorier {
    int sisteNr;

    std::map <std::string, Kategori*> nytingMap;

    public:
        // Constructor
        Kategorier();

        // Håndterer valg
        void handling(char valg);

        // Leser fra fil
        void lesFraFil();

        // Skriver til fil
        void skrivTilFil();
};

#endif