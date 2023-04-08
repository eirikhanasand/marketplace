/**
 *  Definisjon av funksjoner i Kategorier klassen
 *
 *  @file      kategorier.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "kunder.hpp"
#include "kategorier.hpp"
#include "kategori.hpp"
#include "lesData3.hpp"
#include "skrivMeny.hpp"

extern Kunder gKundebase;

/**
 * @brief Deconstructor for kategorier
 *
 * Sletter først hver kategori, sletter deretter
 * kategoriMappet i seg selv
*/
Kategorier::~Kategorier() {
    for (auto &[navn, data] : kategoriMap) {
        delete data;
    }
    kategoriMap.clear();
}

/**
 * @brief Skriver ut valgmuligheter for ting.
 * 
 * @param valg Valget brukeren ønsker å foreta
 * 
 * @see lagTingIKategori()
 * @see endreTingIKategori()
 * @see skrivMeny()
*/
void Kategorier::tingHandling(char valg) {
    switch (valg) {
        case 'N': lagTingIKategori();   break;
        case 'E': endreTingIKategori(); break;
        default:  skrivMeny();          break;
    }
}

/**
 * @brief Håndterer overordnede valgmuligheter for kategorier.
 *
 * Valgmuligheter:
 * - Ny ting i kategori
 * - Skriv alle ting i kategori
 * - Skriv entydig kategori
 * - Skriv hovedmeny
 * 
 * @param valg Valget brukeren ønsker å foreta
 * 
 * @see Kategorier::lagKategori()
 * @see Kategorier::skrivAlle()
 * @see Kategorier::skrivEntydig()
 * @see skrivMeny()
*/
void Kategorier::kategoriHandling(char valg) {
    switch (valg) {
        case 'N': {
            lagKategori();
            break;
        }
        case 'A': {
            skrivAlle();
            break;
        }
        case 'S': {
            skrivEntydig();
            break;
        }
        default: {
            skrivMeny();
            break;
        }
    }
}

/**
 * @brief Leser alle kategorier og alle deres ting fra fil.
 * 
 * @see Kategori::Kategori(...)
 * @see Kategori::hentNavn()
 * @see antallKategorier()
*/
void Kategorier::lesFraFil() {
    std::ifstream kategoriFil("data/KATEGORIER.DTA");
    std::string navn;

    if (kategoriFil) {
        std::cout << "Leser fra filen KATEGORIER.DTA\n";

        while (!kategoriFil.eof()) {
            std::getline(kategoriFil, navn);

            if (navn.length()) {
                navn[navn.length()] = '\0';
                Kategori *kategori = new Kategori(kategoriFil, navn);
                // Legger inn kategorien i mappet, med navnet som identifikator
                kategoriMap[kategori->hentNavn()] = kategori;
            }
        }

        if (antallKategorier()) {
            std::cout << "Leste inn " << antallKategorier() 
                  << " kategorier fra KATEGORIER.DTA\n";
        } else {
            std::cout << "Kategorifilen er tom!\n";
        }
    } else {
        std::cout << "Kunne ikke lese fra /data/KATEGORIER.DTA.\n";
    }

    kategoriFil.close();
}

/**
 * @brief Oppretter ny kategori dersom den ikke allerede finnes.
 * 
 * @see lesString(...)
 * @see kategoriFinnes(...)
 * @see Kategori::settData(...)
 * @see Kategori::hentNavn()
*/
void Kategorier::lagKategori() {
    std::string kategoriNavn = lesString("Kategorinavn");

    if (!kategoriFinnes(kategoriNavn)) {
        Kategori *kategori = new Kategori();
        kategori->settData(kategoriNavn);

        // Legger kategorien inn i mappet
        kategoriMap[kategoriNavn] = kategori;

        std::cout << "Opprettet kategori " << kategori->hentNavn() << ".\n";
    } else {
        std::cout << "Kategorien finnes allerede.\n";
    }
}

/**
 * @brief Sjekker om det finnes en kategori med gitt navn
 * 
 * @param kategoriNavn Navnet på kategorien
 * 
 * @return true hvis den finnes, ellers false
*/
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    return kategoriMap.count(kategoriNavn);
}

/**
 * @brief Fjerner en gitt kategori
 * 
 * @param kategori Peker til kategorien som skal slettes
 * 
 * @see Kategori::hentNavn()
*/
void Kategorier::fjernKategori(Kategori *kategori) {
    auto funn = kategoriMap.find(kategori->hentNavn());
    kategoriMap.erase(funn);
    delete kategori;
}

/**
 * @brief Skriver alle kategorier.
 * 
 * @see Kategori::skrivData()
 * @see Kategori::skrivTing()
 * @see antallKategorier()
*/
void Kategorier::skrivAlle() const {
    if (antallKategorier()) {
        for (const auto &[navn, data] : kategoriMap) {
            data->skrivData();
        }
    } else {
        std::cout << "Det finnes ingen kategorier å skrive ut.\n";
    }
}

/**
 * @brief Henter en entydig kategori.
 *
 * Entydig har vi tolket som at det er den eneste
 * som ligner eller som det kan være. Dersom det er flere som kan tolkes som 
 * entydige får brukeren beskjed om dette, og mulighet til å velge den de mente.
 * 
 * @param kategoriNavn Navnet på kategorien man ønsker å finne
 * 
 * @see stringTilLiten(...)
 * @see lesInt(...)
 * @see kategoriFinnes(std::string)
 * 
 * @return Kategori peker, evt nullptr
*/
Kategori *Kategorier::hentKategoriEntydig(std::string kategoriNavn) {
    Kategori* element = nullptr;

    if (!kategoriFinnes(kategoriNavn)) {
        // Vector over funn
        std::vector<std::string> funn;

        std::string liteNavn = stringTilLiten(kategoriNavn);

        // Går gjennom alle kategoriene
        for (auto iterator = kategoriMap.begin();
                iterator != kategoriMap.end();
                iterator++)
        {
            // Gjør om hvert kategorinavn til lowercase
            std::string liteFunn = stringTilLiten(iterator->first);

            // Legger funnet i funnvectoren
            if (liteFunn.find(liteNavn) != std::string::npos) {
                funn.push_back(iterator->first);
            }
        }

        if (funn.size()) { // Nummererer og skriver ut antall funn
            for (int i = 1; i <= funn.size(); i++) {
                std::cout << '[' << i << ']' << " " << funn.at(i-1) << '\n';
            }
            // Brukeren bes velge kategori
            int valg = lesInt("Velg kategori:", 1, funn.size());

            // Elementet blir satt til ønsket kategori
            element = kategoriMap.find(funn.at(valg-1))->second;
        }
    } else {
        // Returnerer med en gang hvis det ikke finnes flere treff
        element = kategoriMap.find(kategoriNavn)->second;
    }
    // Elementet returneres
    return element;
}

/**
 * @brief Oppretter ny ting i en gitt kategori.
 * 
 * @see lesString(...)
 * @see hentKategoriEntydig(...)
 * @see lagTing()
*/
void Kategorier::lagTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->lagTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn "
                  << kategoriNavn << '\n';
    }
}

/**
 * @brief Endre datamedlemmer for gitt ting i gitt kategori.
 *
 * Evt feilmelding om kategorien ikke finnes.
 * 
 * @see lesString(...)
 * @see Kategorier::hentKategoriEntydig(...)
 * @see Kategori::skrivData()
 * @see Kategori::sisteTing()
 * @see Kategori::hentTing(...)
 * @see Kategori::endreTing()
*/
void Kategorier::endreTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivData();
        kategori->skrivTingIndeksert();

        int tingIndeks = lesInt("Hvilken ting vil du endre?", 1,
                                kategori->antallTing());
        // Endrer ting i funnet kategori
        auto ting = kategori->hentTingMedIndeks(tingIndeks);

        ting->endreTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn "
                  << kategoriNavn << '\n';
    }
}

/**
 * @brief Kjøp ting i kategori.
 *
 * Spør først etter kundenummer, spør deretter etter
 * navnet på kategorien, og deretter navnet på tingen de ønsker å kjøpte, evt
 * 0 for å avbryte kjøpet. Har også feilmelding dersom kategorien ikke finnes.
 * 
 * @see lesInt(...)
 * @see lesString(...)
 * @see Kategori::skrivTing(...)
 * @see Kategori::sisteTing(...)
 * @see hentKategoriEntydig(...)
 * @see Kunder::hentKunde(...)
 * @see Kunde::kjopTing(...)
*/
void Kategorier::kjopTing() {
    int indeks;
    Kunde* kunde;
    int kundenummer;

    do {
        kundenummer = lesInt("Kundenummer:", 1, gKundebase.sisteKunde())-1;
        kunde = gKundebase.hentKunde(kundenummer);

        if (!kunde) {
            std::cout << "Denne kunden er slettet. Vennligst bruk en annen"
                         " kunde.\n";
        }
    } while (!kunde);

    std::string kategoriNavn = lesString("Kategori");

    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivTingIndeksert();
        indeks = lesInt("Skriv inn nummer på tingen du vil kjøpe, 0"
        " for å avbryte", 0, kategori->antallTing());

        if (indeks) {
            auto ting = kategori->hentTingMedIndeks(indeks);
            auto kunde = gKundebase.hentKunde(kundenummer);

            kunde->kjopTing(kategori, ting, kundenummer);
        } else {
            std::cout << "Avbrøt kjøp!\n";
        }
    } else {
        std::cout << "Denne kategorien finnes ikke!\n";
    }
}

/**
 * @brief Skriver alle kategorier og alle ting i hver enkelt kategori til fil
 * 
 * @see Kategori::skrivTilFil(...)
 * @see antallKategorier()
*/
void Kategorier::skrivAlleTilFil() {
    // Sjekker først om det finnes kategorier, utfører deretter skriving til fil
    if (antallKategorier()) {
        std::ofstream kategoriFil("data/KATEGORIER.DTA");

        if (kategoriFil) {
            std::cout << "Leser til filen KATEGORIER.DTA\n";

            for (const auto &[navn, data] : kategoriMap) {
                data->skrivTilFil(kategoriFil);
            }

            kategoriFil.close();
        } else {
            std::cout << "Kunne ikke lese til /data/KATEGORIER.DTA.\n";
        }

        kategoriFil.close();
    } else {
        std::cout << "Det finnes ingen kategorier å skrive til fil.\n";
    }
}

/**
 * @brief Skriver entydig kategori ut ifra gitt input.
 * 
 * @see lesString(...)
 * @see hentKategoriEntydig(...)
 * @see Kategori::skrivData()
 * @see Kategori::skrivTingMindre()
 * @see antallKategorier()
*/
void Kategorier::skrivEntydig() {
    if (antallKategorier()) {
        std::string kategoriNavn = lesString("Kategori");
        auto kategori = hentKategoriEntydig(kategoriNavn);

        if (kategori) {
            kategori->skrivData();
            kategori->skrivTingMindre();
        } else {
            std::cout << kategoriNavn << " er ikke en kategori!\n";
        }
    } else {
        std::cout << "Det finnes ingen kategorier å skrive ut.\n";
    }
}

/**
 * @brief Øker antall ting som finnes totalt
*/
void Kategorier::okAntallTing() {
    antallTing++;
}

/**
 * @brief Antall kategorier i programmet
 * 
 * @return int Antall kategorier
 */
int Kategorier::antallKategorier() const {
  return kategoriMap.size();
}

/**
 * @brief Totalt antall ting i programmet
 * 
 * @return int antall ting
*/
int Kategorier::hentAntallTing() {
    return antallTing;
}