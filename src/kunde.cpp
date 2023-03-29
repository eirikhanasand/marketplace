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

Kunde::Kunde(int KundeNummer) {
    kundeNummer = KundeNummer;
    settData();
}

Kunde::~Kunde() {
    //
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

void Kunde::skrivKunde() {
    /*auto kunde = finnKunde();
    if (kunde) {
        kunde->skrivData();
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    };*/ // TODO
}

void Kunde::skrivData() {
    std::cout << "Navn: " << navn << std::endl;
    std::cout << "Gateadresse: " << gateAdresse << std::endl;
    std::cout << "Mobilnummer: " << mobilNummer << std::endl;
    std::cout << "Mailadresse: " << mailAdresse << std::endl;
    std::cout << "Poststed: " << postSted << std::endl;
    std::cout << "Postnummer: " << postNummer << std::endl;
    std::cout << "Antall ting kjøpt: " << antallTingKjopt << std::endl;
    std::cout << "Antall ting solgt: " << antallTingSolgt << std::endl;
    std::cout << "Antall til salgs: " << antallTingTilSalgs << std::endl;
}