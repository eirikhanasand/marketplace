/**
 *   Header for klassen Kategorier
 *
 *   @file      Kategorier.h
 *   @authors   todo
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <string>
#include <map>
#include "kategori.h"

class Kategorier {
    public:
        // Kart over kategorier
        std::map<std::string, Kategori*> nyTingMap;

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

        // Sjekker om kategori finnes med samme navn
        bool kategoriFinnes(std::string kategoriNavn);

        // Skriver alle kategorier
        void skrivAlle();

        // Finner kategori hvis kategori stemmer
        Kategori* finnKategori(std::string kategoriNavn);
};

#endif