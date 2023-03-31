/**
 *  Definisjon av funksjoner i Kategori klassen
 *
 *  @file      kategori.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "kategori.hpp"
#include "kategorier.hpp"
#include "lesData3.hpp"
#include "bruktTing.hpp"

/**
 * @brief Constructor for kategori.
 *
 * Denne er tom (default), men er nødvendig for compileren.
*/
Kategori::Kategori() {

}

/**
 * @brief Setter navn og antall ting til salgs for en kategori.
 * 
 * @param navn Navnet på kategorien 
*/
void Kategori::settData(std::string navn) {
    kategoriNavn = navn;
    antallTingTilSalgs = 0;
}

/**
 * @brief Skriver ut navn og antall ting til salgs i en kategori
*/
void Kategori::skrivData() const {
    std::cout << "Kategorinavn: " << kategoriNavn 
              << "\tAntall ting til salgs: " << antallTingTilSalgs << '\n';
}

/**
 * @brief Henter navnet til en kategori
 * 
 * @return std::string kategoriNavn
*/
std::string Kategori::hentNavn() {
    return kategoriNavn;
}

/**
 * @brief Henter ting i kategori som tilhører spesifikt kundenummer.
 *
 * Sjekker listen og finner matchende elementer som returneres, evt nullptr.
 * 
 * @param kundenummer Kundenummeret til kunden
 * 
 * @see NyTing::hentSelgernummer()
 * 
 * @return NyTing peker til funnet ting, evt nullptr
*/
NyTing* Kategori::hentTing(int kundenummer) {
    auto element = std::find_if(tingListe.begin(), tingListe.end(),
    [kundenummer](NyTing* ting) {
        return ting->hentSelgernummer() == kundenummer;
    });
    return (element != tingListe.end()) ? *element : nullptr;
}

/**
 * @brief Oppretter en ny ting i en kategori.
 *
 * Bestemmer ut ifra om den er brukt om den tilhører klassen NyTing eller 
 * BruktTing. Setter deretter data om tingen og legger den bakerst i listen.
 * Øker til slutt antall ting til salgs.
 * 
 * @see lesBool(...)
 * @see BruktTing(...)
 * @see NyTing(...)
 * @see NyTing::settData()
*/
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

/**
 * @brief Henter antall ting i en kategori
 * 
 * @return int Antall ting i kategorien
*/
int Kategori::hentAntallTing() {
    return tingListe.size();
}

/**
 * @brief Skriver all informasjon om alle ting i en gitt kategori.
 * 
 * @see NyTing::skrivData()
*/
void Kategori::skrivTing() {
    for (const auto &ting: tingListe) {
        ting->skrivData();
    }
}

/**
 * @brief Skriver en kategori og alle dens ting til fil.
 * 
 * @param kundeFil Fil som skal skrives til
 * 
 * @see NyTing::skrivTilFIl(...)
*/
void Kategori::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kategoriNavn << '\n' << antallTingTilSalgs << '\n';

    for (const auto &ting: tingListe) { 
        ting->skrivTilFil(kundeFil);
    }
}

/**
 * @brief Kategori constructor med filparameter for å lage kategorier fra fil
 * 
 * @param innfil Filen som skal leses inn fra
 * 
 * @see NyTing::NyTing(...)
 * @see BruktTing::BruktTing(...)
 * @see NyTing::settRestData(...)
*/
Kategori::Kategori(std::ifstream &innfil) {
    int type;

    std::getline(innfil, kategoriNavn);
    kategoriNavn[kategoriNavn.length()] = '\0';

    innfil >> antallTingTilSalgs;
    innfil.ignore();

    for (int i = 0; i < antallTingTilSalgs; i++) {
        type = 0;
        innfil >> type;
        innfil.ignore();

        if (type) {
            BruktTing *bruktTing = new BruktTing(innfil);
            tingListe.push_back(bruktTing);
        } else {
            NyTing *nyTing = new NyTing(innfil);
            nyTing->settRestData(innfil);
            tingListe.push_back(nyTing);
        }
    }
}