/**
 *   todo
 *
 *   @file      kunde.cpp
 *   @authors   todo
 */

#include <iostream>
#include "Kunde.h"
#include "Kunder.h"

extern Kunder gKundebase;

// Constructor
Kunde::Kunde(int KundeNummer, std::string Navn) {
    kundeNummer = KundeNummer;
    navn = Navn;
    settData();
};

// Destructor
Kunde::~Kunde() {

};

void Kunde::settData() {
    std::cout << "Gateadresse: " << std::endl;
    std::getline(std::cin, gateAdresse);

    std::cout << "Mobilnummer: " << std::endl;
    std::getline(std::cin, mobilNummer);

    std::cout << "Mailadresse: " << std::endl;
    std::getline(std::cin, mailAdresse);

    std::cout << "Poststed: " << std::endl;
    std::getline(std::cin, postSted);

    std::cout << "Postnummer: " << std::endl;
    std::getline(std::cin, postNummer);
}