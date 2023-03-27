/**
 *   todo
 *
 *   @file      kunder.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "Kunder.h"

// Constructor
Kunder :: Kunder() {

};

// Destructor
Kunder :: ~Kunder() {

};

// Håndterer valg
void Kunder ::  handling() {

};

// Leser fra fil
void Kunder ::  lesFraFil() {
    std::ifstream kundeFil;
    kundeFil.open("../data/KUNDER.DTA");

    if (kundeFil.is_open()) {
        // les fra kundefil
    } else {
        std::cout << "Kunne ikke lese fra /data/KUNDER.DTA." << std::endl;
    };
        
    // write here
    kundeFil.close();
};

// Skriver til fil
void Kunder :: skrivTilFil(){
    std::ofstream kundeFil;
    kundeFil.open("../data/KUNDER.DTA");

    if (kundeFil.is_open()) {
        // skriv til kundefil
    } else {
        std::cout << "Kunne ikke skrive til /data/KUNDER.DTA." << std::endl;
    };

    // write here
    kundeFil.close();
};