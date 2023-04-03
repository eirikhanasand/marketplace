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
    Kategori(std::ifstream &kundeFil, std::string navn);
    NyTing* hentTing(int tingnummer);
    NyTing* hentTingMedIndeks(int indeks);
    std::string hentNavn();
    int sisteTing();
    void settData(std::string navn);
    void skrivData() const;
    void skrivTingMindre() const;
    void lagTing();
    void skrivTing() const;
    void skrivTingIndeksert() const;
    void skrivTilFil(std::ofstream &kundeFil);
    void fjernTing(NyTing *ting);
    int antallTing();

private:
    std::list<NyTing*> tingListe;
    int sisteTingnummer = 0;
    std::string kategoriNavn;
};

#endif