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