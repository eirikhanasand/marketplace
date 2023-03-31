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
 * Oppretter ting basert på medsendt nummer og setter tingens nummer til dette.
*/
NyTing::NyTing(int Nummer) {
    nummer = Nummer;
}

/**
 * Setter alle datamedlemmer for en gitt ting
 * 
 * @see lesInt(...)
 * @see lesString(...)
*/
void NyTing::settData() {
    selgernummer = lesInt("Kundenummer", 1, gKundebase.antallKunder());
    navn = lesString("Navn på tingen");
    beskrivelse = lesString("Beskriv tingen");
    pris = lesInt("Hvor mye koster tingen", 0, MAKS_PRIS);
    antall = lesInt("Hvor mange selger du", 0, MAKS_ANTALL);
}

/**
 * Skriver all data om en gitt ting
 * 
*/
void NyTing::skrivData() const {
    std::cout << "Selger " << selgernummer 
              << "\tTing: " << nummer 
              << "\tNavn: " << navn 
              << "\tAntall: " << antall 
              << "\tPris: " << pris 
              << "\tBeskrivelse: " << beskrivelse << std::endl;
}

/**
 * Henter navnet til en gitt ting
 * 
 * @returns std::string Navnet på tingen
 */
std::string NyTing::hentNavn() const {
    return navn;
}

/**
 * Henter antall av en gitt ting
 * 
 * @returns int Antall av tingen
 */
int NyTing::hentAntall() {
    return antall;
}

/**
 * Endrer antall av en gitt ting
 * 
 * @param nyttAntall Tingens nye antall
*/
void NyTing::endreAntall(int nyttAntall) {
    antall = nyttAntall;
}

/**
 * Endrer navn på en gitt ting
 * 
 * @param nyttNavn Tingens nye navn
*/
void NyTing::endreNavn(std::string nyttNavn) {
    navn = nyttNavn;
}

/**
 * Endrer pris for en gitt ting
 * 
 * @param nyPris Tingens nye pris
*/
void NyTing::endrePris(int nyPris) {
    pris = nyPris;
}

/**
 * Endrer beskrivelse for gitt ting
*/
void NyTing::endreBeskrivelse(std::string nyBeskrivelse) {
    beskrivelse = nyBeskrivelse;
}

/**
 * Henter nummer for gitt ting
 * 
 * @return int nummer
*/
int NyTing::hentNummer() const {
    return nummer;
}

/**
 * Henter selgernummer for gitt ting
 * 
 * @return int selgernummer
*/
int NyTing::hentSelgernummer() const {
    return selgernummer;
}

/**
 * Funksjon for å endre på en gitt ting sine datamedlemmer. Skriver først
 * ut meny for å bestemme hvilket datamedlem som skal endres på, og referererer
 * videre til relevant funksjon som kan utføre endringen.
 * 
 * @see lesInt(...)
 * @see lesString(...)
 * @see NyTing::endreNavn(...)
 * @see NyTing::endreAntall(...)
 * @see NyTing::endrePris(...)
 * @see NyTing::endreBeskrivelse(...)
*/
void NyTing::endreTing() {
    std::cout << "Hva vil du endre på?" << '\n'
        << "1. Navn" << '\n'
        << "2. Antall" << '\n'
        << "3. Pris" << '\n'
        << "4. Beskrivelse" << '\n'
        << "5. Avbryt" << '\n';

    int valg = lesInt("Valg: ", 1, 5);

    switch (valg) {
        case '1': {
            std::string navn = lesString("Nytt navn");
            endreNavn(navn);
            break;
        }
        case '2': {
            int antall = lesInt("Nytt antall", 1, MAKS_ANTALL);
            endreAntall(antall);
            break;
        }
        case '3': {
            int pris = lesInt("Ny pris", 1, MAKS_PRIS);
            endrePris(pris);
            break;
        }
        case '4': {
            std::string beskrivelse = lesString("Ny beskrivelse");
            endreBeskrivelse(0);
            break;
        }
        default: break;
    }
}

/**
 * Constructor for ting som setter tingenes data ut ifra innhold lest
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
 * Skriver all informasjon om gitt ting til fil.
 * 
 * @param tingFil Filen tingen skal skrives til
*/
void NyTing::skrivTilFil(std::ofstream &tingFil) {
    tingFil << selgernummer << nummer << ' ' << pris << ' ' << antall << '\n' 
            << navn << '\n' << beskrivelse << '\n';
}

/**
 * Setter alle int datamedlemmer for ting utifra det som blir lest inn fra fil.
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
 * Setter navn og beskrivelse for ting. Dette må ha egen funksjon for at 
 * BruktTing sin lesData skal funke, på grunn av måten dette er lagret på fil.
 * 
 * @param tingFil Filen tingens variabler skal leses inn fra
*/
void NyTing::settRestData(std::ifstream &tingFil) {
    std::getline(tingFil, navn);
    navn[navn.length()] = '\0';

    std::getline(tingFil, beskrivelse);
    beskrivelse[beskrivelse.length()] = '\0';
}