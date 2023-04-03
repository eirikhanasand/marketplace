/**
 *  Skriver programmets hovedmeny og beskriver alle valgmuligheter
 *
 *  @file      skrivMeny.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>

#include "skrivMeny.hpp"

/**
 *  @brief Skriver programmets hovedmeny og beskriver alle valgmuligheter
*/
void skrivMeny() {
    std::cout << "Programmets hovedmeny. Skriv inn som AA uten mellomrom\n"
              << "UN - Opprett ny kunde\n"
              << "UA - Skriv alle kunder\n"
              << "US - Skriv bestemt kunde\n"
              << "UF - Slett kunde\n"
              << "AN - Opprett kategori\n"
              << "AA - Skriv alle kategorier\n"
              << "AS - Skriv en entydig navngitt kategori\n"
              << "TN - Opprett ny ting\n"
              << "TE - Endre ting\n"
              << " K - Kjøp ting\n";
}
