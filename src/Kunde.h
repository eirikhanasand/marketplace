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

    public:
        // Constructor
        Kunde(int KundeNummer);

        // Destructor
        ~Kunde();

        // Reads user data
        void settData();
};

#endif