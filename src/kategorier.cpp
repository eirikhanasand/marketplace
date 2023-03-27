/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "Kategorier.h"

// Constructor
Kategorier::Kategorier() {

};

// Destructor
Kategorier::~Kategorier(){

};

// Håndterer valg
void Kategorier::handling(char valg) {

};

// Leser fra fil
void Kategorier::lesFraFil() {
    std::ifstream kundeFil;
    kundeFil.open("../data/KATEGORIER.DTA");

    if (kundeFil.is_open()) {
        // les fra kundefil
    } else {
        std::cout << "Kunne ikke lese fra /data/KATEGORIER.DTA." << std::endl;
    };

    // write here
    kundeFil.close();
};

// Skriver til fil
void Kategorier::skrivTilFil(){
    std::ofstream kundeFil;
    kundeFil.open("../data/KATEGORIER.DTA");

    if (kundeFil.is_open()) {
        // skriv til kundefil
    } else {
        std::cout << "Kunne ikke skrive til /data/KATEGORIER.DTA." << std::endl;
    };

    // write here
    kundeFil.close();
};