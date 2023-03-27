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

    NyTing();
    ~NyTing();

    std::string navn;
    std::string beskrivelse;
};

#endif