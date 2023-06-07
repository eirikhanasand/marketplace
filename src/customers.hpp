/**
 *  Header for Customers class
 *
 *  @file      customers.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __CUSTOMERS_H
#define __CUSTOMERS_H

#include <iostream>
#include <list>

#include "customer.hpp"

class Customers {
 public:
    ~Customers();
    Customer *getCustomer(int customerNumber) const;
    int lastCustomer() const;
    void removeCustomer(int customerNumber);
    void handling(char choice);
    void makeCustomer();
    void readFromFile();
    void writeAll() const;
    void writeAllToFile() const;
    int getCustomerCount() const;

 private:
    std::list<Customer *> customerList;
    int lastCustomerCount = 0;
};

#endif