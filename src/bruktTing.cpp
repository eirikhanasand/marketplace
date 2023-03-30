/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av 
 *  data, setting av antall år tingen er brukt, og tingens kvalitet
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>

#include "nyTing.hpp"
#include "bruktTing.hpp"
#include "lesData3.hpp"
#include "kategorier.hpp"

// Constructor
BruktTing::BruktTing(int Nummer):NyTing(Nummer) {

}

// Destructor
BruktTing::~BruktTing() {

}

void BruktTing::settData() {
    NyTing::settData();
    aar = lesInt("Tingens alder", 0, INT32_MAX);
    int kategoriKvalitet = lesInt("Hvor sliten er tingen? 1 = SomNy, 2 = PentBrukt, 3 = Brukt, 4 = GodtBrukt, 5 = Sliten", 1, 5);

    switch (kategoriKvalitet) {
        case 1: kvalitet = SomNy;       break;
        case 2: kvalitet = PentBrukt;   break;
        case 3: kvalitet = Brukt;       break;
        case 4: kvalitet = GodtBrukt;   break;
        case 5: kvalitet = Sliten;      break;
    }
}

void BruktTing::skrivData() const {
    NyTing::skrivData();
    std::cout << "Tingens alder: " << aar << "\tKvalitet: " << kvalitet << std::endl;
}

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

BruktTing::BruktTing(std::ifstream &tingFil):NyTing(tingFil) {
    int kvalitetInt;
    // det e noe feil her pga aar og kvalitet e allerede lest inn i parent funksjonen så me får isje brukt det her // todo
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
}