/**
 *   todo
 *
 *   @file      kunde.cpp
 *   @authors   todo
 */

#include <iostream>
#include "NyTing.h"
#include "BruktTing.h"
#include "LesData3.h"
#include "Kategorier.h"

// Constructor
BruktTing::BruktTing() {
    settData();
}

// Destructor
BruktTing::~BruktTing() {
    
}

void BruktTing::settData() {
    NyTing::settData();
    aar = lesInt("Tingens alder", 0, INT32_MAX);
    kategoriKvalitet = lesInt("Hvor sliten er tingen?", 1,5);

    switch (kategoriKvalitet) {
        case 1: kategori = SomNy;       break;
        case 2: kategori = PentBrukt;   break;
        case 3: kategori = Brukt;       break;
        case 4: kategori = GodtBrukt;   break;
        case 5: kategori = Sliten;      break;
    }
}
