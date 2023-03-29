/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Kategori.h"
#include "Kategorier.h"
#include "LesData3.h"

Kategori::Kategori(std::string KategoriNavn) {
    kategoriNavn = KategoriNavn;
    settData();
}

Kategori::~Kategori() {
    //TODO
}

// Input category data
void Kategori::settData() {
    antallTingTilSalgs = 0;
}

// Prints category data
void Kategori::skrivData() {
    std::cout << "Kategorinavn: " << kategoriNavn << "\tAntall ting til salgs: " << antallTilSalgs << std::endl;
}

std::string Kategori::hentNavn() const {
    return kategoriNavn;
}
