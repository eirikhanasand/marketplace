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

void NyTing::skrivData() const {
    std::cout << "Ting: " << nummer << "\tNavn: " << navn << "\tAntall: " << antall << "\tPris: " << pris << "\tBeskrivelse: " << beskrivelse << std::endl;
}

std::string NyTing::hentNavn() const {
    return navn;
}

void NyTing::endreAntall(int nyttAntall) {
    antall = nyttAntall;
}

void NyTing::endreNavn(std::string nyttNavn) {
    navn = nyttNavn;
}

void NyTing::endrePris(int nyPris) {
    pris = nyPris;
}

void NyTing::endreBeskrivelse(std::string nyBeskrivelse) {
    beskrivelse = nyBeskrivelse;
}

void NyTing::endreTing() {
    cout << "Hva vil du endre på?" << endl;
    cout << "1. Navn" << endl;
    cout << "2. Antall" << endl;    
    cout << "3. Pris" << endl;
    cout << "4. Beskrivelse" << endl;
    cout << "5. Avbryt" << endl;
    char valg = lesChar("Valg: ", "12345");

    switch (valg) {
        case '1': {
            NyTing::endreNavn(std::string nyttNavn);
            break;
        }
        case '2': {
            NyTing::endreAntall(int nyttAntall);
            break;
        }
        case '3': {
            NyTing::endrePris(int nyPris);
            break;
        }
        case '4': {
            NyTing::endreBeskrivelse(std::string nyBeskrivelse);
            break;
        }
        case '5': {
            break;
        }
         default: {
            std::cout << "Det er ikke en gyldig kommando!" << std::endl;
            break;
        }
    }
}