/**
 *  Definisjon av funksjoner i Kunder klassen
 *
 *  @file      kunder.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include "skrivMeny.hpp"
#include "lesData3.hpp"
#include "kunder.hpp"
#include "kunde.hpp"

/**
 * @brief Kunder sin destructor
 */
Kunder::~Kunder() {
    for (auto &kunde : kundeListe) {
        delete kunde;
    }
}

/**
 * @brief Håndterer valgmuligheter for kunder
 *
 * Valgmuligheter:
 * - Opprettelse av ny kunde
 * - Utskriving av alle kunder
 * - Utskriving av spesifikk kunde
 * - Sletting av kunde
 * 
 * @param valg Bokstav som indikerer brukerens valg
 * 
 * @see lagKunde()
 * @see skrivAlle()
 * @see lesInt(...)
 * @see hentKunde(...)
 * @see Kunde::skrivData(...)
 * @see fjernKunde(...)
 * @see skrivMeny()
*/
void Kunder::handling(char valg) {
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
                std::cout << "Det finnes ingen kunder å skrive ut.\n";
            }
            valg = 0;
            break;
        }
        case 'S': {
            if (kundeListe.size()) {
                if (sisteKundenummer) {
                    int kundenummer =
                        lesInt("Kundenummer", 1, sisteKundenummer)-1;
                    Kunde *kunde = hentKunde(kundenummer);
                    if (kunde) {
                        kunde->skrivData();
                    } else {
                        std::cout << "Kunde nummer " << kundenummer+1
                                << " har blitt slettet.\n";
                    }
                } else {
                    std::cout << "Det finnes ingen kunder, kan derfor ikke "
                    "skrive enkeltkunde.\n";
                }
                valg = 0;
            } else {
                std::cout << "Det finnes ingen kunder å skrive ut.\n";
            }
            break;
        }
        case 'F': {
            if (kundeListe.size()) {
                if (sisteKundenummer) {
                    int kundenummer =
                            lesInt("Kundenummer:", 1, sisteKundenummer)-1;

                    if (hentKunde(kundenummer)) {
                        fjernKunde(kundenummer);
                    } else {
                        std::cout << "Kunde nummer " << kundenummer+1
                                << " har blitt slettet.\n";
                    }
                } else {
                    std::cout << "Det finnes ingen kunder å slette.\n";
                }
                valg = 0;
            } else {
                std::cout << "Det finnes ingen kunder å slette.\n";
            }
            break;
        }
        default: {
            std::cout << "Ugyldig kommando!\n";
            skrivMeny();
            break;
        }
    }
}

/**
 * @brief Leser kunder fra fil.
 *
 * Deretter oppretter disse som objekter, og legger de bakerst i kundelisten.
 * 
 * @see Kunde::Kunde(...)
*/
void Kunder::lesFraFil() {
    int kundenummer = 0;
    std::ifstream kundeFil("data/KUNDER.DTA");

    if (kundeFil) {
        std::cout << "Leser fra filen KUNDER.DTA\n";

        while (!kundeFil.eof()) {
            kundenummer = 0;
            kundeFil >> kundenummer;
            if (kundenummer) {
                kundeFil.ignore();
                kundeListe.push_back(new Kunde(kundeFil, kundenummer-1));
                sisteKundenummer++;   
            }
        }

        std::cout << "Leste inn " << sisteKundenummer << " kunder fra "
                     "KUNDER.DTA\n";
    } else {
        std::cout << "Kunne ikke lese fra /data/KUNDER.DTA.\n";
    }

    kundeFil.close();
}

/**
 * @brief Skriver alle kunder til fil.
 * 
 * @see Kunde::skrivTilFil(...)
*/
void Kunder::skrivAlleTilFil() {
    std::ofstream kundeFil("data/KUNDER.DTA");

    if (kundeFil) {
        std::cout << "Skriver til filen KUNDER.DTA\n";

        for (const auto &kunde : kundeListe) {
            kunde->skrivTilFil(kundeFil);
        }
    } else {
        std::cout << "Kunne ikke skrive til /data/KUNDER.DTA.\n";
    }

    kundeFil.close();
}

/**
 * @brief Sletter kunde
 * 
 * Basert på kundenummer. All informasjon om kunden skrives ut, og brukeren må 
 * deretter bekrefte at de ønsker å gjennomføre slettingen.
 * 
 * @param kundenummer Nummeret på kunden man ønsker å slette
 * 
 * @see Kunder::hentKunde(...)
 * @see Kunde::skrivData()
 * @see lesChar(...)
 * @see Kunde::~Kunde()
*/
void Kunder::fjernKunde(int kundenummer) {
    char bekreftelse;
    auto kunde = hentKunde(kundenummer);

    if (kunde) {
        kunde->skrivData();
        bekreftelse = lesChar("Er du sikker på at du vil slette kunden? (j/N)");
        if (bekreftelse == 'J') {
            kundeListe.remove(kunde);
            kunde->~Kunde();
            std::cout << "Kunden ble slettet.\n";
        } else {
            std::cout << "Kunde ble ikke slettet.\n";
        }
    } else {
        std::cout << "Kunde finnes ikke.\n";
    }
}

/**
 * Henter kunde tilhørende gitt kundenummer.
 * 
 * @param kundenummer Kundenummeret på kunden man ønsker å hente
 * 
 * @see hentKundenummer()
 * 
 * @return Kunde peker, evt nullptr om kunden ikke ble funnet.
*/
Kunde *Kunder::hentKunde(int kundenummer) {
    auto element = std::find_if(kundeListe.begin(), kundeListe.end(),
        [kundenummer](Kunde *kunde){
        return kunde->hentKundenummer() == kundenummer;
    });
    return (element != kundeListe.end()) ? *element : nullptr;
}

/**
 * @brief Skriver alle kunder.
 *
 * Bruker må bekrefte at de vil skrive ut flere for hver 20. kunde.
 * 
 * @see Kunde::skrivInfo()
 * @see lesBool(...)
*/
void Kunder::skrivAlle() {
    int i = 0;
    bool valg;

    std::cout << "Siste kunde: " << sisteKundenummer << ". Det finnes nå "
              << kundeListe.size() << " kunder.\n";

    for (const auto &kunde : kundeListe) {
        if (i && i % 20 == 0) {
            valg = lesBool("Skriv ut 20 kunder til? j/N");
            if (!valg) break;
        }
        kunde->skrivInfo();
        i++;
    }
}

/**
 * @brief Returnerer antall kunder som finnes for øyeblikket
 * 
 * @return int Antall kunder
*/
int Kunder::sisteKunde() {
    return sisteKundenummer;
}

/**
 * @brief Oppretter en ny kunde.
 *
 * Deretter setter alle dens datamedlemmer,
 * og legger den inn i kundelisten. 
 * 
 * @see Kunde::Kunde(...)
 * @see Kunde::skrivInfo()
*/
void Kunder::lagKunde() {
    Kunde *kunde = new Kunde(sisteKundenummer);
    kundeListe.push_back(kunde);
    std::cout << "Opprettet kunde med ";
    kunde->skrivInfo();
    sisteKundenummer++;
}

/**
 * @brief Henter antall kunder som faktisk finnes
 * 
 * @return int Antall kunder
*/
int Kunder::hentAntallKunder() {
    return kundeListe.size();
}
