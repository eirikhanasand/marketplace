/**
 *  Class for used items, with functions to set data, read data, set amount of
 *  years the item has been used, and the quality of the item.
 * 
 *  @file      usedItem.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>

#include "categories.hpp"
#include "usedItem.hpp"
#include "readData.hpp"
#include "newItem.hpp"
#include "const.hpp"

/**
 * @brief Constructor for UsedItem.
 *
 * Empty constructor, needed for the compiler, as it first runs the constructor
 * of newItem.
 * 
 * @param Number The unique number of the item
 * 
 * @see NewItem(...)
*/
UsedItem::UsedItem(int Number):NewItem(Number) {

}

/**
 * @brief Constructor to read UsedItem from file.
 * 
 * @param itemFile Reference to the file to read from
 * 
 * @see NewItem(...)
 * @see setData(...) 
*/
UsedItem::UsedItem(std::ifstream &itemFile):NewItem(itemFile) {
    setData(itemFile);
}

/**
 * @brief Destructor for UsedItem.
 *
 * Empty (default), necesarry for the compiler.
*/
UsedItem::~UsedItem() {

}

/**
 * @brief Setdata function for UsedItem, to set extra data members that are not
 * in NewItem's setData.
 *
 * First calls the setData of the parent class, then sets specific data of the
 * subclass.
 * 
 * @see NewItem::setData()
 * @see readInt(...)
*/
void UsedItem::setData() {
    NewItem::setData();
    year = readInt("Age of the item", 0, MAX_AGE);
    int categoryQuality = readInt(
            "How worn is the item? 1 = AsNew, 2 = "
            "NicelyUsed, 3 = Used, 4 = WellUsed, 5 = Worn", 1, 5
    );
    quality = static_cast<Quality>(categoryQuality-1);
}

/**
 * @brief Writes all datamembers for objects of the UsedThing class.
 * 
 * @see NewItem::writeData()
*/
void UsedItem::writeData() const {
    NewItem::writeData();
    std::cout << "Age of the item: " << year << "year, quality: "
              << quality << '\n';
}

/**
 * @brief Writes everything except salesnumber of UsedItem
 * 
 * @see NewItem::writeLessData()
*/
void UsedItem::writeLessData() const {
    NewItem::writeLessData();
    std::cout << "Age of the item: " << year << "year, quality: "
              << quality << '\n';
}

/**
 * @brief Writes UsedItem objects to file
 * 
 * @param itemFile Reference to the file to write to
 * 
 * @see NewItem::writeToFile(...)
*/
void UsedItem::writeToFile(std::ofstream &itemFile) const {
    NewItem::writeToFile(itemFile);
    itemFile << ' ' << year << ' ' << static_cast<int>(quality);
}

/**
 * @brief Reads data members of UsedItem.
 *
 * Reads leftover members from the NewItem class that cannot be read before this.
 * 
 * @param itemFile Reference to the file to read from
 * 
 * @see NewItem::setRestData(...)
*/
void UsedItem::setData(std::ifstream &itemFile) {
    int qualityInt;
    
    itemFile >> year;
    itemFile.ignore();
    itemFile >> qualityInt;
    itemFile.ignore();

    quality = static_cast<Quality>(qualityInt-1);

    NewItem::setRestData(itemFile);
}

/**
 * @brief Function to edit the datamembers of UsedItem.
 *
 * First writes the menu to decide what datamember to edit, then refers to the
 * relevant function that can execute the change.
 * 
 * @see NewItem::editItem()
 * @see readInt(...)
 * @see readString(...)
*/
void UsedItem::editItem() {
    NewItem::editItem();
    int choice = readInt("1. Age\n2. Quality\n", 1, 2);
    
    switch (choice) {
        case 1: 
            year = readInt("New age", 1, MAX_AGE);
            break;
        case 2:
            int categoryQuality = readInt(
            "How worn is the item? 1 = AsNew, 2 = "
            "NicelyUsed, 3 = Used, 4 = WellUsed, 5 = Worn", 1, 5
            );
            quality = static_cast<Quality>(categoryQuality-1);
            break;
    }
}