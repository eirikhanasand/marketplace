/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include "../headers/kategorier/Kategorier.h"
using namespace std;

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
            ifstream kundeFil;
            kundeFil.open("../data/KATEGORIER.DTA");

        if (kundeFil.is_open()) {
            // les fra kundefil
        } else {
            cout << "Kunne ikke lese fra /data/KATEGORIER.DTA." << endl;
        };

        // write here
        kundeFil.close();
    };

    // Skriver til fil
    void skrivTilFil(){
        ofstream kundeFil;
        kundeFil.open("../data/KATEGORIER.DTA");

        if (kundeFil.is_open()) {
            // skriv til kundefil
        } else {
            cout << "Kunne ikke skrive til /data/KATEGORIER.DTA." << endl;
        };

        // write here
        kundeFil.close();
    };

};