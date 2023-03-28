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
#include "kategori.h"

class Kategorier {
    int sisteNr;

    std::map<std::string, Kategori*> nyTingMap;

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

        // Oppretter ny kategori
        void nyKategori();

        //Sjekker om kategori finnes med samme navn
        void kategoriFinnes(std::string kategoriNavn);
};

#endif