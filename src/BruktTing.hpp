/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av data.
 * 
 *  @file      bruktTing.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include "NyTing.hpp"

class BruktTing : NyTing {
public:
    BruktTing();

    ~BruktTing();

    void settData();

private:
    int aar;

    enum kvalitet {
        SomNy,
        PentBrukt,
        Brukt,
        GodtBrukt,
        Sliten
    };
};

#endif