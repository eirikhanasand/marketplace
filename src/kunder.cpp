/**
 *   todo
 *
 *   @file      kunder.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "kunder.h"
#include "kunde.h"
#include "lesData3.h"

extern Kunder gKundebase;

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
                int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.kundeListe.size());
                Kunde* kunde = finnKunde(kundeNummer);
                break;
            }
            case 'F':
                // TODO
                break;
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
void Kunder::skrivTilFil(){
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
void Kunder::slettKunde() { 
    char bekreftelse = lesChar("Er du sikker på at du vil slette kunden? (J/N): ");
    int kundeNummer = lesInt("Kundenummer: ",0,gKundebase.kundeListe.size());
    auto kunde = finnKunde(kundeNummer);
    
    if (kunde) {
        if (bekreftelse == 'J'){
            kunde->skrivData();
            kunde->~Kunde();
        } else {
            std::cout << "Kunde ble ikke slettet." << std::endl;
        };
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    };
}

// Finds customer
Kunde* Kunder::finnKunde(int kundeNummer) {
    for (auto &k : gKundebase.kundeListe) {
        if (k->kundeNummer == kundeNummer) {
            return k;
        };
    };
    return nullptr;
}

void Kunder::skrivAlle() {
    for (const auto &k: gKundebase.kundeListe) {
        std::cout << "Kundenummer: " << k->kundeNummer << "\tNavn: " << k->navn << "\tTlf: " << k->mobilNummer << std::endl;
    };
}