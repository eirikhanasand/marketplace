/**
 *  Definisjon av funksjoner i Kunde klassen
 *
 *  @file      kunde.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Kunde.hpp"
#include "Kunder.hpp"
#include "LesData3.hpp"
#include "NyTing.hpp"

extern Kunder gKundebase;

// Opprettet kunde med kundenummer
Kunde::Kunde(int KundeNummer) {
    kundenummer = KundeNummer;
    settData();
}

// Leser kunde fra fil
Kunde::Kunde(std::ifstream &kundeFil) {
    kundeFil >> kundenummer;
    kundeFil.ignore();

    kundeFil >> mobilnummer;
    kundeFil.ignore();

    kundeFil >> postnummer;
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

// Destructor
Kunde::~Kunde() {
    // todo
}

// Setter data for kunde
void Kunde::settData() {
    navn = lesString("Navn");
    gateAdresse = lesString("Gateadresse");
    mobilnummer = lesInt("Mobilnummer", 40000000, 99999999);
    mailAdresse = lesString("Mailadresse");
    postSted = lesString("Poststed");
    postnummer = lesInt("Postnummer", 0, 9999);

    antallTingKjopt = 0;
    antallTingSolgt = 0;
    antallTingTilSalgs = 0;
}

// Returnerer kunde sitt kundenummer
int Kunde::hentKundenummer() {
    return kundenummer;
}

// Skriver all data om kunde
void Kunde::skrivData() const {
    std::cout << "Navn: " << navn << '\n' << "Gateadresse: " << gateAdresse << '\n' << "Mobilnummer: " 
    << mobilnummer << '\n' << "Mailadresse: " << mailAdresse << '\n' << "Poststed: " << postSted << '\n' 
    << "Postnummer: " << postnummer << '\n' << "Antall ting kjøpt: " << antallTingKjopt << '\n' 
    << "Antall ting solgt: " << antallTingSolgt << '\n' << "Antall til salgs: " << antallTingTilSalgs << std::endl;
}

// Skriver basisinfo om kunde
void Kunde::skrivInfo() const {
    std::cout << "Kundenummer: " << kundenummer << "\tNavn: " << navn << "\tTlf: " << mobilnummer << std::endl;
}

// Skriver til fil
void Kunde::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kundenummer << ' ' << mobilnummer << ' ' << postnummer << ' ' 
    << antallTingKjopt << ' ' << antallTingSolgt << ' ' << antallTingTilSalgs << '\n'
    << navn << '\n' << gateAdresse << '\n' << postSted << '\n' << mailAdresse << '\n';
}

// Kunde kjøper en ting
void Kunde::kjopTing(Kategori *kategori, NyTing *ting) {
    int selgernummer = ting->hentKundenummer();
    Kunde* selger = gKundebase.hentKunde(selgernummer);

    if (kundenummer != selgernummer) {
        std::cout << "Kjøpte ting " << ting->hentNavn() << std::endl;
        selger->selgTing(ting);
        antallTingKjopt+=1;
    } else {
        std::cout << "Du kan ikke kjøpe av deg selv!" << std::endl;
    }
}

// Kunde selger en ting
void Kunde::selgTing(NyTing *ting) {
    int antall = ting->hentAntall();
    antallTingSolgt+=1;
    antallTingTilSalgs-=1;

    if (antall > 1) {
        ting->endreAntall(antall-1);
    } else {
        delete ting;
    }
}