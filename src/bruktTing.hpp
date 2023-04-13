/**
 *  Klasse for brukte ting, med funksjoner som setting av data, lesing av data.
 * 
 *  @file      bruktTing.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __BRUKTTING_H
#define __BRUKTTING_H

#include <iostream>
#include <fstream>

#include "enum.hpp"
#include "nyTing.hpp"

class BruktTing : public NyTing {
 public:
    explicit BruktTing(int Nummer);
    explicit BruktTing(std::ifstream &tingFil);
    ~BruktTing();
    void settData();
    void settData(std::ifstream &tingFil);
    void skrivData() const;
    void skrivMindreData() const;
    void skrivTilFil(std::ofstream &tingFil) const;
    void endreTing();
 private:
    int aar;
    Kvalitet kvalitet;
};

#endif