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
#include "unordered_map"
#include "Kategori.h"

class Kategorier {
    int sisteNr;

    std::unordered_map<std::string, Kategori*> nyTingMap;

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