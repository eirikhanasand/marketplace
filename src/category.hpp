/**
 *  Definitions of functions for the UsdeItem class.
 *
 *  @file      usedItem.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __CATEGORY_H
#define __CATEGORY_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "newItem.hpp"

class Category {
 public:
    Category();    
    Category(std::ifstream &customerFile, std::string name);
    NewItem* getItem(int itemNumber) const;
    NewItem* getItemWithIndex(int index) const;
    std::string getName() const;
    int itemCount() const;
    void setData(std::string name);
    void writeData() const;
    void writeLessData() const;
    void makeItem();
    void writeItem() const;
    void writeIndexedItem() const;
    void writeToFile(std::ofstream &customerFile) const;
    void removeItem(NewItem *item);
    void removeItemWithSellerNumber(int customerNumber);
    int numberOfItems() const;

 private:
    std::list<NewItem*> itemList;
    std::string categoryName;
    int items = 0;
};

#endif