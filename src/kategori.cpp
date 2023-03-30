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

// 0 1 1 2000 1
// ForsteLego
// Den nyeste legoen som finnes! Helt ny, og enda ikke brukt!! Passer godt til både store og små!
// 1 2 2 10000 1 230 4
// ForsteBruktLego
// Den første legoen som noensinne ble laget! Denne er av ekstrem sjeldenhet, og går derfor til en høy pris.
// 0 2 3 3000 2
// AndreLego
// Denne legoen er fra serie 2 av lego som ble laget helt tilbake i 
// Den første legoen som noensinne ble laget! Denne er av ekstrem sjeldenhet, og går derfor til en høy pris.

Kategori::Kategori(std::ifstream &kundeFil) {
    int type;

    std::getline(kundeFil, kategoriNavn);
    kategoriNavn[kategoriNavn.length()-1] = '\0';

    kundeFil >> antallTingTilSalgs;
    kundeFil.ignore();

    for (int i = 0; i < antallTingTilSalgs; i++) {
        type = 0;
        kundeFil >> type;
        kundeFil.ignore();

        if (type) {
            BruktTing *bruktTing = new BruktTing(kundeFil);
            bruktTing->skrivData();
            tingListe.push_back(bruktTing);
        } else {
            NyTing *nyTing = new NyTing(kundeFil);
            nyTing->skrivData();
            tingListe.push_back(nyTing);
        }
    }
}