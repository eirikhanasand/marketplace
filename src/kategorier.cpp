/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "kategorier.h"
#include "kategori.h"

extern Kategorier gKategoribase;

// Constructor
Kategorier::Kategorier() {

}

// Destructor
Kategorier::~Kategorier(){
    for(auto &k: nyTingMap) {
        delete k.second;
    };
    nyTingMap.clear();
}

// Håndterer valg
void Kategorier::handling(char valg) {
    
}

// Leser fra fil
void Kategorier::lesFraFil() {
    std::ifstream kundeFil;
    kundeFil.open("../data/KATEGORIER.DTA");

    if (kundeFil.is_open()) {
        // les fra kundefil
    } else {
        std::cout << "Kunne ikke lese fra /data/KATEGORIER.DTA." << std::endl;
    };

    kundeFil.close();
}

// Skriver til fil
void Kategorier::skrivTilFil(){
    std::ofstream kundeFil;
    kundeFil.open("../data/KATEGORIER.DTA");

    if (kundeFil.is_open()) {
        // skriv til kundefil
    } else {
        std::cout << "Kunne ikke skrive til /data/KATEGORIER.DTA." << std::endl;
    };

    kundeFil.close();
};

// Oppretter ny kategori
void Kategorier::nyKategori() {
    std::string kategoriNavn = lesString("Kategorinavn");

    if (!kategoriFinnes(kategoriNavn)) {
        Kategori* kategori = new Kategori(kategoriNavn);
        // Kategori nyKategori(kategoriNavn);
        // gKategoribase.push_back(nyKategori);
    } else {
        std::cout << "Kategorien finnes allerede." << std::endl;
    };
};

//Sjekker om kategori finnes med samme navn
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    for (const auto &k: gKategoribase.nyTingMap) {
        if (k.second->hentNavn() == kategoriNavn) {
            return true;
        };
    };
    return false;
}

// Skriver alle kategorier
void Kategorier::skrivAlle() {
    for (const auto &k: gKategoribase.nyTingMap) {
        k.second->skrivData();
    }
}

Kategori* Kategorier::finnKategori(std::string kategoriNavn) {
    Kategori* kategori = nullptr;
    for (const auto &k: gKategoribase.nyTingMap) {
        if (!k.second->hentNavn().compare(0, kategoriNavn.size(), kategoriNavn)) {
            kategori = dynamic_cast <Kategori*> (k.second);
        };
    };
    return kategori;
}