/**
 *   todo
 *
 *   @file      kategorier.cpp
 *   @authors   todo
 */

#include <iostream>
#include <fstream>
#include <string>

#include "kategori.h"
#include "kategorier.h"

extern Kategorier gKategoribase;

Kategori::Kategori(std::string KategoriNavn) {
    kategoriNavn = KategoriNavn;
    settData();
}

Kategori::~Kategori() {
    gKategoribase.remove();
}

// Input category data
void Kategori::settData() {
    kategoriNavn = lesString("Kategorinavn");
}

// Prints category data
void Kategori::skrivData() {
    std::cout << "Kategorinavn: " << kategoriNavn << "\tAntall ting til salgs: " << antallTilSalgs << std::endl;
}

std::string Kategori::hentNavn() const { 
    return kategoriNavn; 
}