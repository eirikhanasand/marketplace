/**
 *  Definitions of functions of customers class
 *
 *  @file      customers.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>

#include "categories.hpp"
#include "writeMenu.hpp"
#include "readData.hpp"
#include "customers.hpp"
#include "customer.hpp"

extern Categories gCategoryBase;

/**
 * @brief Customers destructor
 */
Customers::~Customers() {
    for (auto &customer : customerList) {
        delete customer;
    }
}

/**
 * @brief Handles choices for customers
 *
 * Choices:
 * - Creation of new customers
 * - Printing of all customers
 * - Printing of given customer
 * - Removal of customer
 * 
 * @param choice Letter indicating the choice of the user
 * 
 * @see makeCustomer()
 * @see writeAll()
 * @see readInt(...)
 * @see getCustomer(...)
 * @see Customer::writeData(...)
 * @see removeCustomer(...)
 * @see writeMenu()
*/
void Customers::handling(char choice) {
    switch (choice) {
        case 'N': {
            makeCustomer();
            choice = 0;
            break;
        }
        case 'A': {
            if (customerList.size()) {
                writeAll();
            } else {
                std::cout << "There are no customers to write.\n";
            }
            choice = 0;
            break;
        }
        case 'S': {
            if (customerList.size()) {
                if (lastCustomerCount) {
                    int customerNumber =
                        readInt("Customer number", 1, lastCustomerCount)-1;
                    Customer *customer = getCustomer(customerNumber);
                    if (customer) {
                        customer->writeData();
                    } else {
                        std::cout << "Customer number " << customerNumber+1
                                << " has been deleted.\n";
                    }
                } else {
                    std::cout << "There are no customers, therefore can not "
                    "write given customer.\n";
                }
                choice = 0;
            } else {
                std::cout << "There are no customers to write.\n";
            }
            break;
        }
        case 'F': {
            if (customerList.size()) {
                if (lastCustomerCount) {
                    int customerNumber =
                            readInt("Customer number:", 1, lastCustomerCount)-1;

                    if (getCustomer(customerNumber)) {
                        removeCustomer(customerNumber);
                    } else {
                        std::cout << "Customer number " << customerNumber+1
                                << " has been deleted.\n";
                    }
                } else {
                    std::cout << "There are no customers to delete.\n";
                }
                choice = 0;
            } else {
                std::cout << "There are no customers to delete.\n";
            }
            break;
        }
        default: {
            std::cout << "Invalid command!\n";
            writeMenu();
            break;
        }
    }
}

/**
 * @brief Writes customers from file.
 *
 * Afterwards creates these as objects, and puts them at the back of the
 * customer list.
 * 
 * @see Customer::Customer(...)
*/
void Customers::readFromFile() {
    int customerNumber = 0;
    std::ifstream customerFile("../data/CUSTOMERS.DTA");

    if (customerFile) {
        std::cout << "Reading from ../data/CUSTOMERS.DTA\n";

        while (!customerFile.eof()) {
            customerNumber = 0;
            customerFile >> customerNumber;
            if (customerNumber) {
                customerFile.ignore();
                customerList.push_back(new Customer(customerFile, customerNumber-1));
                lastCustomerCount++;   
            }
        }

        if (lastCustomerCount) {
            std::cout << "Read " << lastCustomerCount << " customers from "
                     "file ../data/CUSTOMERS.DTA\n";
        } else {
            std::cout << "Customer file is empty!\n";
        }
    } else {
        std::cout << "Could not read from ../data/KUNDER.DTA.\n";
    }

    customerFile.close();
}

/**
 * @brief Writes all customers to file
 * 
 * @see Customer::writeToFile(...)
*/
void Customers::writeAllToFile() const {
    if (getCustomerCount()) {
        std::ofstream customerFile("../data/CUSTOMERS.DTA");

        if (customerFile) {
            std::cout << "Writing to ../data/CUSTOMERS.DTA\n";

            for (const auto &customer : customerList) {
                customer->writeToFile(customerFile);
            }
        } else {
            std::cout << "Could not write to ../data/CUSTOMERS.DTA.\n";
        }

        customerFile.close();
    } else {
        std::cout << "There are no customers to write to file.\n";
    }
}

/**
 * @brief Deletes customer
 * 
 * Based on customernumber. ALl info about the customer is printed, and the user
 * then needs to confirm the deletion.
 * 
 * @param customerNumber Number of the customer to delete
 * 
 * @see Customers::getCustomer(...)
 * @see Customer::writeData()
 * @see Categories::removeAllItemsBelongingToCustomer()
 * @see Customer::getCustomerNumber()
 * @see readChar(...)
 * @see Customer::~Customer()
*/
void Customers::removeCustomer(int customerNumber) {
    char confirmation;
    auto customer = getCustomer(customerNumber);

    if (customer) {
        customer->writeData();
        confirmation = readChar("Do you really want to delete this customer? (y/N)");
        if (confirmation == 'Y') {
            gCategoryBase.removeAllItemsBelongingToCustomer(customer->getCustomerNumber());
            customerList.remove(customer);
            customer->~Customer();
            std::cout << "Customer was deleted.\n";
        } else {
            std::cout << "Cancelled deletion.\n";
        }
    } else {
        std::cout << "Customer does not exist.\n";
    }
}

/**
 * Gets customer with given customer number.
 * 
 * @param customerNumber Number of customer to get
 * 
 * @see getCustomerNumber()
 * 
 * @return Customer pointer, or nullptr if not found.
*/
Customer *Customers::getCustomer(int customerNumber) const {
    auto element = std::find_if(customerList.begin(), customerList.end(),
        [customerNumber](Customer *customer){
        return customer->getCustomerNumber() == customerNumber;
    });
    return (element != customerList.end()) ? *element : nullptr;
}

/**
 * @brief Writes all customers.
 *
 * User needs to confirm that they wish to print more every 20 customers.
 * 
 * @see Customer::writeInfo()
 * @see readBool(...)
*/
void Customers::writeAll() const {
    int i = 0;
    bool choice;

    std::cout << "Last customer: " << lastCustomerCount << ". There are now "
              << customerList.size() << " customers.\n";

    for (const auto &customer : customerList) {
        if (i && i % 20 == 0) {
            choice = readBool("Write 20 more customers? y/N");
            if (!choice) break;
        }
        customer->writeInfo();
        i++;
    }
}

/**
 * @brief Returns current amount of customers
 * 
 * @return int Amount of customers
*/
int Customers::lastCustomer() const {
    return lastCustomerCount;
}

/**
 * @brief Creates new customer.
 *
 * Afterwards sets all its datamembers and adds it to the customer list.
 * 
 * @see Customer::Customer(...)
 * @see Customer::writeInfo()
*/
void Customers::makeCustomer() {
    Customer *customer = new Customer(lastCustomerCount);
    customerList.push_back(customer);
    std::cout << "Created customer with ";
    customer->writeInfo();
    lastCustomerCount++;
}

/**
 * @brief Gets number of customers that actually exists
 * 
 * @return int Customer count
*/
int Customers::getCustomerCount() const {
    return customerList.size();
}
