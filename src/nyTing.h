/**
 *   Headere for klassen Kunder
 *
 *   @file      Kunder.h
 *   @authors   todo
 */

#ifndef __NYTING_H
#define __NYTING_H

#include <iostream>

class NyTing {
    int nr;

    std::string navn;
    std::string beskrivelse;

    public:
        NyTing();
        ~NyTing();
};

#endif