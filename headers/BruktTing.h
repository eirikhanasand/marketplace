/**
 *   Header for klassen BruktTing
 *
 *   @file      BruktTing.h
 *   @authors   todo
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include "NyTing.h"
#include <iostream>

struct BruktTing : NyTing {
    int år;
    
    enum kvalitet {
        SomNy,
        PentBrukt,
        Brukt,
        GodtBrukt,
        Sliten
    };
};

#endif