/**
 *  Hovedprogrammet for OOP-prosjektet V23 med et Miniatyr-Finn<dot>no
 *  med salg av "Leker og Spill".
 *
 *  @file     mainV23.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <string>

#include "kategorier.hpp"
#include "skrivMeny.hpp"
#include "lesData3.hpp"
#include "kunder.hpp"
#include "kunde.hpp"

Kunder gKundebase;          // Globalt container-objekt med ALLE kundene.
Kategorier gKategoribase;   // Globalt container-objekt med ALLE kategoriene.

/**
 * @brief Programmets hovedmeny
 * 
 * Her skrives alle overordnede valgmuligheter ut, kunder og kategorier leses
 * fra og til fil, og valg leses inn.
 * 
 * @see Kategorier::kategoriHandling(...)
 * @see Kategorier::kjopTing(...)
 * @see Kategorier::lesFraFil()
 * @see Kategorier::skrivAlleTilFil()
 * @see Kategorier::tingHandling(...)
 * @see Kunder::handling(...)
 * @see Kunder::lesFraFil()
 * @see Kunder::skrivAlleTilFil()
 * @see lesString(...)
 * @see skrivMeny()
 * 
 * @return 0, programmet avsluttes
 */
int main() {
    std::string valg;

    gKundebase.lesFraFil();
    gKategoribase.lesFraFil();

    skrivMeny();
    
    valg = lesString("\nKommando");

    char forsteValg = std::toupper(valg.at(0));

    if (valg.size() == 1 && (forsteValg != 'K' && forsteValg != 'Q')) {
        skrivMeny();
        valg = lesString("\nUgyldig Kommando");
    }

    forsteValg = std::toupper(valg.at(0));
    char andreValg;

    while (forsteValg != 'Q') {
        switch (forsteValg) {
            case 'U':
                andreValg = std::toupper(valg.at(1));
                gKundebase.handling(andreValg);
                break;
            case 'A':
                andreValg = std::toupper(valg.at(1));
                gKategoribase.kategoriHandling(andreValg);
                break;
            case 'K':
                gKategoribase.kjopTing();
                break;
            case 'T':
                andreValg = std::toupper(valg.at(1));
                gKategoribase.tingHandling(andreValg);
                break;
            default:
                skrivMeny();
                break;
        }

        valg = lesString("\nKommando");
        forsteValg = std::toupper(valg.at(0));

        if (valg.size() == 1 && (forsteValg != 'K' || forsteValg != 'Q')) {
            skrivMeny();
            valg = lesString("\nUgyldig Kommando");
        }
        forsteValg = std::toupper(valg.at(0));
    }
    
    gKundebase.skrivAlleTilFil();
    gKategoribase.skrivAlleTilFil();

   std::cout << "All data er lagret, og programmet er avsluttet.\n";

    return 0;
}