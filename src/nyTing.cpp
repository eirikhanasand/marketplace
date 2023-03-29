/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      nyTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include "NyTing.hpp"
#include "LesData3.hpp"
#include "Kunder.hpp"
#include "Kategorier.hpp"
#include "Kategori.hpp"

extern Kunder gKundebase;
extern Kategorier gKategoribase;

// Constructor
NyTing::NyTing(int Nummer) {
    nummer = Nummer;
    settData();
}

// Destructor
NyTing::~NyTing() {

}

void NyTing::settData() {
    navn = lesString("Navn på tingen");
    beskrivelse = lesString("Beskriv tingen");
    pris = lesInt("Hvor mye koster tingen", 0, INT32_MAX);
    antall = lesInt("Hvor mange selger du", 0, INT32_MAX);
}

void NyTing::kjopTing() {
    int ting;
    int kundeNummer = lesInt("Kundenummer:", 0, noe);
    std::string kategoriNavn = lesString("Kategori");

    auto k = finnKategori(kategoriNavn);

    if(k) {
        k->skrivFullKategori();
        ting = lesInt("Skriv inn nummer på tingen du vil kjøpe", 0, k->tingMap.size());
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