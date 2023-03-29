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
    
}

// Destructor
Kunder::~Kunder() {
    for(auto &kunde : kundeListe) {
        kunde->~Kunde();
    }
    std::cout << "Slettet alle kunder." << std::endl;
}

// Håndterer valg
void Kunder::handling() {
    char valg = toupper(lesChar("\nKommando: "));

    while (valg != 'Q') {
        switch (valg) {
            case 'N': {
                lagKunde();
                valg = 0;
                break;
            }
            case 'A': {
                if (kundeListe.size()) {
                    skrivAlle();
                } else {
                    std::cout << "Det finnes ingen kunder å skrive ut." << std::endl;
                }
                valg = 0;
                break;
            }
            case 'S': {
                if (kundeListe.size()) {
                    int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                    Kunde *kunde = finnKunde(kundeNummer);
                    if(kunde) {
                        kunde->skrivData();
                    } else {
                        std::cout << "Det finnes ingen kunde med kundenummer " << kundeNummer << std::endl;
                    }
                    valg = 0;
                } else {
                    std::cout << "Det finnes ingen kunder, kan derfor ikke skrive enkeltkunde." << std::endl;
                }
                break;
            }
            case 'F': {
                if(kundeListe.size()) {
                    int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                    fjernKunde(kundeNummer);
                    valg = 0;
                } else {
                    std::cout << "Det finnes ingen kunder å slette." << std::endl;
                }
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
    }

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
    }

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
        }
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    }
}

// Finds customer
Kunde* Kunder::finnKunde(int kundeNummer) {
    for (auto &kunde: kundeListe) {
        if (kunde->hentKundeNummer() == kundeNummer) {
            return kunde;
        }
    }
    return nullptr;
}

void Kunder::skrivAlle() {
    int i = 0;
    char valg;

    std::cout << "Siste kunde: " << sisteNummer << ". " << "Det finnes nå " 
              << kundeListe.size() << " kunder." << std::endl;
        
    for (const auto &kunde: kundeListe) {
        if (i && i % 20 == 0) {
            valg = lesChar("Skriv ut 20 kunder til? (y/N)");
            if (valg != 'y') break;
        }
        kunde->skrivInfo();
        i++; 
    }
}

int Kunder::antallKunder() {
    return kundeListe.size();
}

void Kunder::lagKunde() {
    Kunde* kunde = new Kunde(kundeListe.size());
    kundeListe.push_back(kunde);
    std::cout << "Opprettet kunde med ";
    kunde->skrivInfo();
}