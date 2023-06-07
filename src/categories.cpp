/**
 *  Definitions of functions in the Category class.
 *
 *  @file      categories.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "customers.hpp"
#include "categories.hpp"
#include "category.hpp"
#include "readData.hpp"
#include "writeMenu.hpp"

extern Customers gCustomerBase;

/**
 * @brief Deconstructor for categories
 *
 * First deletes every category, then the categoryMap itself.
*/
Categories::~Categories() {
    for (auto &[name, data] : categoryMap) {
        delete data;
    }
    categoryMap.clear();
}

/**
 * @brief Writes choices for item.
 * 
 * @param item Choice the user wants to take
 * 
 * @see makeItemInCategory()
 * @see editItemInCategory()
 * @see writeItem()
*/
void Categories::itemHandling(char item) {
    switch (item) {
        case 'N': makeItemInCategory();     break;
        case 'E': editItemInCategory();     break;
        default:  writeMenu();              break;
    }
}

/**
 * @brief Handles choices for categories.
 *
 * Item choices:
 * - New item in category
 * - Write all items of category
 * - Write specific category
 * - Write main menu
 * 
 * @param choice Choice the user wants to perform
 * 
 * @see Categories::makeCategory()
 * @see Categories::writeAll()
 * @see Categories::writeSpecified()
 * @see writeMenu()
*/
void Categories::categoryHandling(char choice) {
    switch (choice) {
        case 'N': {
            makeCategory();
            break;
        }
        case 'A': {
            writeAll();
            break;
        }
        case 'S': {
            writeSpecified();
            break;
        }
        default: {
            writeMenu();
            break;
        }
    }
}

/**
 * @brief Reads all categories and their given items from file.
 * 
 * @see Category::Category(...)
 * @see Category::getName()
 * @see numberOfCategories()
*/
void Categories::readFromFile() {
    std::ifstream categoryFile("../data/CATEGORIES.DTA");
    std::string name;

    if (categoryFile) {
        std::cout << "Reads from file CATEGORIES.DTA\n";

        while (!categoryFile.eof()) {
            std::getline(categoryFile, name);

            if (name.length()) {
                name[name.length()] = '\0';
                Category *category = new Category(categoryFile, name);
                // Adds category to map, with name as identifier.
                categoryMap[category->getName()] = category;
            }
        }

        if (categoryCount()) {
            std::cout << "Read " << categoryCount() 
                  << " categories from CATEGORIES.DTA\n";
        } else {
            std::cout << "Categoryfile is empty!\n";
        }
    } else {
        std::cout << "Could not read from ../data/CATEGORIES.DTA.\n";
    }

    categoryFile.close();
}

/**
 * @brief Creates new category if it does not already exist.
 * 
 * @see readString(...)
 * @see categoryExists(...)
 * @see Category::setData(...)
 * @see Category::getName()
*/
void Categories::makeCategory() {
    std::string categoryName = readString("Category name");

    if (!categoryExists(categoryName)) {
        Category *category = new Category();
        category->setData(categoryName);

        // Adds category to map
        categoryMap[categoryName] = category;

        std::cout << "Created category " << category->getName() << ".\n";
    } else {
        std::cout << "This category already exists.\n";
    }
}

/**
 * @brief Checks if there exists a category with a given name
 * 
 * @param categoryName Name of the category
 * 
 * @return true if found, otherwise false
*/
bool Categories::categoryExists(std::string categoryName) const {
    return categoryMap.count(categoryName);
}

/**
 * @brief Removes a given category.
 * 
 * @param category Pointer to the category to delete.
 * 
 * @see Category::getName()
*/
void Categories::removeCategory(Category *category) {
    auto result = categoryMap.find(category->getName());
    categoryMap.erase(result);
    delete category;
}

/**
 * @brief Writes all categories.
 * 
 * @see Category::writeData()
 * @see Category::writeItem()
 * @see numberOfCategories()
*/
void Categories::writeAll() const {
    if (categoryCount()) {
        for (const auto &[name, data] : categoryMap) {
            data->writeData();
        }
    } else {
        std::cout << "There are no categories to write.\n";
    }
}

/**
 * @brief Gets named category.
 *
 * Specific we interpreted as the only category similar, or the only one it
 * could be. If there are multiple that can be seen as the right one, these will
 * be returned, and the user will have to choose the correct one.
 * 
 * @param categoryName Name of the category you want to find
 * 
 * @see stringToLower(...)
 * @see readInt(...)
 * @see categoryExists(...)
 * 
 * @return Category pointer, or nullptr
*/
Category *Categories::getSpecificCategory(std::string categoryName) const {
    Category* element = nullptr;

    if (!categoryExists(categoryName)) {
        // Vector over results
        std::vector<std::string> results;

        std::string lowerName = stringToLower(categoryName);

        // Goes through all categories
        for (auto iterator = categoryMap.begin();
                iterator != categoryMap.end();
                iterator++)
        {
            // Makes every categoryname lowercase
            std::string lowerResult = stringToLower(iterator->first);

            // Adds result to result vector
            if (lowerResult.find(lowerName) != std::string::npos) {
                results.push_back(iterator->first);
            }
        }

        if (results.size()) { // Numbers and writes all results
            for (int i = 1; i <= results.size(); i++) {
                std::cout << '[' << i << ']' << " " << results.at(i-1) << '\n';
            }
            // User is asked to choose category
            int choice = readInt("Choose category:", 1, results.size());

            // Element is set to desired category
            element = categoryMap.find(results.at(choice-1))->second;
        }
    } else {
        // Returners instantly if there are no more results
        element = categoryMap.find(categoryName)->second;
    }
    // Element is returned
    return element;
}

/**
 * @brief Creates new item of category
 * 
 * @see readString(...)
 * @see getSpecificCategory(...)
 * @see makeItem()
*/
void Categories::makeItemInCategory() {
    std::string categoryName = readString("Choose category");
    auto category = getSpecificCategory(categoryName);

    if (category) {
        category->makeItem();
    } else {
        std::cout << "There is no category with name "
                  << categoryName << '\n';
    }
}

/**
 * @brief Edits datamembers for given item of a given category.
 *
 * Otherwise errormessage if the category does not exist.
 * 
 * @see readString(...)
 * @see Categories::getSpecificCategory(...)
 * @see Category::writeData()
 * @see Category::itemCount()
 * @see Category::writeIndexedItem()
 * @see Category::getItemWithIndex()
 * @see Category::getItem(...)
 * @see Category::editItem()
*/
void Categories::editItemInCategory() {
    std::string categoryName = readString("Choose category");
    auto category = getSpecificCategory(categoryName);

    if (category) {
        category->writeData();
        category->writeIndexedItem();

        int itemIndex = readInt("Which item would you like to edit?", 1,
                                category->itemCount());
        // Edits item of found category
        auto item = category->getItemWithIndex(itemIndex);

        item->editItem();
    } else {
        std::cout << "There is no category named "
                  << categoryName << '\n';
    }
}

/**
 * @brief Buy item in category.
 *
 * First asks for customer number, then name of the category, then the numbre of
 * the item they would like to buy, or 0 to cancel the purchase. Error message
 * if the category does not exist.
 * 
 * @see readInt(...)
 * @see readString(...)
 * @see Category::writeItem(...)
 * @see Category::itemCount(...)
 * @see Category::writeIndexedItem()
 * @see Category::getItemWithIndex()
 * @see getSpecificCategory(...)
 * @see Customers::getCustomer(...)
 * @see Customers::lastCustomer(...)
 * @see Customer::buyItem(...)
*/
void Categories::buyItem() {
    int index;
    Customer* customer;
    int customerNumber;

    do {
        customerNumber = readInt("Customer number:", 1, gCustomerBase.lastCustomer())-1;
        customer = gCustomerBase.getCustomer(customerNumber);

        if (!customer) {
            std::cout << "This customer has been deleted. Please choose a" 
                         "different customer.\n";
        }
    } while (!customer);

    std::string categoryName = readString("Category");

    auto category = getSpecificCategory(categoryName);

    if (category) {
        if (category->itemCount()) {
            category->writeIndexedItem();
            index = readInt("Write the number of the item you would like to buy, 0"
            " to cancel", 0, category->itemCount());

            if (index) {
                auto item = category->getItemWithIndex(index);
                auto customer = gCustomerBase.getCustomer(customerNumber);

                customer->buyItem(category, item, customerNumber);

            } else {
                std::cout << "Cancelled purchase!\n";
            }
        } else {
            std::cout << "There are no items in this category.\n";
        }
    } else {
        std::cout << "This category does not exist!\n";
    }
}

/**
 * @brief Writes all categories and all items of each category to file.
 * 
 * @see Category::writeToFile(...)
 * @see categoryCount()
*/
void Categories::writeAllToFile() {
    // First checks if there are categories, then writes to file.
    if (categoryCount()) {
        std::ofstream categoryFile("../data/CATEGORIES.DTA");

        if (categoryFile) {
            std::cout << "Writing to file CATEGORIES.DTA\n";

            for (const auto &[name, data] : categoryMap) {
                data->writeToFile(categoryFile);
            }

            categoryFile.close();
        } else {
            std::cout << "Could not write to ../data/CATEGORIES.DTA.\n";
        }

        categoryFile.close();
    } else {
        std::cout << "There are no categories to write to file.\n";
    }
}

/**
 * @brief Writes specified category from given input.
 * 
 * @see writeString(...)
 * @see getSpecificCategory(...)
 * @see Category::writeData()
 * @see Category::writeLessData()
 * @see categoryCount()
*/
void Categories::writeSpecified() const {
    if (categoryCount()) {
        std::string categoryName = readString("Category");
        auto category = getSpecificCategory(categoryName);

        if (category) {
            category->writeData();
            category->writeLessData();
        } else {
            std::cout << categoryName << " is not a category!\n";
        }
    } else {
        std::cout << "There are no categories to write.\n";
    }
}

/**
 * @brief Increases number of items in total
*/
void Categories::increaseItemCount() {
    itemCount++;
}

/**
 * @brief Number of categories in the program
 * 
 * @return int Number of categories
 */
int Categories::categoryCount() const {
  return categoryMap.size();
}

/**
 * @brief Total number of items in the program.
 * 
 * @return int number of items
*/
int Categories::getItemCount() const {
    return itemCount;
}

/**
 * @brief Removes all items belonging to a given customer number.
 * 
 * @param customerNumber Customernumber of the items to delete
 * 
 * @see Category::removeItemWithSellerNumber(...)
*/
void Categories::removeAllItemsBelongingToCustomer(int customerNumber) {
    for (const auto &[name, data] : categoryMap) {
        data->removeItemWithSellerNumber(customerNumber);
    }
}