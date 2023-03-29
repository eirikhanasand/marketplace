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
    char valg;

    gKundebase.lesFraFil();
    gKategoribase.lesFraFil();

    skrivMeny();

    valg = lesChar("\nKommando");

    while (valg != 'Q') {
        switch (valg) {
            case 'U':
                gKundebase.handling();
                break;
            case 'A':
            case 'K':
            case 'T':
                gKategoribase.handling(valg);
                break;
            default:
                skrivMeny();
                break;

        };
        valg = lesChar("\nKommando");
    }
    
    gKundebase.skrivTilFil();
    gKategoribase.skrivTilFil();

    std::cout << "\n\n";

    return 0;
}