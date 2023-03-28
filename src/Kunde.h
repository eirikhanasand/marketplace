/**
 *   Header for klassen Kunde
 *
 *   @file      Kunde.h
 *   @authors   todo
 */

#ifndef __KUNDE_H
#define __KUNDE_H

#include <string>

class Kunde {

public:
    int kundeNummer;
    int mobilNummer;
    int postNummer;
    int antallTingKjopt;
    int antallTingSolgt;
    int antallTilSalgs;

    std::string navn;
    std::string gateAdresse;
    std::string postSted;
    std::string mailAdresse;

    // Constructor
    Kunde(int KundeNummer);

    // Destructor
    ~Kunde();

    // Input user data
    void settData();

    // Writes name of customer
    void skrivKunde();

    // Prints user data
    void skrivData();
};

#endif