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
public:
    // Constructor
    NyTing();

    // Destructor
    ~NyTing();

    // Setter data
    void settData(int Nummer);

    // Kjøper en ting
    void kjopTing();

private:
    int nummer;
    int pris;
    int antall;

    std::string navn;
    std::string beskrivelse;
};

#endif