/**
 *  Defines functions of the UsedItem class
 *
 *  @file      newItem.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "categories.hpp"
#include "usedItem.hpp"
#include "category.hpp"
#include "readData.hpp"
#include "newItem.hpp"
#include "customers.hpp"
#include "const.hpp"

extern Customers gCustomerBase;
extern Categories gCategoryBase;

/**
 * @brief NewItem constructor
 *
 * Creates item based on number and sets the number of the item to this number.
 * 
 * @param Number Number of the item
*/
NewItem::NewItem(int Number) {
    number = Number;
}

/**
 * @brief Destructor for NewItem.
 *
 * Empty (default), but necesarry for the compiler
*/
NewItem::~NewItem() {

}

/**
 * @brief Sets all datamebmers of a NewItem
 * 
 * @see readInt(...)
 * @see readString(...)
 * @see Customers::getCustomer(...)
 * @see Customers::lastCustomer()
*/
void NewItem::setData() {
    int tempSeller;
    Customer* customer;

    do {
        tempSeller = readInt("Customer number", 1, gCustomerBase.lastCustomer())-1;
        customer = gCustomerBase.getCustomer(tempSeller);

        if (!customer) {
            std::cout << "This customer has been deleted. Use the command AA"
            " to view the customer list.\n";
        }
    } while (!customer);

    sellerNumber = tempSeller;
    name = readString("Name the item");
    description = readString("Describe the item");
    price = readInt("How much does it cost", 0, MAX_PRICE);
    count = readInt("How many are you selling", 1, MAX_ITEMS);
}

/**
 * @brief Writes all data of a NewItem
*/
void NewItem::writeData() const {
    std::cout << "Seller " << sellerNumber+1
              << "\tItem number: " << number
              << "\tName: " << name
              << "\tCount: " << count
              << "\tPrice: " << price
              << "kr\tDescription: " << description << '\n';
}

/**
 * @brief Writes all data of a NewItem except its seller number.
*/
void NewItem::writeLessData() const {
    std::cout << "Item number: " << number
              << "\tName: " << name
              << "\tCount: " << count
              << "\tPrice: " << price
              << "kr\tDescription: " << description << '\n';
}

/**
 * @brief Gets the name of a NewItem
 * 
 * @returns std::string Name of the item
 */
std::string NewItem::getName() const {
    return name;
}

/**
 * @brief Gets the count of a NewItem
 * 
 * @returns int Item count
 */
int NewItem::getCount() const {
    return count;
}

/**
 * @brief Edits count of a NewItem
 * 
 * @param newCount New count of the item
*/
void NewItem::editCount(int newCount) {
    count = newCount;
}

/**
 * @brief Gets count of a NewItem
 * 
 * @return int number
*/
int NewItem::getNumber() const {
    return number;
}

/**
 * @brief Gets seller number of a NewItem
 * 
 * @return int sellerNumber
*/
int NewItem::getSellerNumber() const {
    return sellerNumber;
}

/**
 * @brief Function to edit the data members of NewItem.
 *
 * First writes menu to decide which data member to change, then references to 
 * the relevant function that can perform the change.
 * 
 * @see readInt(...)
 * @see readString(...)
 * @see NewItem::editName(...)
 * @see NewItem::editCount(...)
 * @see NewItem::editPrice(...)
 * @see NewItem::editDescription(...)
*/
void NewItem::editItem() {
    std::cout << "What would you like to edit?\n1. Name\n2. Count\n3. Price\n4. "
    "Description\n5. Cancel / UsedItem\n";

    int choice = readInt("Item", 1, 5);

    switch (choice) {
        case 1: {
            name = readString("New name");
            break;
        }
        case 2: {
            count = readInt("New count", 1, MAX_ITEMS);
            break;
        }
        case 3: {
            price = readInt("New price", 1, MAX_PRICE);
            break;
        }
        case 4: {
            description = readString("New description");
            break;
        }
    }
}

/**
 * @brief Constructor for item to set the item data based on the content read
 * from attached file
 * 
 * @param itemFile File to read item from
 * 
 * @see NewItem:::setData()
*/
NewItem::NewItem(std::ifstream &itemFile) {
    setData(itemFile);
} 

/**
 * @brief Writes integer data members to file
 * 
 * Writes sellerNumber, item number, price and count to file.
 * 
 * @param itemFile File to write to
*/
void NewItem::writeToFile(std::ofstream &itemFile) const {
    int intIsUsed = isUsed ? 1:0;

    itemFile << intIsUsed <<  ' '
            << sellerNumber << ' '
            << number << ' '
            << price << ' '
            << count;
}

/**
 * @brief Writes all data of a given item to file.
 * 
 * @param itemFile File to write the item to
*/
void NewItem::writeRestDataToFile(std::ofstream &itemFile) {
    itemFile  << '\n' << name << '\n' << description << '\n';
}

/**
 * @brief Sets data of item
 * 
 * Sets sellerNumber, item number, price and count based on what was read from
 * file.
 * 
 * @param itemFile File to read from
*/
void NewItem::setData(std::ifstream &itemFile) {
    itemFile >> sellerNumber;
    itemFile.ignore();
    itemFile >> number;
    itemFile.ignore();
    itemFile >> price;
    itemFile.ignore();
    itemFile >> count;
    itemFile.ignore();
}

/**
 * @brief Sets name and description of a NewItem.
 *
 * This must have its own function for UsedItem's readData to work, due to the
 * way the data members are stored on file.
 * 
 * @param itemFile File to read item variables from
*/
void NewItem::setRestData(std::ifstream &itemFile) {
    std::getline(itemFile, name);
    name[name.length()] = '\0';

    std::getline(itemFile, description);
    description[description.length()] = '\0';
}

/**
 * @brief Sets isUsed of item
 * 
 * @param status If the item used or not
*/
void NewItem::setWornStatus(bool status) {
    if (status) {
        isUsed = true;
    } else {
        isUsed = false;
    }
}
