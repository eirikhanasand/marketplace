/**
 *  Defintion of functions of the Customer class
 *
 *  @file      customer.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "categories.hpp"
#include "readData.hpp"
#include "customers.hpp"
#include "newItem.hpp"
#include "customer.hpp"

extern Customers gCustomerBase;
extern Categories gCategoryBase;

/**
 * @brief Customer constructor with customer number parameter.
 *
 * Also sets all data members.
 * 
 * @param CustomerNumber Customer number of the customer to create.
 * 
 * @see Customer::setData()
*/
Customer::Customer(int CustomerNumber) {
    customerNumber = CustomerNumber;
    setData();
}

/**
 * @brief Customer constructor with parameters to create customer from file
 * 
 * @param customerFile File to read from
 * @param CustomerNumber Customer number of the customer
*/
Customer::Customer(std::ifstream &customerFile, int CustomerNumber) {
    customerNumber = CustomerNumber;

    customerFile >> phone;
    customerFile.ignore();

    customerFile >> postNumber;
    customerFile.ignore();

    customerFile >> itemsBought;
    customerFile.ignore();

    customerFile >> itemsSold;
    customerFile.ignore();

    customerFile >> itemsForSale;
    customerFile.ignore();

    std::getline(customerFile, name);
    name[name.length()] = '\0';

    std::getline(customerFile, address);
    address[address.length()] = '\0';

    std::getline(customerFile, postLocation);
    postLocation[postLocation.length()] = '\0';

    std::getline(customerFile, mail);
    mail[mail.length()] = '\0';
}

/**
 * @brief Sets all data members for a given customer
 * 
 * @see readString(...)
 * @see readInt(...)
*/
void Customer::setData() {
    name = readString("Name");
    address = readString("Address");
    phone = readInt("Phone", 40000000, 99999999);
    mail = readString("Mail");
    postLocation = readString("Postlocation");
    postNumber = readInt("Postnumber", 0, 9999);

    itemsBought = 0;
    itemsSold = 0;
    itemsForSale = 0;
}

/**
 * @brief Gets customer number of given customer number
 * 
 * @return int customerNumber Customer number
*/
int Customer::getCustomerNumber() const {
    return customerNumber;
}

/**
 * @brief Writes all data for customer.
*/
void Customer::writeData() const {
    std::cout << "Name: " << name
              << "\nAddress: " << address
              << "\nPhone: " << phone
              << "\nMail: " << mail
              << "\nPost location: " << postLocation
              << "\nPostnumber: " << postNumber
              << "\nItems bought: " << itemsBought
              << "\nItems sold: " << itemsSold
              << "\nItems for sale: " << itemsForSale << '\n';
}

/**
 * @brief Writes basisinfo for customer.
 * 
 * This includes customer number, name and phone number.
*/
void Customer::writeInfo() const {
    std::cout << "Customer number: " << customerNumber+1
              << "\tName: " << name
              << "\nPhone: " << phone << '\n';
}

/**
 * @brief Writes given customer ot file.
 * 
 * @param customerFile File to write customer to
*/
void Customer::writeToFile(std::ofstream &customerFile) const {
    customerFile << customerNumber+1 << ' '
             << phone << ' '
             << postNumber << ' '
             << itemsBought << ' '
             << itemsSold << ' '
             << itemsForSale << '\n'
             << name << '\n'
             << address << '\n'
             << postLocation << '\n'
             << mail << '\n';
}

/**
 * @brief Function to let customers buy items from category
 * 
 * @param category Pointer to relevant category
 * @param item Pointer to relevant item
 * @param customerNumber Customer number to buyer 
 * 
 * @see NewItem::getSellerNumber()
 * @see NewItem::getName()
 * @see Customers::getCustomer(...)
 * @see sellItem(...)
*/
void Customer::buyItem(Category *category, NewItem *item, int customerNumber) {
    int sellerNumber = item->getSellerNumber();
    Customer* seller = gCustomerBase.getCustomer(sellerNumber);

    if (customerNumber != sellerNumber) {
        std::cout << "Bought " << item->getName() << '\n';
        seller->sellItem(item, category);
        itemsBought+=1;
    } else {
        std::cout << "You can not buy from yourself!\n";
    }
}

/**
 * @brief Sels item
 * 
 * Function to let customer sell item in category. Increases items sold, lowers
 * item count for sale, and edits count left of the item, or removes the item. 
 * tingen.
 * 
 * @param item Item to sell
 * @param category Category item belongs to
 * 
 * @see NewItem::getCount()
 * @see NewItem::editCount(...)
 * @see NewItem::removeItem(...)
*/
void Customer::sellItem(NewItem *item, Category *category) {
    int count = item->getCount();
    itemsSold++;
    itemsForSale--;

    if (count > 1) {
        item->editCount(count-1);
    } else {
        category->removeItem(item);
    }
}