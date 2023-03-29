/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av data.
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include "Enum.hpp"
#include "NyTing.hpp"

class BruktTing : public NyTing {
public:
    BruktTing(int Nummer);

    ~BruktTing();

    void settData();

    void skrivData();

private:
    int aar;
    Kvalitet kvalitet;
};

#endif