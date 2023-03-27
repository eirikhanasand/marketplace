/**
 *   Skriver programmets hovedmeny
 *
 *   @file      skrivMeny.cpp
 *   @authors   todo
 */

#include <iostream>
#include "skrivMeny.h"

/**
 *  Skriver programmets hovedmeny
*/
void skrivMeny() {
    std::cout << "Meny" << std::endl;
    std::cout << "UN - Opprett ny kunde" << std::endl;
    std::cout << "UA - Skriv alle kunder" << std::endl;
    std::cout << "US - Skriv bestemt kunde" << std::endl;
    std::cout << "UF - Slett kunde" << std::endl;
    std::cout << "AN - Opprett kategori" << std::endl;
    std::cout << "AA - Skriv alle kategorier" << std::endl;
    std::cout << "AS - Skriv en entydig navngitt kategori" << std::endl;
    std::cout << "TN - Opprett ny ting" << std::endl;
    std::cout << "TE - Endre ting" << std::endl;
    std::cout << " K - Kjøp ting" << std::endl;
};