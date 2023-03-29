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

class Kunde {
public:
    Kunde(int KundeNummer);
    Kunde(std::ifstream &kundeFil);

    ~Kunde();

    void settData();

    void skrivData();

    int hentKundeNummer();

    void skrivInfo();
    
    void skrivTilFil(std::ofstream &kundeFil);

private:
    int kundeNummer;
    int mobilNummer;
    int postNummer;
    int antallTingKjopt;
    int antallTingSolgt;
    int antallTingTilSalgs;

    std::string navn;
    std::string gateAdresse;
    std::string postSted;
    std::string mailAdresse;
};

#endif