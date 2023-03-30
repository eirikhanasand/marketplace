/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      nyTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "nyTing.hpp"
#include "lesData3.hpp"
#include "kunder.hpp"
#include "kategorier.hpp"
#include "kategori.hpp"
#include "bruktTing.hpp"

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
    selgernummer = lesInt("Kundenummer", 0, gKundebase.antallKunder());
    navn = lesString("Navn på tingen");
    beskrivelse = lesString("Beskriv tingen");
    pris = lesInt("Hvor mye koster tingen", 0, INT32_MAX);
    antall = lesInt("Hvor mange selger du", 0, INT32_MAX);
}

void NyTing::skrivData() const {
    std::cout << "Selger " << selgernummer << "\tTing: " << nummer << "\tNavn: " << navn << "\tAntall: " << antall << "\tPris: " << pris << "\tBeskrivelse: " << beskrivelse << std::endl;
}

std::string NyTing::hentNavn() const {
    return navn;
}

int NyTing::hentAntall() {
    return antall;
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

int NyTing::hentKundenummer() const {
    return nummer;
}

void NyTing::endreTing() {
    std::cout << "Hva vil du endre på?" << '\n'
        << "1. Navn" << '\n'
        << "2. Antall" << '\n'
        << "3. Pris" << '\n'
        << "4. Beskrivelse" << '\n'
        << "5. Avbryt" << '\n';

    int valg = lesInt("Valg: ", 1, 5);

    switch (valg) {
        case '1': {
            std::string navn = lesString("Nytt navn: ");
            NyTing::endreNavn(navn);
            break;
        }
        case '2': {
            int antall = lesInt("Nytt antall: ", 0, INT32_MAX);
            NyTing::endreAntall(antall);
            break;
        }
        case '3': {
            int pris = lesInt("Ny pris: ", 0, INT32_MAX);
            NyTing::endrePris(pris);
            break;
        }
        case '4': {
            std::string beskrivelse = lesString("Ny beskrivelse: ");
            NyTing::endreBeskrivelse(0);
            break;
        }
        case '5': {
            break;
        }
    }
}

NyTing::NyTing(std::ifstream &tingFil) {
    settData(tingFil);
} 

void NyTing::skrivTilFil(std::ofstream &tingFil) {
    tingFil << selgernummer << nummer << ' ' << pris << ' ' << antall << '\n' << navn << '\n' << beskrivelse << '\n';
}

void NyTing::settData(std::ifstream &tingFil) {
    tingFil >> selgernummer;
    tingFil.ignore();
    tingFil >> nummer;
    tingFil.ignore();
    tingFil >> pris;
    tingFil.ignore();
    tingFil >> antall;
    tingFil.ignore();
}

void NyTing::settRestData(std::ifstream &tingFil) {
    std::getline(tingFil, navn);
    navn[navn.length()] = '\0';

    std::getline(tingFil, beskrivelse);
    beskrivelse[beskrivelse.length()] = '\0';
}