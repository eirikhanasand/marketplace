/**
 *  Definisjon av funksjoner i Kategorier klassen
 *
 *  @file      kategorier.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Kategorier.hpp"
#include "Kategori.hpp"
#include "LesData3.hpp"

// Constructor
Kategorier::Kategorier() {
    std::navn = lesString("Kategorinavn");
    if(!kategoriFinnes(navn)) {
         Kategori* kategori = new Kategori(navn);
         
    } else {
        std::cout << "Beklager, det finnes allerede en " << navn " kategori!" << std::endl;
    };

    Kunde* kunde = new Kunde(kundeListe.size());
    kundeListe.push_back(kunde);
    std::cout << "Opprettet kunde med " << kunde->skrivInfo();
}

// Destructor
Kategorier::~Kategorier() {
    for (auto &k: kategoriMap) {
        delete k.second;
    };
    kategoriMap.clear();
}

// Håndterer valg
void Kategorier::handling(char valg) {
    while (valg != 'Q') {
        switch (valg) {
            case 'N':
                Kategorier();
                break;
            case 'A':
                skrivAlle();
                break;
            case 'S': {
                int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                Kunde *kunde = finnKunde(kundeNummer);
                if(kunde) {
                    kunde->skrivData();
                } else {
                    std::cout << "Det finnes ingen kunde med kundenummer " << kundeNummer << std::endl;
                };
                break;
            }
            case 'F': {
                int kundeNummer = lesInt("Kundenummer:", 0, kundeListe.size());
                fjernKunde(kundeNummer);
                break;
            }

            default:
                valg = toupper(lesChar("\nKommando: "));
                break;
        }
    }
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
void Kategorier::skrivTilFil() {
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
        Kategori *kategori = new Kategori(kategoriNavn);
        kategoriMap.insert(std::pair<std::string, Kategori *>(kategoriNavn, kategori));
    } else {
        std::cout << "Kategorien finnes allerede." << std::endl;
    };
};

//Sjekker om kategori finnes med samme navn
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    for (const auto &k: kategoriMap) {
        if (k.second->hentNavn() == kategoriNavn) {
            return true;
        };
    };
    return false;
}

void Kategorier::fjernKategori(Kategori *kategori) {
    auto iterator = kategoriMap.find(kategori->hentNavn());
    kategoriMap.erase(iterator);
    delete kategori;
}


// Skriver alle kategorier
void Kategorier::skrivAlle() {
    for (const auto &k: kategoriMap) {
        k.second->skrivData();
    }
}

Kategori* Kategorier::finnKategori(std::string kategoriNavn) {
    Kategori *kategori = nullptr;

    for (const auto &k: kategoriMap) {
        if (!k.second->hentNavn().compare(0, kategoriNavn.size(), kategoriNavn)) {
            kategori = dynamic_cast<Kategori *>(k.second);
        };
    };

    return kategori;
}

void Kategorier::skrivFullKategori() {
    for (const auto &k: kategoriMap) {
        k->skrivData();
        for (const auto &t: NyTing)
        // Skriv alle data om alle ting i denne kategorien utenom selgerens nummer, 
        // om den er NY eller BRUKT og tingens unike nummer fra 1 og oppover
    }
}

void Kategorier::lagTing() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto k = finnKategori(kategoriNavn);
    NyTing* ting = new NyTing();

    if (k) {
        k->NyTing.push_back(ting);
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    };

}