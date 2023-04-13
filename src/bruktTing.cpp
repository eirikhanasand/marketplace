/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av 
 *  data, setting av antall år tingen er brukt, og tingens kvalitet
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>

#include "kategorier.hpp"
#include "bruktTing.hpp"
#include "lesData3.hpp"
#include "nyTing.hpp"
#include "const.hpp"

/**
 * @brief Constructor for BruktTing.
 *
 * Denne inneholder ingenting, men er nødvendig for
 * compileren ettersom den først kjører NyTing sin constructor.
 * 
 * @param Nummer Tingens unike nummer
 * 
 * @see NyTing(...)
*/
BruktTing::BruktTing(int Nummer):NyTing(Nummer) {

}

/**
 * @brief Constructor som leser inn BruktTing fra fil.
 * 
 * @param tingFil Referanse til filen som skal leses inn fra
 * 
 * @see NyTing(...)
 * @see settData(...) 
*/
BruktTing::BruktTing(std::ifstream &tingFil):NyTing(tingFil) {
    settData(tingFil);
}

/**
 * @brief Destructor for BruktTing.
 *
 * Denne er tom (default), men er nødvendig for compileren.
*/
BruktTing::~BruktTing() {

}

/**
 * @brief Settdata funksjon for BruktTing,
 * for å sette ekstra datamedlemmer som ikke finnes i NyTing sin settData.
 *
 * Kaller først på morklassen sin settData
 * funksjon, og setter deretter spesifikke data for denne subklassen.
 * 
 * @see NyTing::settData()
 * @see lesInt(...)
*/
void BruktTing::settData() {
    NyTing::settData();
    aar = lesInt("Tingens alder", 0, MAKS_ALDER);
    int kategoriKvalitet = lesInt(
            "Hvor sliten er tingen? 1 = SomNy, 2 = "
            "PentBrukt, 3 = Brukt, 4 = GodtBrukt, 5 = Sliten", 1, 5
    );
    kvalitet = static_cast<Kvalitet>(kategoriKvalitet-1);
}

/**
 * @brief Skriver ut alle datamedlemmer om objekter av BruktTing klassen
 * 
 * @see NyTing::skrivData()
*/
void BruktTing::skrivData() const {
    NyTing::skrivData();
    std::cout << "Tingens alder: " << aar << "år, kvalitet: "
              << kvalitet << '\n';
}

/**
 * @brief Skriver alt utenom selgernummer for BruktTing
 * 
 * @see NyTing::skrivMindreData()
*/
void BruktTing::skrivMindreData() const {
    NyTing::skrivMindreData();
    std::cout << "Tingens alder: " << aar << "år, kvalitet: "
              << kvalitet << '\n';
}

/**
 * @brief Skriver BruktTing objekter til fil
 * 
 * @param tingFil Referanse til filen som skal skrives til
 * 
 * @see NyTing::skrivTilFil(...)
*/
void BruktTing::skrivTilFil(std::ofstream &tingFil) const {
    NyTing::skrivTilFil(tingFil);
    tingFil << ' ' << aar << ' ' << static_cast<int>(kvalitet);
}

/**
 * @brief Leser inn datamedlemmer for BruktTing.
 *
 * Leser deretter restmedlemmer
 * fra NyTing klassen som ikke kan leses inn før dette er gjort.
 * 
 * @param tingFil Referanse til filen som skal leses fra
 * 
 * @see NyTing::settRestData(...)
*/
void BruktTing::settData(std::ifstream &tingFil) {
    int kvalitetInt;
    
    tingFil >> aar;
    tingFil.ignore();
    tingFil >> kvalitetInt;
    tingFil.ignore();

    kvalitet = static_cast<Kvalitet>(kvalitetInt-1);

    NyTing::settRestData(tingFil);
}

/**
 * @brief Funksjon for å endre på en BruktTing sine datamedlemmer.
 *
 * Skriver først ut meny for å bestemme hvilket datamedlem som skal endres på,
 * og referererer videre til relevant funksjon som kan utføre endringen.
 * 
 * @see NyTing::endreTing()
 * @see lesInt(...)
 * @see lesString(...)
*/
void BruktTing::endreTing() {
    NyTing::endreTing();
    int valg = lesInt("1. Alder\n2. Kvalitet\n", 1, 2);
    
    switch (valg) {
        case 1: 
            aar = lesInt("Ny alder", 1, MAKS_ALDER);
            break;
        case 2:
            int kategoriKvalitet = lesInt(
            "Hvor sliten er tingen? 1 = SomNy, 2 = "
            "PentBrukt, 3 = Brukt, 4 = GodtBrukt, 5 = Sliten", 1, 5
            );
            kvalitet = static_cast<Kvalitet>(kategoriKvalitet-1);
            break;
    }
}