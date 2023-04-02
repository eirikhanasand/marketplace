/**
 *  Header for Kunde klassen
 *
 *  @file      Kunde.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KUNDE_H
#define __KUNDE_H

#include <fstream>
#include <string>

#include "kategori.hpp"

class Kunde {
public:
    Kunde(int Kundenummer);
    Kunde(std::ifstream &kundeFil, int Kundenummer);
    int hentKundenummer();
    void kjopTing(Kategori *kategori, NyTing *ting, int kundenummer);
    void selgTing(NyTing *ting);
    void settData();
    void skrivData() const;
    void skrivInfo() const;
    void skrivTilFil(std::ofstream &kundeFil);

private:
    int kundenummer;
    int mobilnummer;
    int postnummer;
    int antallTingKjopt;
    int antallTingSolgt;
    int antallTingTilSalgs;

    std::string navn;
    std::string gateAdresse;
    std::string postSted;
    std::string mailAdresse;
};

#endif