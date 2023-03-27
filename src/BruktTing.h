/**
 *   Header for klassen BruktTing
 *
 *   @file      BruktTing.h
 *   @authors   todo
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include "NyTing.h"

class BruktTing : NyTing {
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