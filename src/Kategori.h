/**
 *   Header for klassen Kategori
 *
 *   @file      Kategori.h
 *   @authors   todo
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <list>
#include <string>
#include "nyTing.h"

class Kategori {
    int antallTilSalgs;
    
    std::string kategoriNavn;
    
    public:
        std::list<NyTing*> NyTing;
        
        // Constructor
        Kategori(std::string KategoriNavn);

        // Destructor
        ~Kategori();

        // Setter kategoridata
        void settData();

        // Skriver kategoridata
        void skrivData();

        // Henter kategorinavn
        std::string hentNavn() const;
};

#endif