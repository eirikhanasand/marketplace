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
Kunde::~Kunde() {

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

    antallTingKjøpt = 0;
    antallTingSolgt = 0;
    antallTilSalgs = 0;
};