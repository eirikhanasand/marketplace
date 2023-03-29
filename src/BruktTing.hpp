/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av data.
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include <fstream>

#include "Enum.hpp"
#include "NyTing.hpp"

class BruktTing : NyTing {
public:
    BruktTing(int Nummer);
    BruktTing(std::ifstream &tingFil);

    ~BruktTing();

    void settData();

    void skrivData();

    void skrivTilFil(std::ofstream &tingFil);

private:
    int aar;
    Kvalitet kvalitet;
};

#endif