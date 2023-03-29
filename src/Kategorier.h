/**
 *   Header for klassen Kategorier
 *
 *   @file      Kategorier.h
 *   @authors   todo
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <string>
#include <map>
#include "Kategori.h"
#include "Kunde.h"

class Kategorier {
public:
    // Constructor
    Kategorier();

    // Destructor
    ~Kategorier();

    // Håndterer valg
    void handling(char valg);

    // Leser fra fil
    void lesFraFil();

    // Skriver til fil
    void skrivTilFil();

    // Oppretter ny kategori
    void nyKategori();

    // Sjekker om kategori finnes med samme navn
    bool kategoriFinnes(std::string kategoriNavn);

    // Skriver alle kategorier
    void skrivAlle();

    void fjernKategori(Kategori *kategori);

    // Finner kategori hvis kategori stemmer
    Kategori *finnKategori(std::string kategoriNavn);

    // Skriver alle tingene som ligger i en kategori
    void skrivFullKategori();
    
    // Legger inn en ny ting i datastrukturen
    void lagTing();

private:
    // Kart over kategorier
    std::map<std::string, Kategori *> kategoriMap;
};

#endif