/**
 *  Definitions of functions for the Category class.
 *
 *  @file      category.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include "category.hpp"
#include "categories.hpp"
#include "readData.hpp"
#include "usedItem.hpp"

extern Categories gCategoryBase;
/**
 * @brief Constructor for category.
 *
 * Empty constructor necesarry for the compiler.
*/
Category::Category() {
}

/**
 * @brief Sets name and amount for sale of a item in a category.
 * 
 * @param name Name of the category
*/
void Category::setData(std::string name) {
    categoryName = name;
    items = 0;
}

/**
 * @brief Writes name and items for sale of a category.
*/
void Category::writeData() const {
    std::cout << "Categoryname: " << categoryName
              << "\tAmount for sale: " << itemList.size() << '\n';
}

/**
 * @brief Returns name of category
 * 
 * @return std::string categoryName
*/
std::string Category::getName() const {
    return categoryName;
}

/**
 * @brief Gets item in category with a specific itemnumber.
 *
 * Checks the list and finds matching element that are returned, or nullptr.
 * 
 * @param itemNumber The number of the item
 * 
 * @return NewItem points to found item, or nullptr.
*/
NewItem* Category::getItem(int itemNumber) const {
    auto element = std::find_if(itemList.begin(), itemList.end(),
        [itemNumber](NewItem *item){
        return item->getNumber() == itemNumber;
    });
    return (element != itemList.end()) ? *element : nullptr;
}

/**
 * @brief Gets item of given index.
 * 
 * @param index Index of the item to get.
 * 
 * @returns NewItem points to item, or nullptr.
*/
NewItem* Category::getItemWithIndex(int index) const {
    int itemIndex = 1;
    for (const auto &item : itemList) {
        if (itemIndex == index) {
            return item;
        }
        itemIndex++;
    }
    return nullptr;
}


/**
 * @brief Creates new item of category.
 *
 * Decides wether to put item in the NewItem or UsedItem class. Then sets data
 * of the item, and puts it at the back of the list.
 * Finally increases number of items for sale.
 * 
 * @see readBool(...)
 * @see usedItem(...)
 * @see NewItem(...)
 * @see NewItem::setData()
 * @see Categories::increaseAmountOfItems()
 * @see Categories::getAmountOfItems()
*/
void Category::makeItem() {
    bool used = readBool("Used (y/n)");
    NewItem* item = nullptr;

    if (used) {
        item = new UsedItem(gCategoryBase.getItemCount()+1);
    } else {
        item = new NewItem(gCategoryBase.getItemCount()+1);
    }

    item->setData();
    itemList.push_back(item);
    items++;
    gCategoryBase.increaseItemCount();
}

/**
 * @brief Gets amount of items in a category
 * 
 * @return int Number of items in that category
*/
int Category::itemCount() const {
    return items;
}

/**
 * @brief Writes all info available for an item of a given category.
 * 
 * @see NewItem::writeData()
*/
void Category::writeItem() const {
    for (const auto &item : itemList) {
        item->writeData();
    }
}
/**
 * @brief Writes all info of a item of a given category with index.
 *
 * @see NewItem::writeData()
*/
void Category::writeIndexedItem() const {
    int index = 1;
    for (const auto &item : itemList) {
        std::cout << "[" << index << "] ";
        item->writeData();
        index++;
    }
}

/**
 * @brief Writes everything except sellerNumber of all items of a cagtegory.
 * 
 * @see NewItem::writeLessData()
*/
void Category::writeLessData() const {
    for (const auto &item : itemList) {
        item->writeLessData();
    }
}

/**
 * @brief Writes a category and all items of it to file.
 * 
 * @param customerFile File to write to
 * 
 * @see NewItem::writeToFile(...)
 * @see NewItem::writeRestDataToFile(...)
*/
void Category::writeToFile(std::ofstream &customerFile) const {
    customerFile << categoryName << '\n' << items << '\n';

    for (const auto &item : itemList) {
        item->writeToFile(customerFile);
        item->writeRestDataToFile(customerFile);
    }
}

/**
 * @brief Number of items in the itemlist.
 *
 * @return Number of items in the list.
 */
int Category::numberOfItems() const {
    return itemList.size();
}


/**
 * @brief Category constructor with file params to make categories from file.
 * 
 * @param infile File to read from
 * @param name Name of the category
 * 
 * @see NewItem::NewItem(...)
 * @see UsedItem::UsedItem(...)
 * @see NewItem::setRestData(...)
 * @see NewItem::setWornStatus(...)
 * @see Category::increaseAmountOfItems()
*/
Category::Category(std::ifstream &infile, std::string name) {
    int type;

    categoryName = name;

    infile >> items;
    infile.ignore();

    for (int i = 0; i < itemCount(); i++) {
        type = 0;
        infile >> type;
        infile.ignore();

        if (type) {
            UsedItem *usedItem = new UsedItem(infile);
            usedItem->setWornStatus(true);
            itemList.push_back(usedItem);
            gCategoryBase.increaseItemCount();
        } else {
            NewItem *newItem = new NewItem(infile);
            newItem->setWornStatus(false);
            newItem->setRestData(infile);
            itemList.push_back(newItem);
            gCategoryBase.increaseItemCount();
        }
    }
}

/**
 * @brief Removes given item from itemlist
 * 
 * @param item Item to remove
*/
void Category::removeItem(NewItem *item) {
    itemList.remove(item);
}

/**
 * @brief Removes item with given customerNumber
 * 
 * @param customerNumber Sellernumber of the items to remove.
 * 
 * @see getSellerNumber()
*/
void Category::removeItemWithSellerNumber(int customerNumber) {
    itemList.erase(
        std::remove_if(itemList.begin(), itemList.end(), 
        [&](const auto &item) {
            if (item->getSellerNumber() == customerNumber) {
                delete item;
                return true;
            } else {
                return false;
            }
        }), itemList.end()
    );
}