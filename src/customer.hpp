/**
 *  Header for Customer class
 *
 *  @file      Customer.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KUNDE_H
#define __KUNDE_H

#include <fstream>
#include <string>

#include "category.hpp"

class Customer {
 public:
    explicit Customer(int CustomerNumber);
    Customer(std::ifstream &kundeFil, int CustomerNumber);
    int getCustomerNumber() const;
    void buyItem(Category *category, NewItem *item, int customerNumber);
    void sellItem(NewItem *item, Category *category);
    void setData();
    void writeData() const;
    void writeInfo() const;
    void writeToFile(std::ofstream &kundeFil) const;

 private:
    int customerNumber;
    int phone;
    int postNumber;
    int itemsBought;
    int itemsSold;
    int itemsForSale;

    std::string name;
    std::string address;
    std::string postLocation;
    std::string mail;
};

#endif