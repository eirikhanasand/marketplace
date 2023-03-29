/**
 *  Header for Kategorier klassen
 *
 *  @file      Kategorier.h
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <string>
#include <map>
#include "Kategori.hpp"
#include "Kunde.hpp"

class Kategorier {
public:
    Kategorier();

    ~Kategorier();

    void handling(char valg);

    void lesFraFil();

    void skrivTilFil();

    void nyKategori();

    bool kategoriFinnes(std::string kategoriNavn);

    void skrivAlle();

    void fjernKategori(Kategori *kategori);

    Kategori *finnKategori(std::string kategoriNavn);
    
    void lagTingIKategori();

    void kjopTing();

private:
    std::map<std::string, Kategori *> kategoriMap;
};

#endif