/**
 *   Header for klassen Kategori
 *
 *   @file      Kategori.h
 *   @authors   todo
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include <iostream>
#include <list>
#include "NyTing.h"

class Kategori {
    int sisteNr;

    std::list<NyTing*> NyTing;
};

#endif