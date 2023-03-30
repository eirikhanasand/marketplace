/**
 *  Definisjon av funksjoner i Kategori klassen
 *
 *  @file      kategori.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>
#include "algorithm"

#include "Kategori.hpp"
#include "Kategorier.hpp"
#include "LesData3.hpp"
#include "BruktTing.hpp"



Kategori::Kategori() {

}

Kategori::~Kategori() {
    //TODO
}

// Input category data
void Kategori::settData() {
    kategoriNavn = KategoriNavn;
    antallTingTilSalgs = 0;
}

// Prints category data
void Kategori::skrivData() const {
    std::cout << "Kategorinavn: " << kategoriNavn << "\tAntall ting til salgs: " << antallTingTilSalgs << std::endl;
}

std::string Kategori::hentNavn() const {
    return kategoriNavn;
}

NyTing* Kategori::finnTing(int kundeNummer) {
    return *std::find_if(tingListe.begin(), tingListe.end(),[kundeNummer](NyTing* ting) {
        return ting->hentKundeNummer() == kundeNummer;
    });
}

void Kategori::lagTing() {
    bool brukt = lesBool("Brukt (j/n)");
    NyTing* ting = nullptr;

    if (brukt) {
        ting = new BruktTing(tingListe.size());
    } else {
        ting = new NyTing(tingListe.size());
    }

    ting->settData();
    tingListe.push_back(ting);
}

int Kategori::hentAntallTing() {
    return tingListe.size();
}

void Kategori::skrivFullKategori() {
    for (const auto &ting: tingListe) {
        ting->skrivData();
    }
}

void Kategori::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kategoriNavn << '\n' << antallTingTilSalgs << '\n';

    for (const auto &ting: tingListe) { 
        ting->skrivTilFil(kundeFil);
    }
}

Kategori::Kategori(std::ifstream &kundeFil) {
    kundeFil >> kategoriNavn;
    kundeFil.ignore();
    kundeFil >> antallTingTilSalgs;
    kundeFil.ignore();

    for (int i = 0; i < antallTingTilSalgs; i++) {
        NyTing *ting = new NyTing(kundeFil);
        tingListe.push_back(ting);
    }
}