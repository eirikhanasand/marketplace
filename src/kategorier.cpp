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

#include "Kunder.hpp"
#include "Kategorier.hpp"
#include "Kategori.hpp"
#include "LesData3.hpp"

extern Kunder gKundebase;

// Constructor
Kategorier::Kategorier() {

}

// Destructor
Kategorier::~Kategorier() {
    for (auto &kategori: kategoriMap) {
        delete kategori.second;
    }
    kategoriMap.clear();
}

void Kategorier::lagKategorier() {
    std::string navn = lesString("Kategorinavn");

    if(!kategoriFinnes(navn)) {
         Kategori* kategori = new Kategori(navn);
         kategori->settData();
         std::cout << "Opprettet kategori " << navn << std::endl;
    } else {
        std::cout << "Beklager, det finnes allerede en " << navn << " kategori!" << std::endl;
    }
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
                int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
                Kunde *kunde = gKundebase.finnKunde(kundeNummer);
                if(kunde) {
                    kunde->skrivData();
                } else {
                    std::cout << "Det finnes ingen kunde med kundenummer " << kundeNummer << std::endl;
                }
                break;
            }
            case 'F': {
                int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
                gKundebase.fjernKunde(kundeNummer);
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
    }

    kundeFil.close();
}

// Oppretter ny kategori
void Kategorier::nyKategori() {
    std::string kategoriNavn = lesString("Kategorinavn");

    if (!kategoriFinnes(kategoriNavn)) {
        Kategori *kategori = new Kategori(kategoriNavn);
        kategoriMap.insert(std::pair<std::string, Kategori *>(kategoriNavn, kategori));
    } else {
        std::cout << "Kategorien finnes allerede." << std::endl;
    }
}

//Sjekker om kategori finnes med samme navn
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    for (const auto &kategori: kategoriMap) {
        if (kategori.second->hentNavn() == kategoriNavn) {
            return true;
        }
    }
    return false;
}

void Kategorier::fjernKategori(Kategori *kategori) {
    auto iterator = kategoriMap.find(kategori->hentNavn());
    kategoriMap.erase(iterator);
    delete kategori;
}


// Skriver alle kategorier
void Kategorier::skrivAlle() {
    for (const auto &kategori: kategoriMap) {
        kategori.second->skrivData();
    }
}

Kategori* Kategorier::finnKategori(std::string kategoriNavn) {
    for (const auto &kategori: kategoriMap) {
        if (!kategori.second->hentNavn().compare(0, kategoriNavn.size(), kategoriNavn)) {
            return dynamic_cast<Kategori *>(kategori.second);
        }
    }
    return nullptr;
}

void Kategorier::lagTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = finnKategori(kategoriNavn);

    if (kategori) {
        kategori->lagTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    }
}

void Kategorier::kjopTing() {
    int ting;
    int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
    std::string kategoriNavn = lesString("Kategori");

    auto kategori = finnKategori(kategoriNavn);

    if(kategori) {
        kategori->skrivFullKategori(); 
        ting = lesInt("Skriv inn nummer på tingen du vil kjøpe", 0, kategori->hentAntallTing());
        /**
         * Ifm. kjøpet må alt følgende skje: Kjøperens antall kjøp telles opp med en. 
         * Selgerens antall salg telles opp med en. Antall av tingen telles ned med en, 
         * evt. at den slettes helt fra datastrukturen om dette er den siste/eneste. 
         * I så fall telles også antallet av det selgeren har til salgs ned med en også.
        */
    } else {
        std::cout << "Denne kategorien finnes ikke!" << std::endl;
    }
}

// Skriver til fil
void Kategorier::skrivAlleTilFil() {
    std::ofstream kategoriFil("../data/KATEGORIER.DTA");

   if (kategoriFil) {
        std::cout << "Leser til filen KATEGORIER.DTA" << std::endl;

        for(const auto &kategori: kategoriMap) {
            kategori->skrivTilFil(kategoriFil);
        }

        kategoriFil.close();
    } else {
        std::cout << "Kunne ikke lese til /data/KATEGORIER.DTA." << std::endl;
    }

    kategoriFil.close();
}

void Kategorier::lesAlleFraFil() {
    std::ifstream kategoriFil("../data/KATEGORIER.DTA");

    if(kategoriFil) {
        std::cout << "Leser fra filen KUNDER.DTA" << std::endl;

        while(!kategoriFil.eof()) {
            kategoriMap.push_back(new Kategori(innfil));
        }

        kategoriFil.close();
    } else {
        std::cout << "Kunne ikke lese fra fil /data/KATEGORIER.DTA." << std::endl;
    }
}