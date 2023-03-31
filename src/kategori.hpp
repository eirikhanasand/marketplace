/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      bruktTing.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "nyTing.hpp"

class Kategori {
public:
    Kategori();    
    Kategori(std::ifstream &kundeFil);
    NyTing* hentTing(int kundeNummer);
    std::string hentNavn();
    int hentAntallTing();
    void settData(std::string navn);
    void skrivData() const;
    void lagTing();
    void skrivTing();
    void skrivTilFil(std::ofstream &kundeFil);

private:
    std::list<NyTing*> tingListe;

    int antallTingTilSalgs;

    std::string kategoriNavn;
};

#endif