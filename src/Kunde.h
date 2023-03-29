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
    // Constructor
    Kunde(int KundeNummer);

    // Destructor
    ~Kunde();

    // Input user data
    void settData();

    // Skriver data om kunden
    void skrivData();

    // Henter kundenummer
    int hentKundeNummer();

    // Printer kundenummer navn og telefonnummer
    void skrivInfo();

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