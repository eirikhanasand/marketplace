/**
 *  Hovedprogrammet for OOP-prosjektet V23 med et Miniatyr-Finn<dot>no
 *  med salg av "Leker og Spill".
 *
 *  @file     mainV23.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <string>

#include "skrivMeny.hpp"
#include "kategorier.hpp"
#include "lesData3.hpp"
#include "kunder.hpp"
#include "kunde.hpp"

Kunder gKundebase;          // Globalt container-objekt med ALLE kundene.
Kategorier gKategoribase;   // Globalt container-objekt med ALLE kategoriene.

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
                gKategoribase.kategoriHandling(andreValg);
                break;
            case 'K':
                gKategoribase.kjopTing();
                break;
            case 'T':
                gKategoribase.tingHandling(andreValg);
                break;
            default:
                skrivMeny();
                break;
        }

        valg = lesString("\nKommando");
        forsteValg = valg.at(0);
        andreValg = valg.at(1);
    }
    
    gKundebase.skrivAlleTilFil();
    gKategoribase.skrivAlleTilFil();

   std::cout << "All data er lagret, og programmet er avsluttet." << std::endl;

    return 0;
}