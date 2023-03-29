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
#include "BruktTing.hpp"



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

NyTing* Kategori::finnTing(int kundeNummer) {
    for (const auto &item: tingListe) {
        if (item->hentKundeNummer() == kundeNummer) {
            return item;
        }
    }
    return nullptr;
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
    // Skriv alle data om alle ting i denne kategorien utenom selgerens nummer, 
    // om den er NY eller BRUKT og tingens unike nummer fra 1 og oppover
}