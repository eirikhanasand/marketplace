/**
 *  Header for Kategorier klassen
 *
 *  @file      Kategorier.hpp
 *  @authors   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther
 */

#ifndef __KATEGORIER_H
#define __KATEGORIER_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "kategori.hpp"
#include "kunde.hpp"

class Kategorier {
public:
    ~Kategorier();
    Kategori *hentKategoriEntydig(std::string kategoriNavn);
    bool kategoriFinnes(std::string kategoriNavn);
    void kategoriHandling(char valg);
    void tingHandling(char valg);
    void lesFraFil();
    void lagKategori();
    void lagTingIKategori();
    void endreTingIKategori();
    void skrivAlleTilFil();
    void skrivAlle() const;
    void skrivEntydig();
    void fjernKategori(Kategori *kategori);
    void kjopTing();

private:
    std::map<std::string, Kategori *> kategoriMap;
};

#endif