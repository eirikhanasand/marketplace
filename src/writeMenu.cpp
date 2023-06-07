/**
 *  Writes the main menu of the program, and describes all choices.
 *
 *  @file      writeMenu.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>

#include "writeMenu.hpp"

/**
 *  @brief Writes main menu and describes all choices.
*/
void writeMenu() {
    std::cout << "Main menu. Write choice as AA without spaces.\n"
              << "UN - Creates new customer\n"
              << "UA - Writes all customers\n"
              << "US - Writes specific customer\n"
              << "UF - Delete customer\n"
              << "AN - Creates category\n"
              << "AA - Writes all categories\n"
              << "AS - Writes specific category\n"
              << "TN - Creates new item\n"
              << "TE - Edits item\n"
              << " K - Buys item\n";
}
