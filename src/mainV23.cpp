/**
 *  Hovedprogrammet for OOP-prosjektet V23 med et Miniatyr-Finn<dot>no
 *  med salg av "Leker og Spill".
 *
 *  @file     mainV23.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>

#include "SkrivMeny.hpp"
#include "Kategorier.hpp"
#include "LesData3.hpp"
#include "Kunder.hpp"
#include "Kunde.hpp"

Kunder gKundebase;    // Globalt container-objekt med ALLE kundene.
Kategorier gKategoribase; // Globalt container-objekt med ALLE kategoriene.

//  Kode som legges innledningsvis i de .cpp-filene som trenger å bruke
//  en eller begge det to globale objektene definert ovenfor:
//  extern Kunder     gKundebase;
//  extern Kategorier gKategoribase;

/**
 *  Hovedprogram.
 */
int main() {
    std::string valg;

    gKundebase.lesFraFil();
    gKategoribase.lesFraFil();

    skrivMeny();

    valg = lesString("\nKommando");

    char forsteValg = valg.at(0);
    char andreValg = valg.at(1);

    while (forsteValg != 'Q') {
        switch (forsteValg) {
            case 'U':
                gKundebase.handling(andreValg);
                break;
            case 'A':
            case 'K':
            case 'T':
                gKategoribase.handling(andreValg);
                break;
            default:
                skrivMeny();
                break;
        }

        valg = lesString("\nKommando");
        forsteValg = valg.at(0);
        andreValg = valg.at(1);
    }
    
    gKundebase.skrivTilFil();
    gKategoribase.skrivTilFil();

    std::cout << "\n\n";

    return 0;
}