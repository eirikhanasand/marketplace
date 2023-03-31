/**
 *  Utvidet verktøykasse for å lese tegn, tall og stringer.
 *
 *  Identisk til 'LesData2.h' bare at funksjonenes DEKLARASJON 
 *  og DEFINISJON (som er på DENNE filen) er adskilt, og at denne
 *  også støtter innlesning av strings.
 *
 *  @file     lesData3.hpp
 *  @author   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther, Frode Haug, NTNU
 */

#ifndef __LESDATA3_H
#define __LESDATA3_H

#include <string>

const int MAXCHAR = 200;      //  Max.tegn i input-buffer.

char lesChar(const char *t);

float lesFloat(const char *t, const float min, const float max);

int lesInt(const char *t, const int min, const int max);

bool lesBool(const char *t, const char ja = 'J', const char nei = 'N');

std::string lesString(const std::string t);

std::string stringTilLiten(std::string t);

#endif