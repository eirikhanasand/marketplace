/**
 *  Header for Kategorier klassen
 *
 *  @file      Kategorier.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include "kategori.hpp"
#include "kunde.hpp"

class Kategorier {
public:
    Kategorier();

    ~Kategorier();

    void kategoriHandling(char valg);

    void tingHandling(char valg);

    void lesFraFil();

    bool kategoriFinnes(std::string kategoriNavn);

    void skrivAlle() const;

    void fjernKategori(Kategori *kategori);

    Kategori *hentKategoriEntydig(std::string kategoriNavn);

    void lagTingIKategori();

    void endreTingIKategori();

    void kjopTing();

    void lagKategori();

    void skrivAlleTilFil();

    void lesAlleFraFil();

private:
    std::map<std::string, Kategori *> kategoriMap;
};

#endif