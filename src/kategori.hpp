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
    NyTing* hentTing(int tingnummer) const;
    NyTing* hentTingMedIndeks(int indeks) const;
    std::string hentNavn() const;
    int sisteTing() const;
    void settData(std::string navn);
    void skrivData() const;
    void skrivTingMindre() const;
    void lagTing();
    void skrivTing() const;
    void skrivTingIndeksert() const;
    void skrivTilFil(std::ofstream &kundeFil) const;
    void fjernTing(NyTing *ting);
    void fjernTingMedSelgernummer(int kundenummer);
    int antallTing() const;

 private:
    std::list<NyTing*> tingListe;
    std::string kategoriNavn;
    int sisteTingnummer = 0;
};

#endif