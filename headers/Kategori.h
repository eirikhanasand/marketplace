/**
 *   Header for klassen Kategori
 *
 *   @file      Kategori.h
 *   @authors   todo
 */

#ifndef __KATEGORI_H
#define __KATEGORI_H

#include "NyTing.h"
#include <iostream>
#include <list>

struct Kategori {
    int sisteNr;
    
    std::list <NyTing*> NyTing;
};

#endif