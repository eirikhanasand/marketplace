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
#include <list>
#include <string>

#include "nyTing.hpp"

class Kategori {
public:
    Kategori();
    Kategori(std::ifstream &kundeFil);

    ~Kategori();

    void settData(std::string navn);

    void skrivData() const;

    std::string hentNavn();

    void lagTing();

    void skrivFullKategori();

    int hentAntallTing();

    void skrivTilFil(std::ofstream &kundeFil);

    NyTing* hentTing(int kundeNummer);

private:
    std::list<NyTing*> tingListe;

    int antallTingTilSalgs;

    std::string kategoriNavn;
};

#endif