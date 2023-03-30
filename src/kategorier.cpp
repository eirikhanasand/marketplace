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
#include "vector"
#include "algorithm"

#include "kunder.hpp"
#include "kategorier.hpp"
#include "kategori.hpp"
#include "lesData3.hpp"

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

void Kategorier::tingHandling(char valg) {
    if (valg == 'N') {
        lagTingIKategori();
    } else if (valg == 'E') {
        endreTingIKategori();
    } else {
        std::cout << "Ugyldig kommando!\n";
    }
}


// Håndterer valg
void Kategorier::kategoriHandling(char valg) {
    switch (valg) {
        case 'N':
            lagKategori();
            break;
        case 'A':
            skrivAlle();
            break;
        case 'S': {
            std::string kategoriNavn = lesString("Kategori");
            auto kategori = hentKategoriEntydig(kategoriNavn);

            if (kategori) {
                kategori->skrivData();
            } else {
                std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
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
    std::ifstream kategoriFil("data/KATEGORIER.DTA");

    if (kategoriFil) {
        std::cout << "Leser fra filen KATEGORIER.DTA" << std::endl;

        while(!kategoriFil.eof()) {
            Kategori *kategori = new Kategori(kategoriFil);
            kategoriMap.insert(std::pair<std::string, Kategori *>(kategori->hentNavn(), kategori));
        }

        std::cout << "Leste inn " << kategoriMap.size() << " kategorier fra KATEGORIER.DTA" << std::endl;
    } else {
        std::cout << "Kunne ikke lese fra /data/KATEGORIER.DTA." << std::endl;
    }

    kategoriFil.close();
}

// Oppretter ny kategori
void Kategorier::lagKategori() {
    std::string kategoriNavn = lesString("Kategorinavn");

    if (!kategoriFinnes(kategoriNavn)) {
        Kategori *kategori = new Kategori();
        kategori->settData(kategoriNavn);
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

Kategori *Kategorier::hentKategoriEntydig(std::string kategoriNavn) {
   Kategori* element = nullptr;

    if (!kategoriMap.count(kategoriNavn)) {
        std::vector<std::string> funn;

        std::string liteNavn = stringTilLiten(kategoriNavn);

        for (auto iterator = kategoriMap.begin();
                iterator != kategoriMap.end();
                iterator++)
        {
            std::string liteFunn = stringTilLiten(iterator->first);

            if (liteFunn.find(liteNavn) != std::string::npos) {
                funn.push_back(iterator->first);
            }
        }

        if (funn.size()) {
            for (int i = 1; i <= funn.size(); i++) {
                std::cout << '[' << i << ']' << " " << funn.at(i-1) << '\n';
            }
            int valg = lesInt("Velg kategori:", 1, funn.size());

            element = kategoriMap.find(funn.at(valg-1))->second;
        }
    } else {
        element = kategoriMap.find(kategoriNavn)->second;
    }
    return element;
}

void Kategorier::lagTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->lagTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    }
}

void Kategorier::endreTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivData();
        int tingNummer = lesInt("Hvilken ting vil du endre?", 1, kategori->hentAntallTing());
        kategori->hentTing(tingNummer)->endreTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " << kategoriNavn << std::endl;
    }
}

void Kategorier::kjopTing() {
    int tingnummer;
    int kundenummer = lesInt("Kundenummer:", 0, gKundebase.antallKunder());
    std::string kategoriNavn = lesString("Kategori");

    auto kategori = hentKategoriEntydig(kategoriNavn);

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