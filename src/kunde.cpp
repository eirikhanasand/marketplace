/**
 *   todo
 *
 *   @file      kunde.cpp
 *   @authors   todo
 */

#include <iostream>
#include "Kunde.h"
#include "Kunder.h"
#include "LesData3.h"

extern Kunder gKundebase;

// Constructor
Kunde::Kunde(int KundeNummer) {
    kundeNummer = KundeNummer;
    settData();
};

// Destructor
Kunde::~Kunde(int kundeNummer) {
    
};

void skrivKunde() {
    lesInt("Kundenummer: ",1,INT32_MAX);
    if (gKundebase.hentKunde()) {
        kundeSkrivData();  
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    };
} 

void Kunde::settData() {
    std::cout << "Navn: " << std::endl;
    std::getline(std::cin, navn);

    std::cout << "Gateadresse: " << std::endl;
    std::getline(std::cin, gateAdresse);

    mobilNummer = lesInt("Mobilnummer", 40000000, 99999999);

    std::cout << "Mailadresse: " << std::endl;
    std::getline(std::cin, mailAdresse);

    std::cout << "Poststed: " << std::endl;
    std::getline(std::cin, postSted);

    postNummer = lesInt("Postnummer", 0, 9999);

    antallTingKjopt = 0;
    antallTingSolgt = 0;
    antallTilSalgs = 0;
};

void Kunde::skrivData() {
    std::cout << "Navn: " << navn << std::endl;
    std::cout << "Gateadresse: " << gateAdresse << std::endl;
    std::cout << "Mobilnummer: " << mobilNummer << std::endl;
    std::cout << "Mailadresse: " << mailAdresse << std::endl;
    std::cout << "Poststed: " << postSted << std::endl;
    std::cout << "Postnummer: " << postNummer << std::endl;
    std::cout << "Antall ting kjøpt: " << antallTingKjøpt << std::endl;
    std::cout << "Antall ting solgt: " << antallTingSolgt << std::endl;
    std::cout << "Antall til salgs: " << antallTilSalgs << std::endl;
};