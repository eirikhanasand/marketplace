/**
 *  Class for used items, with functions such as set data and read data.
 * 
 *  @file      usedItem.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __USEDITEM_H
#define __USEDITEM_H

#include <iostream>
#include <fstream>

#include "enum.hpp"
#include "newItem.hpp"

class UsedItem : public NewItem {
 public:
    explicit UsedItem(int Number);
    explicit UsedItem(std::ifstream &itemFile);
    ~UsedItem();
    void setData();
    void setData(std::ifstream &itemFile);
    void writeData() const;
    void writeLessData() const;
    void writeToFile(std::ofstream &itemFile) const;
    void editItem();
 private:
    int year;
    Quality quality;
};

#endif