/**
 *   todo
 *
 *   @file      kunde.cpp
 *   @authors   todo
 */

#include <iostream>
#include "kunde.h"
#include "kunder.h"
#include "lesData3.h"

extern Kunde gKundebase;

Kunde::Kunde(int KundeNummer) {
    kundeNummer = KundeNummer;
    settData();
};

Kunde::~Kunde(int kundeNummer) {
    
};

void Kunde::skrivKunde() {
    auto kunde = hentKunde();
    if (kunde) {
        skrivData();
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    };
};

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
    std::cout << "Antall ting kjøpt: " << antallTingKjopt << std::endl;
    std::cout << "Antall ting solgt: " << antallTingSolgt << std::endl;
    std::cout << "Antall til salgs: " << antallTilSalgs << std::endl;
};

auto Kunde::hentKunde() {
    int kundeNummer;

    kundeNummer = lesInt("Kundenummer: ", 1, INT32_MAX);

    // todo
    return gKundebase.contains(kundeNummer);
}