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
 * Deconstructor for kategorier. Sletter først hver kategori, sletter deretter
 * kategoriMappet i seg selv. 
*/
Kategorier::~Kategorier() {
    for (auto &kategori: kategoriMap) {
        delete kategori.second;
    }
    kategoriMap.clear();
}

/**
 * Skriver ut valgmuligheter for ting.
 * 
 * @param valg Valget brukeren ønsker å foreta
 * 
 * @see lagTingIKategori()
 * @see endreTingIKategori()
 * @see skrivMeny()
*/
void Kategorier::tingHandling(char valg) {
    if (valg == 'N') {
        lagTingIKategori();
    } else if (valg == 'E') {
        endreTingIKategori();
    } else {
        skrivMeny();
    }
}

/**
 * Håndterer overordnede valgmuligheter for kategorier. 
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
        case 'N':   lagKategori();  break;
        case 'A':   skrivAlle();    break;
        case 'S':   skrivEntydig(); break;
        default:    skrivMeny();    break;
    }
}

/**
 * Leser alle kategorier og alle deres ting fra fil.
 * 
 * @see Kategori::Kategori(...)
 * @see Kategori::hentNavn()
*/
void Kategorier::lesFraFil() {
    std::ifstream kategoriFil("data/KATEGORIER.DTA");

    if (kategoriFil) {
        std::cout << "Leser fra filen KATEGORIER.DTA" << std::endl;

        while(!kategoriFil.eof()) {
            Kategori *kategori = new Kategori(kategoriFil);
            // Legger inn kategorien i mappet, med navnet som identifikator
            kategoriMap.insert(std::pair<std::string, Kategori *>
            (kategori->hentNavn(), kategori));
        }

        std::cout << "Leste inn " << kategoriMap.size() 
                  << " kategorier fra KATEGORIER.DTA" << std::endl;
    } else {
        std::cout << "Kunne ikke lese fra /data/KATEGORIER.DTA." << std::endl;
    }

    kategoriFil.close();
}

/**
 * Oppretter ny kategori dersom den ikke allerede finnes.
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
        kategoriMap.insert(std::pair<std::string, Kategori *>
        (kategoriNavn, kategori));
        std::cout << "Opprettet kategori " << kategori->hentNavn() << ".\n";
    } else {
        std::cout << "Kategorien finnes allerede." << std::endl;
    }
}

/**
 * Sjekker om det finnes en kategori med gitt navn
 * 
 * @param kategoriNavn Navnet på kategorien
 * 
 * @return true hvis den finnes, ellers false
*/
bool Kategorier::kategoriFinnes(std::string kategoriNavn) {
    return kategoriMap.count(kategoriNavn);
}

/**
 * Fjerner en gitt kategori
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
 * Skriver alle kategorier.
 * 
 * @see Kategori::skrivData()
*/
void Kategorier::skrivAlle() const {
    for (const auto &kategori: kategoriMap) {
        kategori.second->skrivData();
    }
}

/**
 * Skriver en entydig kategori. Entydig har vi tolket som at det er den eneste
 * som ligner eller som det kan være. Dersom det er flere som kan tolkes som 
 * entydige får brukeren beskjed om dette, og mulighet til å velge den de mente.
 * 
 * @param kategoriNavn Navnet på kategorien man ønsker å finne
 * 
 * @see stringTilLiten(...)
 * @see lesInt(...)
 * 
 * @return Kategori peker, evt nullptr
*/
Kategori *Kategorier::hentKategoriEntydig(std::string kategoriNavn) {
   Kategori* element = nullptr;

    if (!kategoriMap.count(kategoriNavn)) {
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
 * Oppretter ny ting i en gitt kategori.
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
        << kategoriNavn << std::endl;
    }
}

/**
 * Endre datamedlemmer for gitt ting i gitt kategori, evt feilmelding om
 * kategorien ikke finnes.
 * 
 * @see lesString(...)
 * @see Kategorier::hentKategoriEntydig(...)
 * @see Kategori::skrivData()
 * @see Kategori::hentAntallTing()
 * @see Kategori::hentTing(...)
 * @see Kategori::endreTing()
*/
void Kategorier::endreTingIKategori() {
    std::string kategoriNavn = lesString("Velg kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivData();
        int tingNummer = lesInt("Hvilken ting vil du endre?", 1, 
                                kategori->hentAntallTing());
        // Endrer ting i funnet kategori
        kategori->hentTing(tingNummer)->endreTing();
    } else {
        std::cout << "Det finnes ingen kategori med navn " 
                  << kategoriNavn << std::endl;
    }
}

/**
 * Kjøp ting i kategori. Spør først etter kundenummer, spør deretter etter 
 * navnet på kategorien, og deretter navnet på tingen de ønsker å kjøpte, evt
 * 0 for å avbryte kjøpet. Har også feilmelding dersom kategorien ikke finnes.
 * 
 * @see lesInt(...)
 * @see lesString(...)
 * @see Kategori::skrivFullKategori(...)
 * @see Kategori::hentAntallTing(...)
 * @see Kategorier::hentKategoriEntydig(...)
 * @see Kunder::hentKunde(...)
 * @see Kunde::kjopTing(...)
*/
void Kategorier::kjopTing() {
    int tingnummer;
    int kundenummer = lesInt("Kundenummer:", 1, gKundebase.antallKunder());
    std::string kategoriNavn = lesString("Kategori");

    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivFullKategori();
        tingnummer = lesInt("Skriv inn nummer på tingen du vil kjøpe, 0"
        " for å avbryte", 0, kategori->hentAntallTing());

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

/**
 * Skriver alle kategorier og alle ting i hver enkelt kategori til fil
 * 
 * @see Kategori::skrivTilFil(...)
*/
void Kategorier::skrivAlleTilFil() {
    std::ofstream kategoriFil("data/KATEGORIER.DTA");

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

/**
 * Skriver entydig kategori ut ifra gitt input.
 * 
 * @see lesString(...)
 * @see hentKategoriEntydig(...)
 * @see Kategori::skrivData()
*/
void Kategorier::skrivEntydig() {
    std::string kategoriNavn = lesString("Kategori");
    auto kategori = hentKategoriEntydig(kategoriNavn);

    if (kategori) {
        kategori->skrivData();
    } else {
        std::cout << kategoriNavn << " er ikke en kategori!" << std::endl;
    }
}