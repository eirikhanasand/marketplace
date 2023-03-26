/**
 *   todo
 *
 *   @file      kunder.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "../headers/kunder/Kunder.h"
using namespace std;

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
            ifstream kundeFil;
            kundeFil.open("../data/KUNDER.DTA");

            if (kundeFil.is_open()) {
                // les fra kundefil
            } else {
                cout << "Kunne ikke lese fra /data/KUNDER.DTA." << endl;
            };
        
            // write here
            kundeFil.close();
        };

        // Skriver til fil
        void skrivTilFil(){
            ofstream kundeFil;
            kundeFil.open("../data/KUNDER.DTA");

            if (kundeFil.is_open()) {
                // skriv til kundefil
            } else {
                cout << "Kunne ikke skrive til /data/KUNDER.DTA." << endl;
            };

            // write here
            kundeFil.close();
        };
};