/**
 *  Skriver programmets hovedmeny
 *
 *  @file      skrivMeny.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include "SkrivMeny.hpp"

/**
 *  Skriver programmets hovedmeny
*/
void skrivMeny() {
    std::cout << "UN - Opprett ny kunde" << '\n' << "UA - Skriv alle kunder" 
    << '\n' << "US - Skriv bestemt kunde" << '\n' << "UF - Slett kunde" << '\n' 
    << "AN - Opprett kategori" << '\n' << "AA - Skriv alle kategorier" << '\n' << "AS - Skriv en entydig navngitt kategori" 
    << '\n' << "TN - Opprett ny ting" << '\n' << "TE - Endre ting" << '\n' << " K - Kjøp ting" << std::endl;
}