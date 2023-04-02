/**
 *  Definisjon av funksjoner i Kunde klassen
 *
 *  @file      kunde.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "lesData3.hpp"
#include "kunder.hpp"
#include "nyTing.hpp"
#include "kunde.hpp"

extern Kunder gKundebase;

/**
 * @brief Kunde constructor med Kundenummer parameter.
 *
 * Den setter også alle datamedlemmer.
 * 
 * @param Kundenummer Kundenummeret til kunden som skal opprettes
 * 
 * @see Kunde::settData()
*/
Kunde::Kunde(int Kundenummer) {
    kundenummer = Kundenummer;
    settData();
}

/**
 * @brief Kunde constructor med filparameter for å opprette kunder fra fil
 * 
 * @param kundeFil Filen som skal leses inn fra
*/
Kunde::Kunde(std::ifstream &kundeFil, int Kundenummer) {
    kundenummer = Kundenummer;

    kundeFil >> mobilnummer;
    kundeFil.ignore();

    kundeFil >> postnummer;
    kundeFil.ignore();

    kundeFil >> antallTingKjopt;
    kundeFil.ignore();

    kundeFil >> antallTingSolgt;
    kundeFil.ignore();

    kundeFil >> antallTingTilSalgs;
    kundeFil.ignore();

    std::getline(kundeFil, navn);
    navn[navn.length()] = '\0';

    std::getline(kundeFil, gateAdresse);
    gateAdresse[gateAdresse.length()] = '\0';

    std::getline(kundeFil, postSted);
    postSted[postSted.length()] = '\0';

    std::getline(kundeFil, mailAdresse);
    mailAdresse[mailAdresse.length()] = '\0';
}

/**
 * @brief Setter alle datamedlemmer for gitt kunde
 * 
 * @see lesString(...)
 * @see lesInt(...)
*/
void Kunde::settData() {
    navn = lesString("Navn");
    gateAdresse = lesString("Gateadresse");
    mobilnummer = lesInt("Mobilnummer", 40000000, 99999999);
    mailAdresse = lesString("Mailadresse");
    postSted = lesString("Poststed");
    postnummer = lesInt("Postnummer", 0, 9999);

    antallTingKjopt = 0;
    antallTingSolgt = 0;
    antallTingTilSalgs = 0;
}

/**
 * @brief Henter gitt kunde sitt kundenummer
 * 
 * @return int kundenummer kundenummeret
*/
int Kunde::hentKundenummer() {
    return kundenummer;
}

/**
 * @brief Skriver ut all data om kunde.
*/
void Kunde::skrivData() const {
    std::cout << "Navn: " << navn
              << "\nGateadresse: " << gateAdresse
              << "\nMobilnummer: " << mobilnummer
              << "\nMailadresse: " << mailAdresse
              << "\nPoststed: " << postSted
              << "\nPostnummer: " << postnummer
              << "\nAntall ting kjøpt: " << antallTingKjopt
              << "\nAntall ting solgt: " << antallTingSolgt
              << "\nAntall til salgs: " << antallTingTilSalgs << '\n';
}

/**
 * @brief Skriver ut basisinfo om kunde.
 *
 * Dette innebærer kundenummer, navn og telefonnummer.
*/
void Kunde::skrivInfo() const {
    std::cout << "Kundenummer: " << kundenummer+1 
              << "\tNavn: " << navn 
              << "\tTlf: " << mobilnummer << '\n';
}

/**
 * @brief Skriver gitt kunde til fil.
 * 
 * @param kundeFil Filen kunden skal skrives til
*/
void Kunde::skrivTilFil(std::ofstream &kundeFil) {
    kundeFil << kundenummer+1 << ' ' << mobilnummer << ' ' << postnummer << ' ' 
    << antallTingKjopt << ' ' << antallTingSolgt << ' ' << antallTingTilSalgs 
    << '\n' << navn << '\n' << gateAdresse << '\n' << postSted << '\n' 
    << mailAdresse << '\n';
}

/**
 * @brief Funksjon for å la kunde kjøpe ting i kategorier
 * 
 * @param kategori Peker til aktuell kategori
 * @param ting Peker til aktuell ting
 * 
 * @see NyTing::hentSelgernummer()
 * @see NyTing::hentNavn()
 * @see Kunder::hentKunde(...)
 * @see selgTing(...)
*/
void Kunde::kjopTing(Kategori *kategori, NyTing *ting, int kundenummer) {
    int selgernummer = ting->hentSelgernummer();
    Kunde* selger = gKundebase.hentKunde(selgernummer);

    if (kundenummer != selgernummer) {
        std::cout << "Kjøpte ting " << ting->hentNavn() << '\n';
        selger->selgTing(ting);
        antallTingKjopt+=1;
    } else {
        std::cout << "Du kan ikke kjøpe av deg selv!\n";
    }
}

/**
 * @brief Selger ting
 * 
 * Funksjon for å la kunde selge ting i kategorier. Øker antall ting solgt,
 * senker antall ting til salgs, og endrer antall igjen av tingen, evt sletter 
 * tingen.
 * 
 * @param ting Tingen som skal selges
 * 
 * @see NyTing::hentAntall()
 * @see NyTing::endreAntall()
*/
void Kunde::selgTing(NyTing *ting) {
    int antall = ting->hentAntall();
    antallTingSolgt+=1;
    antallTingTilSalgs-=1;

    if (antall > 1) {
        ting->endreAntall(antall-1);
    } else {
        delete ting;
    }
}