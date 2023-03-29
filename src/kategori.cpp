/**
 *  Definisjon av funksjoner i Kategori klassen
 *
 *  @file      kategori.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Kategori.hpp"
#include "Kategorier.hpp"
#include "LesData3.hpp"



Kategori::Kategori(std::string KategoriNavn) {
    kategoriNavn = KategoriNavn;
    settData();
}

Kategori::~Kategori() {
    //TODO
}

// Input category data
void Kategori::settData() {
    antallTingTilSalgs = 0;
}

// Prints category data
void Kategori::skrivData() const {
    std::cout << "Kategorinavn: " << kategoriNavn << "\tAntall ting til salgs: " << antallTingTilSalgs << std::endl;
}

std::string Kategori::hentNavn() const {
    return kategoriNavn;
}

void Kategori::lagTing() {
    auto *ting = new NyTing(tingListe.size());
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
    // Skriv alle data om alle ting i denne kategorien utenom selgerens nummer, 
    // om den er NY eller BRUKT og tingens unike nummer fra 1 og oppover
}

void Kategori::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil >> kategoriNavn >> '\n' >> antallTingTilSalgs '\n';

    for (const auto &ting: tingListe) {
        ting->skrivTilFil();
    }
}

Kategori::Kategori(std::ifstream &kundeFil) {
    kundeFil >> kategoriNavn;
    kundeFil.ignore();
    kundeFil >> antallTingTilSalgs;
    kundeFil.ginore();

    for (int i = 0; i < antallTingTilSalgs; i++) {
        NyTing ting = new NyTing(kundeFil);
        tingListe.push_back(ting);
    }
}