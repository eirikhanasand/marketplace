/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "Kategorier.h"

/**
 *  todo
*/
class Kategorier {

    public:
        // Constructor
        Kategorier() {

        };

        // Destructor
        ~Kategorier(){

        };

        // Håndterer valg
        void handling(char valg) {

        };

        // Leser fra fil
        void lesFraFil() {
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
    void skrivTilFil(){
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

};