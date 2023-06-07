/**
 *  Defines functions of the NewItem class
 *
 *  @file      newItem.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __NEWITEM_H
#define __NEWITEM_H

#include <iostream>
#include <fstream>
#include <string>

class NewItem {
 public:
    explicit NewItem(int Number);
    explicit NewItem(std::ifstream &itemFile);
    virtual ~NewItem();
    virtual void setData();
    virtual void setData(std::ifstream &itemFile);
    virtual void setRestData(std::ifstream &itemFile);
    virtual void writeData() const;
    virtual void writeLessData() const;
    virtual void writeToFile(std::ofstream &itemFile) const;
    virtual void editItem();
    std::string getName() const;
    int getNumber() const;
    int getCount() const;
    int getSellerNumber() const;
    void editCount(int nyttAntall);
    void writeRestDataToFile(std::ofstream &tingFil);
    void setWornStatus(bool status);

 private:
    int sellerNumber;
    int number;
    int price;
    int count;
    bool isUsed;

    std::string name;
    std::string description;
};

#endif