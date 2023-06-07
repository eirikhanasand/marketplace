/**
 *  Main menu for Object Oriented Programming project S23 with a mini marketplace
 *  system where you can buy and sell items, create and delete categories, and 
 *  keep track of customers and their statistics.
 *
 *  @file     mainS23.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <string>

#include "categories.hpp"
#include "writeMenu.hpp"
#include "readData.hpp"
#include "customers.hpp"
#include "customer.hpp"

Customers gCustomerBase;          // Global container-object with ALL customers.
Categories gCategoryBase;         // Global container-object with ALL categories.

/**
 * @brief Main menu
 * 
 * Writes all top level choices, customers and categories are read from and
 * written to file, and choices are read.
 * 
 * @see Categories::categoryHandling(...)
 * @see Categories::buyItem(...)
 * @see Categories::readFromFile()
 * @see Categories::writeAllToFile()
 * @see Categories::itemHandling(...)
 * @see Customers::handling(...)
 * @see Customers::readFromFile()
 * @see Customers::writeAllToFile()
 * @see readString(...)
 * @see writeMenu()
 * 
 * @return 0, terminates program
 */
int main() {
    std::string choice;

    gCustomerBase.readFromFile();
    gCategoryBase.readFromFile();

    writeMenu();
    
    choice = readString("\nCommand");

    char firstChoice = std::toupper(choice.at(0));

    while (choice.size() == 1 && (firstChoice != 'K' && firstChoice != 'Q')) {
        writeMenu();
        choice = readString("\nInvalid Command!");
    }

    firstChoice = std::toupper(choice.at(0));
    char secondChoice;

    while (firstChoice != 'Q') {
        switch (firstChoice) {
            std::cout << firstChoice;
            case 'U': {
                secondChoice = std::toupper(choice.at(1));
                gCustomerBase.handling(secondChoice);
                break;
            }
            case 'A': {
                secondChoice = std::toupper(choice.at(1));
                gCategoryBase.categoryHandling(secondChoice);
                break;
            }
            case 'K': {
                if (gCustomerBase.getCustomerCount()) {
                    gCategoryBase.buyItem();
                } else {
                    std::cout << "You need to create a customer to buy items!\n";
                }
                break;
            }
            case 'T': {
                if (gCustomerBase.getCustomerCount()) {
                    secondChoice = std::toupper(choice.at(1));
                    gCategoryBase.itemHandling(secondChoice);
                } else {
                    std::cout << "Create a customer before editing items!\n";
                }
                break;
            }
            default: {
                writeMenu();
                break;
            }
        }

        choice = readString("\nCommand");
        firstChoice = std::toupper(choice.at(0));

        while (choice.size() == 1 && (firstChoice != 'K' && firstChoice != 'Q')) {
            writeMenu();
            choice = readString("\nInvalid command");
        }
        firstChoice = std::toupper(choice.at(0));
    }
    
    gCustomerBase.writeAllToFile();
    gCategoryBase.writeAllToFile();

    std::cout << "All data has been saved, and the program has been terminated.\n";

    return 0;
}
