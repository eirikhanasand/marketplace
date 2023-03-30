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

    if (!kategoriFinnes(navn)) {
        auto *kategori = new Kategori();
        kategori->settData(); 
        std::cout << "Opprettet kategori " << kategori->hentNavn() << std::endl;
    } else {
        std::cout << "Beklager, det finnes allerede en " << navn << " kategori!" << std::endl;
    }
}

void Kategorier::tingHandling(char valg) {
    if (valg == 'N') {
        lagTingIKategori();
    } else if (valg == 'E') {
        // todo
    } else {
        std::cout << "Ugyldig kommando!\n";
    }
}


// Håndterer valg
void Kategorier::kategoriHandling(char valg) {
    switch (valg) {
        case 'N':
            Kategorier();
            break;
        case 'A':
            skrivAlle();
            break;
        case 'S': {
            int kundeNummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
            Kunde *kunde = gKundebase.hentKunde(kundeNummer);
            if (kunde) {
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
            std::cout << "Ugyldig kommando!\n";
            break;
    }

}

// Leser fra fil
void Kategorier::lesFraFil() {
    std::ifstream kundeFil("../data/KATEGORIER.DTA");

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
        Kategori *kategori = new Kategori();
        kategori->settData();
        kategoriMap.insert(std::pair<std::string, Kategori *>(kategoriNavn, kategori));
    } else {
        std::cout << "Kategorien finnes allerede." << std::endl;
    }
}

//Sjekker om kategori finnes med samme navn
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    return kategoriMap.count(kategoriNavn);
}

// Fjerner en kategori
void Kategorier::fjernKategori(Kategori *kategori) {
    auto funn = kategoriMap.find(kategori->hentNavn());
    kategoriMap.erase(funn);
    delete kategori;
}


// Skriver alle kategorier
void Kategorier::skrivAlle() const {
    for (const auto &kategori: kategoriMap) {
        kategori.second->skrivData();
    }
}

Kategori *Kategorier::hentKategori(std::string kategoriNavn) {
    auto element = kategoriMap.find(kategoriNavn);
    return (element != kategoriMap.end()) ? element->second : nullptr;
}

void Kategorier::lagTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategori(kategoriNavn);

    if (kategori) {
        kategori->lagTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    }
}

void Kategorier::endreTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategori(kategoriNavn);

    if (kategori) {
        int kundeNummer = lesInt("Kundenummer: ", 1, kategori->hentAntallTing());
        kategori->hentTing(kundeNummer-1)->endreTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    }
}

void Kategorier::kjopTing() {
    int tingnummer;
    int kundenummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
    std::string kategoriNavn = lesString("Kategori");

    auto kategori = hentKategori(kategoriNavn);

    if (kategori) {
        kategori->skrivFullKategori();
        tingnummer = lesInt("Skriv inn nummer på tingen du vil kjøpe, 0 for å avbryte", 0, kategori->hentAntallTing());

        if (tingnummer) {
            auto ting = kategori->hentTing(tingnummer);
            Kunde *kunde = gKundebase.hentKunde(kundenummer);
            kunde->kjopTing(kategori, ting);
        } else {
            std::cout << "Avbrøt kjøp!" << std::endl;
        }
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
            kategori.second->skrivTilFil(kategoriFil);
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
            Kategori* kategori = new Kategori(kategoriFil);
            kategoriMap.insert(std::pair<std::string, Kategori*>(kategori->hentNavn(), kategori));
        }

        kategoriFil.close();
    } else {
        std::cout << "Kunne ikke lese fra fil /data/KATEGORIER.DTA." << std::endl;
    }
}