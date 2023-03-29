/**
 *   todo
 *
 *   @file      kunde.cpp
 *   @authors   todo
 */

#include <iostream>
#include "NyTing.h"
#include "LesData3.h"
#include "Kunder.h"
#include "Kategorier.h"
#include "Kategori.h"

extern Kunder gKundebase;

// Constructor
NyTing::NyTing() {
    settData();
}

// Destructor
NyTing::~NyTing() {

}

void NyTing::settData(int Nummer) {
    nummer = Nummer;
    navn = lesString("Navn på tingen");
    beskrivelse = lesString("Beskriv tingen");
    pris = lesInt("Hvor mye koster tingen", 0, INT32_MAX);
    antall = lesInt("Hvor mange selger du", 0, INT32_MAX);
}

void NyTing::kjopTing() {
    int ting;
    int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.kundeListe.size());
    std::string kategoriNavn = lesString("Kategori");

    auto k = finnKategori(kategoriNavn);

    if(k) {
        k->skrivFullKategori();
        ting = lesInt("Skriv inn nummer på tingen du vil kjøpe", 0, tingMap.size());
        /**
         * Ifm. kjøpet må alt følgende skje: Kjøperens antall kjøp telles opp med en. 
         * Selgerens antall salg telles opp med en. Antall av tingen telles ned med en, 
         * evt. at den slettes helt fra datastrukturen om dette er den siste/eneste. 
         * I så fall telles også antallet av det selgeren har til salgs ned med en også.
        */
    } else {
        std::cout << "Denne kategorien finnes ikke!" << std::endl;
    }
}