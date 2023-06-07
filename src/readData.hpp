/**
 *  Toolkit to read chars, numbers and strings.
 *
 *
 *  @file     readData.hpp
 *  @author   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther, NTNU
 */

#ifndef __READDATA_H
#define __READDATA_H

#include <string>

const int MAXCHAR = 200;      //  Max.chars in input buffer

char readChar(const char *t);

float readFloat(const char *t, const float min, const float max);

int readInt(const char *t, const int min, const int max);

bool readBool(const char *t, const char yes = 'Y', const char no = 'N');

std::string readString(const std::string t);

std::string stringToLower(std::string t);

#endif