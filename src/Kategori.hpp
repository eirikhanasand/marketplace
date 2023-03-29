/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <list>
#include <string>
#include "NyTing.hpp"

class Kategori {
public:
    Kategori(std::string KategoriNavn);

    ~Kategori();

    void settData();

    void skrivData();

    std::string hentNavn() const;

    void lagTing();
    
    void skrivFullKategori();

    int hentAntallTing();

private:
    std::list<NyTing*> tingListe;

    int antallTingTilSalgs;

    std::string kategoriNavn;
};

#endif