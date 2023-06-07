/**
 *  Toolkit to read chars, numbers and strings.
 *
 *  @file     readData.cpp
 *  @author   Eirik Hanasand, Sindre Hagen Strømdal, 
 *            Steffen Ludviksen Sæther, NTNU.
 */

#include <algorithm>                //  transform
#include <iostream>                 //  cin, cout
#include <iomanip>                  //  setprecision
#include <cstdlib>                  //  atoi, atof
#include <cctype>                   //  toupper
#include <string>                   //  string

#include "readData.hpp"             //  Prototypes for the contents of this file

/**
 *  @brief Reads and returns uppercase char.
 *
 *  @param   t  - Lead text for user when asked for a char
 *
 *  @return  One (uppercase) char.
 */
char readChar(const char *t) {
    char c;
    std::cout << t << ":  ";
    std::cin >> c;
    std::cin.ignore(MAXCHAR, '\n');
    return (toupper(c));
}

/**
 *  @brief Reads and returns float between given limits.
 *
 *  @param   t    - Lead text for the user
 *  @param   min  - Lower limit to accept
 *  @param   max  - Higher limit to accept
 *
 *  @return  Accepted value between given limits
 */
float readFloat(const char *t, const float min, const float max) {
    char buffer[MAXCHAR] = "";
    float num = 0.0F;
    bool error = false;

    do {
        error = false;
        std::cout << std::fixed << std::showpoint << std::setprecision(2);
        std::cout << t << " (" << min << " - " << max << "):  ";
        std::cin.getline(buffer, MAXCHAR);
        num = static_cast <float> (atof(buffer));
        if (num == 0 && buffer[0] != '0') {
            error = true;
            std::cout << "\nERROR: Not a float\n\n";
        }
    } while (error || num < min || num > max);

    return num;
}

/**
 *  @brief Reads and returns integer between given limits.
 *
 *  @param   t    - Lead text for the user
 *  @param   min  - Lower limit to accept
 *  @param   max  - Higher limit to accept
 *
 *  @return  Accepted value between given limits
 */
int readInt(const char *t, const int min, const int max) {
    char buffer[MAXCHAR] = "";
    int num = 0;
    bool error = false;

    do {
        error = false;
        std::cout << t << " (" << min << " - " << max << "):  ";
        std::cin.getline(buffer, MAXCHAR);
        num = atoi(buffer);
        if (num == 0 && buffer[0] != '0') {
            error = true;
            std::cout << "\nERROR: Not an integer\n\n";
        }
    } while (error || num < min || num > max);

    return num;
}

/**
 * @brief Reads and returns bool.
 *
 *  @param   t   - Lead text for the user
 *  @param   yes  - Letter signaling a yes (true)
 *  @param   no - Letter signaling a no (false)
 * 
 * @see readChar(...)
 *
 *  @return True or false based on user input
 */
bool readBool(const char *t, const char yes, const char no) {
    bool answer = false;
    bool error = false;
    
    do {
        error = false;
        std::cout << t;
        char answerChar = readChar("");

        if (answerChar != yes && answerChar != no) {
            error = true;
            std::cout << "\nERROR: Invalid character\n\n";
        } else {
            error = answerChar == yes;
        }
    } while (error);

    return answer;
}

/**
 *  @brief Reads and returns line
 *
 *  @param   t - Lead text for the user
 *
 *  @return  string
 */
std::string readString(const std::string t) {
    std::string string;
    do {
        std::cout << t << ":\n";
        std::getline(std::cin, string);
        if (!string.length()) {
            std::cout << "\nERROR: Empty string\n\n";
        }
    } while (!string.length());
    return string;
}

/**
 * @brief Converts text to lowercase
 * 
 * @param t Text to convert
 * 
 * @returns string lowercase text
*/
std::string stringToLower(std::string t) {
    std::transform(t.begin(), t.end(), t.begin(), tolower);
    return t;
}
