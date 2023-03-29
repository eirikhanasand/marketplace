/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <fstream>
#include <list>
#include <string>

#include "NyTing.hpp"

class Kategori {
public:
    Kategori(std::string KategoriNavn);
    Kategori(std::ifstream &kundeFil);

    ~Kategori();

    void settData();

    void skrivData() const;

    std::string hentNavn() const;

    void lagTing();
    
    void skrivFullKategori();

    int hentAntallTing();
    
    void skrivTilFil(std::ofstream &kundeFil);


    NyTing* finnTing(int kundeNummer);

private:
    std::list<NyTing*> tingListe;

    int antallTingTilSalgs;

    std::string kategoriNavn;
};

#endif