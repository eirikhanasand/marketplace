/**
 *  Definisjon av funksjoner i BruktTing klassen
 *
 *  @file      nyTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "kategorier.hpp"
#include "bruktTing.hpp"
#include "kategori.hpp"
#include "lesData3.hpp"
#include "nyTing.hpp"
#include "kunder.hpp"
#include "const.hpp"

extern Kunder gKundebase;
extern Kategorier gKategoribase;

/**
 * @brief NyTing constructor
 *
 * Oppretter ting basert på medsendt nummer og setter tingens nummer til dette.
*/
NyTing::NyTing(int Nummer) {
    nummer = Nummer;
}

/**
 * @brief Destructor for NyTing.
 *
 * Denne er tom (default), men er nødvendig for compileren.
*/
NyTing::~NyTing() {

}

/**
 * @brief Setter alle datamedlemmer for en NyTing
 * 
 * @see lesInt(...)
 * @see lesString(...)
 * @see Kunder::hentKunde(...)
 * @see Kunder::sisteKunde()
*/
void NyTing::settData() {
    int tempSelger;
    Kunde* kunde;

    do {
        tempSelger = lesInt("Kundenummer", 1, gKundebase.sisteKunde())-1;
        kunde = gKundebase.hentKunde(tempSelger);

        if (!kunde) {
            std::cout << "Denne kunden er slettet. Bruk kommandoen AA for å se"
            " kundelisten.\n";
        }
    } while (!kunde);

    selgernummer = tempSelger;
    navn = lesString("Navn på tingen");
    beskrivelse = lesString("Beskriv tingen");
    pris = lesInt("Hvor mye koster tingen", 0, MAKS_PRIS);
    antall = lesInt("Hvor mange selger du", 1, MAKS_ANTALL);
}

/**
 * @brief Skriver all data om en NyTing
*/
void NyTing::skrivData() const {
    std::cout << "Selger " << selgernummer+1
              << "\tTingnummer: " << nummer
              << "\tNavn: " << navn
              << "\tAntall: " << antall
              << "\tPris: " << pris
              << "kr\tBeskrivelse: " << beskrivelse << '\n';
}

/**
 * @brief Skriver all data om en NyTing utenom dens selgernummer.
*/
void NyTing::skrivMindreData() const {
    std::cout << "Tingnummer: " << nummer
              << "\tNavn: " << navn
              << "\tAntall: " << antall
              << "\tPris: " << pris
              << "kr\tBeskrivelse: " << beskrivelse << '\n';
}

/**
 * @brief Henter navnet til en NyTing
 * 
 * @returns std::string Navnet på tingen
 */
std::string NyTing::hentNavn() const {
    return navn;
}

/**
 * @brief Henter antallet til en NyTing
 * 
 * @returns int Antall av tingen
 */
int NyTing::hentAntall() const {
    return antall;
}

/**
 * @brief Endrer antall av en NyTing
 * 
 * @param nyttAntall Tingens nye antall
*/
void NyTing::endreAntall(int nyttAntall) {
    antall = nyttAntall;
}

/**
 * @brief Henter nummer for en NyTing
 * 
 * @return int nummer
*/
int NyTing::hentNummer() const {
    return nummer;
}

/**
 * @brief Henter selgernummer for en NyTing
 * 
 * @return int selgernummer
*/
int NyTing::hentSelgernummer() const {
    return selgernummer;
}

/**
 * @brief Funksjon for å endre på en NyTing sine datamedlemmer.
 *
 * Skriver først ut meny for å bestemme hvilket datamedlem som skal endres på,
 * og referererer videre til relevant funksjon som kan utføre endringen.
 * 
 * @see lesInt(...)
 * @see lesString(...)
 * @see NyTing::endreNavn(...)
 * @see NyTing::endreAntall(...)
 * @see NyTing::endrePris(...)
 * @see NyTing::endreBeskrivelse(...)
*/
void NyTing::endreTing() {
    std::cout << "Hva vil du endre på?\n1. Navn\n2. Antall\n3. Pris\n4. "
    "Beskrivelse\n5. Avbryt\n";

    int valg = lesInt("Valg", 1, 5);

    switch (valg) {
        case 1: {
            navn = lesString("Nytt navn");
            break;
        }
        case 2: {
            antall = lesInt("Nytt antall", 1, MAKS_ANTALL);
            break;
        }
        case 3: {
            pris = lesInt("Ny pris", 1, MAKS_PRIS);
            break;
        }
        case 4: {
            beskrivelse = lesString("Ny beskrivelse");
            break;
        }
        default: {
            break;
        }
    }
}

/**
 * @brief Constructor for ting som setter tingenes data ut ifra innhold lest
 * fra medsendt fil. 
 * 
 * @param tingFil Filen tingen leses inn fra
 * 
 * @see NyTing:::settData()
*/
NyTing::NyTing(std::ifstream &tingFil) {
    settData(tingFil);
} 

/**
 * @brief Skriver talldata til fil
 * 
 * Skriver selgernummer, tingens nummer, pris og antall til fil
 * 
 * @param tingFil Filen tingen skal skrives til
*/
void NyTing::skrivTilFil(std::ofstream &tingFil) const {
    int tallErBrukt = erBrukt ? 1:0;

    tingFil << tallErBrukt <<  ' '
            << selgernummer << ' '
            << nummer << ' '
            << pris << ' '
            << antall;
}

/**
 * @brief Skriver all informasjon om gitt ting til fil.
 * 
 * @param tingFil Filen tingen skal skrives til
*/
void NyTing::skrivRestDataTilFil(std::ofstream &tingFil) {
    tingFil  << '\n' << navn << '\n' << beskrivelse << '\n';
}

/**
 * @brief Setter data om ting
 * 
 * Setter selgernummer, tingens nummer, pris og antall utifra det som
 * ble lest inn fra fil
 * 
 * @param tingFil Filen tingens variabler skal leses inn fra
*/
void NyTing::settData(std::ifstream &tingFil) {
    tingFil >> selgernummer;
    tingFil.ignore();
    tingFil >> nummer;
    tingFil.ignore();
    tingFil >> pris;
    tingFil.ignore();
    tingFil >> antall;
    tingFil.ignore();
}

/**
 * @brief Setter navn og beskrivelse for en NyTing.
 *
 * Dette må ha egen funksjon for at BruktTing sin lesData skal funke,
 * på grunn av måten dette er lagret på fil.
 * 
 * @param tingFil Filen tingens variabler skal leses inn fra
*/
void NyTing::settRestData(std::ifstream &tingFil) {
    std::getline(tingFil, navn);
    navn[navn.length()] = '\0';

    std::getline(tingFil, beskrivelse);
    beskrivelse[beskrivelse.length()] = '\0';
}

/**
 * @brief Setter erBrukt for ting
 * 
 * @param status Om tingen er brukt eller ikke
*/
void NyTing::settBruktStatus(bool status) {
    if (status) {
        erBrukt = true;
    } else {
        erBrukt = false;
    }
}
