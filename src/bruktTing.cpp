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
 * @see NyTing(int)
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
    int kategoriKvalitet = lesInt("Hvor sliten er tingen? 1 = SomNy, 2 = "
    "PentBrukt, 3 = Brukt, 4 = GodtBrukt, 5 = Sliten", 1, 5);

    switch (kategoriKvalitet) {
        case 1: kvalitet = SomNy;       break;
        case 2: kvalitet = PentBrukt;   break;
        case 3: kvalitet = Brukt;       break;
        case 4: kvalitet = GodtBrukt;   break;
        case 5: kvalitet = Sliten;      break;
    }
}

/**
 * @brief Skriver ut alle datamedlemmer om objekter av BruktTing klassen
 * 
 * @see NyTing::skrivData()
*/
void BruktTing::skrivData() const {
    NyTing::skrivData();
    std::cout << "Tingens alder: " << aar 
              << "\tKvalitet: " << kvalitet << std::endl;
}

/**
 * @brief Skriver BruktTing objekter til fil
 * 
 * @param tingFil Referanse til filen som skal skrives til
 * 
 * @see NyTing::skrivTilFil(...)
*/
void BruktTing::skrivTilFil(std::ofstream &tingFil) {
    NyTing::skrivTilFil(tingFil);
    int kvalitetInt = 0;

    switch (kvalitet) {
        case SomNy:     kvalitetInt = 1; break; 
        case PentBrukt: kvalitetInt = 2; break; 
        case Brukt:     kvalitetInt = 3; break; 
        case GodtBrukt: kvalitetInt = 4; break; 
        case Sliten:    kvalitetInt = 5; break;
    }

    tingFil << aar << ' ' << kvalitetInt << '\n';
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

    switch (kvalitetInt) {
        case 1:   kvalitet = SomNy;       break;
        case 2:   kvalitet = PentBrukt;   break;
        case 3:   kvalitet = Brukt;       break;
        case 4:   kvalitet = GodtBrukt;   break;
        case 5:   kvalitet = Sliten;      break;
    }

    NyTing::settRestData(tingFil);
}