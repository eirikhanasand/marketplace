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
    Kategori *hentKategoriEntydig(std::string kategoriNavn) const;
    bool kategoriFinnes(std::string kategoriNavn) const;
    int hentAntallTing() const;
    int antallKategorier() const;
    void kategoriHandling(char valg);
    void tingHandling(char valg);
    void lesFraFil();
    void lagKategori();
    void lagTingIKategori();
    void endreTingIKategori();
    void skrivAlleTilFil();
    void skrivAlle() const;
    void skrivEntydig() const;
    void fjernKategori(Kategori *kategori);
    void kjopTing();
    void okAntallTing();
    void fjernAlleTingTilhorendeKunde(int kundenummer);

 private:
    std::map<std::string, Kategori *> kategoriMap;
    int antallTing = 0;
};

#endif