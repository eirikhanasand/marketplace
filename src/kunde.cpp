/**
 *  Definisjon av funksjoner i Kunde klassen
 *
 *  @file      kunde.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>

#include "Kunde.hpp"
#include "Kunder.hpp"
#include "LesData3.hpp"

extern Kunder gKundebase;

Kunde::Kunde(int KundeNummer) {
    kundeNummer = KundeNummer;
    settData();
}

Kunde::Kunde(std::ifstream &kundeFil) {
    kundeFil >> kundeNummer;
    kundeFil.ignore();

    kundeFil >> mobilNummer;
    kundeFil.ignore();

    kundeFil >> postNummer;
    kundeFil.ignore();

    kundeFil >> antallTingKjopt;
    kundeFil.ignore();

    kundeFil >> antallTingSolgt;
    kundeFil.ignore();

    kundeFil >> antallTingTilSalgs;
    kundeFil.ignore();

    std::getline(kundeFil, navn);
    navn[navn.length()-1] = '\0';

    std::getline(kundeFil, gateAdresse);
    gateAdresse[gateAdresse.length()-1] = '\0';

    std::getline(kundeFil, postSted);
    postSted[postSted.length()-1] = '\0';

    std::getline(kundeFil, mailAdresse);
    mailAdresse[mailAdresse.length()-1] = '\0';
}

Kunde::~Kunde() {
    // todo
}

void Kunde::settData() {
    navn = lesString("Navn");
    gateAdresse = lesString("Gateadresse");
    mobilNummer = lesInt("Mobilnummer", 40000000, 99999999);
    mailAdresse = lesString("Mailadresse");
    postSted = lesString("Poststed");
    postNummer = lesInt("Postnummer", 0, 9999);

    antallTingKjopt = 0;
    antallTingSolgt = 0;
    antallTingTilSalgs = 0;
}

int Kunde::hentKundeNummer() {
    return kundeNummer;
}

void Kunde::skrivData() {
    std::cout << "Navn: " << navn << '\n' << "Gateadresse: " << gateAdresse << '\n' << "Mobilnummer: " 
    << mobilNummer << '\n' << "Mailadresse: " << mailAdresse << '\n' << "Poststed: " << postSted << '\n' 
    << "Postnummer: " << postNummer << '\n' << "Antall ting kjøpt: " << antallTingKjopt << '\n' 
    << "Antall ting solgt: " << antallTingSolgt << '\n' << "Antall til salgs: " << antallTingTilSalgs << std::endl;
}

void Kunde::skrivInfo() {
    std::cout << "Kundenummer: " << kundeNummer << "\tNavn: " << navn << "\tTlf: " << mobilNummer << std::endl;
}

void Kunde::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kundeNummer << ' ' << mobilNummer << ' ' << postNummer << ' ' 
    << antallTingKjopt << ' ' << antallTingSolgt << ' ' << antallTingTilSalgs << '\n'
    << navn << '\n' << gateAdresse << '\n' << postSted << '\n' << mailAdresse << '\n';
}