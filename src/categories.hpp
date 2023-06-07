/**
 *  Header for Categories class
 *
 *  @file      Categories.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __CATEGORIES_H
#define __CATEGORIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "category.hpp"
#include "customer.hpp"

class Categories {
 public:
    ~Categories();
    Category *getSpecificCategory(std::string categoryName) const;
    bool categoryExists(std::string categoryName) const;
    int getItemCount() const;
    int categoryCount() const;
    void categoryHandling(char choice);
    void itemHandling(char choice);
    void readFromFile();
    void makeCategory();
    void makeItemInCategory();
    void editItemInCategory();
    void writeAllToFile();
    void writeAll() const;
    void writeSpecified() const;
    void removeCategory(Category *category);
    void buyItem();
    void increaseItemCount();
    void removeAllItemsBelongingToCustomer(int customerNumber);

 private:
    std::map<std::string, Category *> categoryMap;
    int itemCount = 0;
};

#endif