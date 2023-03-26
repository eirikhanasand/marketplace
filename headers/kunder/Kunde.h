/**
 *   Header for klassen Kunde
 *
 *   @file      Kunde.h
 *   @authors   todo
 */

#ifndef __KUNDE_H
#define __KUNDE_H

struct Kunde {
    int mobilNummer;
    int postNummer;
    int antallTingKjøpt;
    int antallTingSolgt;
    int antallTilSalgs;

    std::string navn;
    std::string gateAdresse;
    std::string poststed;
    std::string mailAdresse;
};

#endif