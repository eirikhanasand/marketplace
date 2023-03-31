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
    for (auto &kunde: kundeListe) {
        delete kunde;
    }
    std::cout << "Slettet alle kunder." << std::endl;
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
 * @see Kunder::lagKunde()
 * @see Kunder::skrivAlle()
 * @see lesInt(...)
 * @see Kunder::hentKunde(...)
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
                std::cout << "Det finnes ingen kunder å skrive ut." << std::endl;
            }
            valg = 0;
            break;
        }
        case 'S': {
            if (kundeListe.size()) {
                int kundenummer = lesInt("Kundenummer", 1, kundeListe.size());
                Kunde *kunde = hentKunde(kundenummer);
                if (kunde) {
                    kunde->skrivData();
                } else {
                    std::cout << "Det finnes ingen kunde med kundenummer " << kundenummer << std::endl;
                }
            } else {
                std::cout << "Det finnes ingen kunder, kan derfor ikke skrive enkeltkunde." << std::endl;
            }
            valg = 0;
            break;
        }
        case 'F': {
            if (kundeListe.size()) {
                int kundenummer = lesInt("Kundenummer:", 1, kundeListe.size());
                fjernKunde(kundenummer);
            } else {
                std::cout << "Det finnes ingen kunder å slette." << std::endl;
            }
            valg = 0;
            break;
        }
        default:
            std::cout << "Ugyldig kommando!\n";
            skrivMeny();
            break;
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
    std::ifstream kundeFil("data/KUNDER.DTA");

    if (kundeFil) {
        std::cout << "Leser fra filen KUNDER.DTA" << std::endl;

        while(!kundeFil.eof()) {
            kundeListe.push_back(new Kunde(kundeFil));
        }

        std::cout << "Leste inn " << kundeListe.size() << " kunder fra KUNDER.DTA" << std::endl;
    } else {
        std::cout << "Kunne ikke lese fra /data/KUNDER.DTA." << std::endl;
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
        std::cout << "Skriver til filen KUNDER.DTA" << std::endl;

        for(const auto &kunde: kundeListe) {
            kunde->skrivTilFil(kundeFil);
        }
    } else {
        std::cout << "Kunne ikke skrive til /data/KUNDER.DTA." << std::endl;
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
            std::cout << "Kunden ble slettet." << std::endl;
        } else {
            std::cout << "Kunde ble ikke slettet." << std::endl;
        }
    } else {
        std::cout << "Kunde finnes ikke." << std::endl;
    }
}

/**
 * Henter kunde tilhørende gitt kundenummer.
 * 
 * @param kundenummer Kundenummeret på kunden man ønsker å hente
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
 * @see Kunde#skrivInfo()
 * @see lesBool(...)
*/
void Kunder::skrivAlle() {
    int i = 0;
    bool valg;

    std::cout << "Siste kunde: " << sistenummer << ". " << "Det finnes nå "
              << kundeListe.size() << " kunder." << std::endl;

    for (const auto &kunde: kundeListe) {
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
int Kunder::antallKunder() {
    return kundeListe.size();
}

/**
 * @brief Oppretter en ny kunde.
 *
 * Deretter setter alle dens datamedlemmer,
 * og legger den inn i kundelisten. 
 * 
 * @see Kunde#skrivInfo()
*/
void Kunder::lagKunde() {
    Kunde *kunde = new Kunde(kundeListe.size()+1);
    kundeListe.push_back(kunde);
    std::cout << "Opprettet kunde med ";
    kunde->skrivInfo();
}