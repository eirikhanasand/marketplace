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

extern Kategorier gKategoribase;
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
    sisteTingnummer = 0;
}

/**
 * @brief Skriver ut navn og antall ting til salgs i en kategori
*/
void Kategori::skrivData() const {
    std::cout << "Kategorinavn: " << kategoriNavn
              << "\tAntall ting til salgs: " << tingListe.size() << '\n';
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
 * @brief Henter ting i kategori som tilhører spesifikt tingnummer.
 *
 * Sjekker listen og finner matchende element som returneres, evt nullptr.
 * 
 * @param tingnummer Tingens nummer
 * 
 * @return NyTing peker til funnet ting, evt nullptr
*/
NyTing* Kategori::hentTing(int tingnummer) {
    auto element = std::find_if(tingListe.begin(), tingListe.end(),
        [tingnummer](NyTing *ting){
        return ting->hentNummer() == tingnummer;
    });
    return (element != tingListe.end()) ? *element : nullptr;
}

NyTing* Kategori::hentTingMedIndeks(int indeks) {
    int iteratorIndeks = 1;
    for (const auto &ting : tingListe) {
        if (iteratorIndeks == indeks) {
            return ting;
        }
        iteratorIndeks++;
    }
    return nullptr;
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
 * @see Kategorier::okAntallTing()
 * @see Kategorier::hentAntallTing()
*/
void Kategori::lagTing() {
    bool brukt = lesBool("Brukt (j/n)");
    NyTing* ting = nullptr;

    if (brukt) {
        ting = new BruktTing(gKategoribase.hentAntallTing()+1);
    } else {
        ting = new NyTing(gKategoribase.hentAntallTing()+1);
    }

    ting->settData();
    tingListe.push_back(ting);
    sisteTingnummer++;
    gKategoribase.okAntallTing();
}

/**
 * @brief Henter antall ting i en kategori
 * 
 * @return int Antall ting i kategorien
*/
int Kategori::sisteTing() {
    return sisteTingnummer;
}

/**
 * @brief Skriver all informasjon om alle ting i en gitt kategori.
 * 
 * @see NyTing::skrivData()
*/
void Kategori::skrivTing() const {
    for (const auto &ting : tingListe) {
        ting->skrivData();
    }
}
/**
 * @brief Skriver all informasjon om alle ting i en gitt kategori med indeks.
 *
 * @see NyTing::skrivData()
*/
void Kategori::skrivTingIndeksert() const {
    int indeks = 1;
    for (const auto &ting : tingListe) {
        std::cout << "[" << indeks << "] ";
        ting->skrivData();
        indeks++;
    }
}

/**
 * @brief Skriver alt bortsett fra selgernummer for alle ting i en kategori.
 * 
 * @see NyTing::skrivMindreData()
*/
void Kategori::skrivTingMindre() const {
    for (const auto &ting : tingListe) {
        ting->skrivMindreData();
    }
}

/**
 * @brief Skriver en kategori og alle dens ting til fil.
 * 
 * @param kundeFil Fil som skal skrives til
 * 
 * @see NyTing::skrivTilFIl(...)
 * @see NyTing::skrivRestDataTilFil(...)
*/
void Kategori::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kategoriNavn << '\n' << sisteTingnummer << '\n';

    for (const auto &ting : tingListe) {
        ting->skrivTilFil(kundeFil);
        ting->skrivRestDataTilFil(kundeFil);
    }
}

/**
 * @brief Antallet ting som er i tinglisten.
 *
 * @return antallet ting som er i listen.
 */
int Kategori::antallTing() {
    return tingListe.size();
}


/**
 * @brief Kategori constructor med filparameter for å lage kategorier fra fil
 * 
 * @param innfil Filen som skal leses inn fra
 * @param navn Navnet på kategorien
 * 
 * @see NyTing::NyTing(...)
 * @see BruktTing::BruktTing(...)
 * @see NyTing::settRestData(...)
 * @see NyTing::settBruktStatus(...)
 * @see Kategorier::okAntallTing()
*/
Kategori::Kategori(std::ifstream &innfil, std::string navn) {
    int type;

    kategoriNavn = navn;

    innfil >> sisteTingnummer;
    innfil.ignore();

    for (int i = 0; i < sisteTingnummer; i++) {
        type = 0;
        innfil >> type;
        innfil.ignore();

        if (type) {
            BruktTing *bruktTing = new BruktTing(innfil);
            bruktTing->settBruktStatus(true);
            tingListe.push_back(bruktTing);
            gKategoribase.okAntallTing();
        } else {
            NyTing *nyTing = new NyTing(innfil);
            nyTing->settBruktStatus(false);
            nyTing->settRestData(innfil);
            tingListe.push_back(nyTing);
            gKategoribase.okAntallTing();
        }
    }
}

/**
 * @brief Fjerner gitt ting fra tinglisten
 * 
 * @param ting Tingen som skal slettes
*/
void Kategori::fjernTing(NyTing *ting) {
    tingListe.remove(ting);
}