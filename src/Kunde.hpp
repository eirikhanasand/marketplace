/**
 *  Header for Kunde klassen
 *
 *  @file      Kunde.h
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KUNDE_H
#define __KUNDE_H

#include <string>
#include <fstream>
#include <string>
#include "Kategori.hpp"

class Kunde {
public:
    Kunde(int Kundenummer);
    Kunde(std::ifstream &kundeFil);

    ~Kunde();

    void settData();

    void skrivData() const;

    int hentKundenummer();

    void skrivInfo() const;
    
    void skrivTilFil(std::ofstream &kundeFil);

    void kjopTing(Kategori *kategori, NyTing *ting);

    void selgTing(NyTing *ting);


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