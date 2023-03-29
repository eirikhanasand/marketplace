/**
 *   Header for klassen Kunde
 *
 *   @file      Kunde.h
 *   @authors   todo
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <list>
#include <string>
#include "nyTing.h"

class Kategori {
public:
    // Constructor
    Kategori(std::string KategoriNavn);

    // Destructor
    ~Kategori();

    // Setter kategoridata
    void settData();

    // Skriver kategoridata
    void skrivData();

    // Henter kategorinavn
    std::string hentNavn() const;

private:
    std::list<NyTing *> NyTing;

    int antallTilSalgs;

    std::string kategoriNavn;
};

#endif