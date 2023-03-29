/**
 *  Definisjon av funksjoner i Kunder klassen
 *
 *  @file      kunder.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include "Kunder.hpp"
#include "Kunde.hpp"
#include "LesData3.hpp"

// Constructor
Kunder::Kunder() {
    Kunde* kunde = new Kunde(kundeListe.size());
    kundeListe.push_back(kunde);
    std::cout << "Opprettet kunde med " << kunde->skrivInfo();
} 

// Destructor
Kunder::~Kunder() {
    for(auto &k : kundeListe) {
        k->~Kunde();
    }
    std::cout << "Slettet alle kunder." << std::endl;
}

// Håndterer valg
void Kunder::handling() {
    char valg = toupper(lesChar("\nKommando: "));

    while (valg != 'Q') {
        switch (valg) {
            case 'N': {
                Kunder();
                break;
            }
            case 'A': {
                skrivAlle();
                break;
            }
            case 'S': {
                int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                Kunde *kunde = finnKunde(kundeNummer);
                if(kunde) {
                    kunde->skrivData();
                } else {
                    std::cout << "Det finnes ingen kunde med kundenummer " << kundeNummer << std::endl;
                };
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
    char bekreftelse = lesChar("Er du sikker på at du vil slette kunden? (j/N)");
    auto kunde = finnKunde(kundeNummer);

    if (kunde) {
        if (bekreftelse == 'j') {
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
Kunde* Kunder::finnKunde(int kundeNummer) {
    for (auto &k: kundeListe) {
        if (k->hentKundeNummer() == kundeNummer) {
            return k;
        };
    };
    return nullptr;
}

void Kunder::skrivAlle() {
    int i = 0;
    char valg;

    std::cout << "Siste kunde: " << sisteNummer << ". " << "Det finnes nå " 
              << kundeListe.size() << " kunder." << std::endl;
        
    for (const auto &k: kundeListe) {
        if (i && i % 20 == 0) {
            valg = lesChar("Skriv ut 20 kunder til? (y/N)");
            if (valg != 'y') break;
        }
        k->skrivInfo();
        i++; 
    };
}

int Kunder::antallKunder() {
    return kundeListe.size();
}