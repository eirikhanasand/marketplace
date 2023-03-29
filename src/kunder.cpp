/**
 *   todo
 *
 *   @file      kunder.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "Kunder.h"
#include "Kunde.h"
#include "LesData3.h"

// Constructor
Kunder::Kunder() {

}

// Destructor
Kunder::~Kunder() {

}

// Håndterer valg
void Kunder::handling() {
    char valg = toupper(lesChar("\nKommando: "));

    while (valg != 'Q') {
        switch (valg) {
            case 'N':
                // TODO
                break;
            case 'A':
                skrivAlle();
                break;
            case 'S': {
                int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                Kunde *kunde = finnKunde(kundeNummer);
                break;
            }
            case 'F': {
                int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                fjernKunde(kundeNummer);
                break;
            }

            default:
                valg = toupper(lesChar("\nKommando: "));
                break;
        }
    }
}

// Leser fra fil
void Kunder::lesFraFil() {
    std::ifstream kundeFil;
    kundeFil.open("../data/KUNDER.DTA");

    if (kundeFil.is_open()) {
        // les fra kundefil
    } else {
        std::cout << "Kunne ikke lese fra /data/KUNDER.DTA." << std::endl;
    };

    // write here
    kundeFil.close();
}

// Skriver til fil
void Kunder::skrivTilFil() {
    std::ofstream kundeFil;
    kundeFil.open("../data/KUNDER.DTA");

    if (kundeFil.is_open()) {
        // skriv til kundefil
    } else {
        std::cout << "Kunne ikke skrive til /data/KUNDER.DTA." << std::endl;
    };

    // write here
    kundeFil.close();
}

// Deletes customer 
void Kunder::fjernKunde(int kundeNummer) {
    char bekreftelse = lesChar("Er du sikker på at du vil slette kunden? (J/N): ");
    auto kunde = finnKunde(kundeNummer);

    while (bekreftelse != 'J' && bekreftelse != 'N') {
        bekreftelse = lesChar("Feil input, prøv på nytt: ");
    }

    if (kunde) {
        if (bekreftelse == 'J') {
            kunde->skrivData();
            kundeListe.remove(kunde);
            kunde->~Kunde();
        } else {
            std::cout << "Kunde ble ikke slettet." << std::endl;
        };
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    };
}

// Finds customer
Kunde *Kunder::finnKunde(int kundeNummer) {
    for (auto &k: kundeListe) {
        if (k->hentKundeNummer() == kundeNummer) {
            return k;
        };
    };
    return nullptr;
}

void Kunder::skrivAlle() {
    for (const auto &k: kundeListe) {
        // std::cout << "Kundenummer: " << k->hentKundeNummer() << "\tNavn: " << k->navn << "\tTlf: " << k->mobilNummer << std::endl;
        // Usikker om dette er riktig.
        k->skrivData();
    };
}