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

#include "kategori.hpp"
#include "kategorier.hpp"
#include "lesData3.hpp"
#include "bruktTing.hpp"



Kategori::Kategori() {

}

Kategori::~Kategori() {
    //TODO
}

// Input category data
void Kategori::settData() {
    kategoriNavn = lesString("Kategorinavn");
    antallTingTilSalgs = 0;
}

// Prints category data
void Kategori::skrivData() const {
    std::cout << "Kategorinavn: " << kategoriNavn << "\tAntall ting til salgs: " << antallTingTilSalgs << std::endl;
}

std::string Kategori::hentNavn() {
    return kategoriNavn;
}

NyTing* Kategori::hentTing(int kundenummer) {
    auto element = std::find_if(tingListe.begin(), tingListe.end(),[kundenummer](NyTing* ting) {
        return ting->hentKundenummer() == kundenummer;
    });
    return (element != tingListe.end()) ? *element : nullptr;
    /*
    for (const auto &item: tingListe) {
        if (item->hentKundenummer() == kundenummer) {
            return item;
        }
    }
    return nullptr;*/
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
    antallTingTilSalgs++;
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