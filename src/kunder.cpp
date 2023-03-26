/**
 *   todo
 *
 *   @file      kunder.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "Kunder.h"

/**
 *  todo
 */
class Kunder {

    public:
        // Constructor
        Kunder() {

        };

        // Destructor
        ~Kunder() {

        };

        // Håndterer valg
        void handling() {

        };

        // Leser fra fil
        void lesFraFil() {
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
        void skrivTilFil(){
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
};