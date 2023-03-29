/**
 *   Header for klassen BruktTing
 *
 *   @file      BruktTing.h
 *   @authors   todo
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include "nyTing.h"

class BruktTing : NyTing {
public:
    // Constructor
    BruktTing();

    // Deconstructor
    ~BruktTing();

    // Leser inn data om brukt ting
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