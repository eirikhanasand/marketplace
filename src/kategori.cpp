/**
 *  Definisjon av funksjoner i Kategori klassen
 *
 *  @file      kategori.cpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#include <iostream>
#include <fstream>
#include <string>

#include "Kategori.hpp"
#include "Kategorier.hpp"
#include "LesData3.hpp"

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
