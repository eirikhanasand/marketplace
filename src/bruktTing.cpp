/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av 
 *  data, setting av antall år tingen er brukt, og tingens kvalitet
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include "NyTing.hpp"
#include "BruktTing.hpp"
#include "LesData3.hpp"
#include "Kategorier.hpp"

// Constructor
BruktTing::BruktTing(int Nummer):NyTing(Nummer) {
    BruktTing::settData();
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
    };
}
