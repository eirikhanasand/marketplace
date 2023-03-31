/**
 *  Utvidet verktøykasse for å lese tegn, tall og stringer.
 *
 *  Identisk til 'LesData2.h' bare at funksjonenes DEKLARASJON 
 *  og DEFINISJON (som er på DENNE filen) er adskilt, og at denne
 *  også støtter innlesning av strings.
 *
 *  @file     lesData3.cpp
 *  @author   Eirik Hanasand, Sindre Hagen Strømdal, Steffen Ludviksen Sæther, Frode Haug, NTNU
 */

#include <algorithm>
#include <iostream>                 //  cin, cout
#include <iomanip>                  //  setprecision
#include <cstdlib>                  //  atoi, atof
#include <cctype>                   //  toupper
#include <string>

#include "lesData3.hpp"             //  Prototypene for denne filens innhold

/**
 *  Leser og returnerer ett (upcaset) tegn.
 *
 *  @param   t  - Ledetekst til brukeren når ber om ett tegn
 *
 *  @return  Ett (upcaset) tegn.
 */
char lesChar(const char *t) {
    char tegn;
    std::cout << t << ":  ";
    std::cin >> tegn;
    std::cin.ignore(MAXCHAR, '\n');
    return (toupper(tegn));
}

/**
 *  Leser og returnerer et flyttall mellom to gitte grenser.
 *
 *  @param   t    - Ledetekst til brukeren når ber om input/et tall
 *  @param   min  - Minimum for innlest og godtatt tallverdi
 *  @param   max  - Maksimum for innlest og godtatt tallverdi
 *
 *  @return  Godtatt verdi i intervallet 'min' - 'max'
 */
float lesFloat(const char *t, const float min, const float max) {
    char buffer[MAXCHAR] = "";
    float tall = 0.0F;
    bool feil = false;

    do {
        feil = false;
        std::cout << std::fixed << std::showpoint << std::setprecision(2);
        std::cout << t << " (" << min << " - " << max << "):  ";
        std::cin.getline(buffer, MAXCHAR);
        tall = static_cast <float> (atof(buffer));
        if (tall == 0 && buffer[0] != '0') {
            feil = true;
            std::cout << "\nERROR: Not a float\n\n";
        }
    } while (feil || tall < min || tall > max);

    return tall;
}

/**
 *  Leser og returnerer et heltall mellom to gitte grenser.
 *
 *  @param   t    - Ledetekst til brukeren når ber om input/et tall
 *  @param   min  - Minimum for innlest og godtatt tallverdi
 *  @param   max  - Maksimum for innlest og godtatt tallverdi
 *
 *  @return  Godtatt verdi i intervallet 'min' - 'max'
 */
int lesInt(const char *t, const int min, const int max) {
    char buffer[MAXCHAR] = "";
    int tall = 0;
    bool feil = false;

    do {
        feil = false;
        std::cout << t << " (" << min << " - " << max << "):  ";
        std::cin.getline(buffer, MAXCHAR);
        tall = atoi(buffer);
        if (tall == 0 && buffer[0] != '0') {
            feil = true;
            std::cout << "\nERROR: Not an integer\n\n";
        }
    } while (feil || tall < min || tall > max);

    return tall;
}

/**
 * Leser og returnerer en bool.
 *
 *
 *  @param   t   - Ledetekst til brukeren når ber om input/et tall
 *  @param   ja  - Bokstaven som tilsvarer et ja(true)
 *  @param   nei - Bokstaven som tilsvarer et nei(false)
 *
 *  @return True eller false fra om brukeren svarte ja eller nei.
 */
bool lesBool(const char *t, const char ja, const char nei) {
    bool svar = false;
    bool feil = false;
    
    do {
        feil = false;
        std::cout << t;
        char svarBokstav = lesChar("");

        if (svarBokstav != ja && svarBokstav != nei) {
            feil = true;
            std::cout << "\nERROR: Invalid character\n\n";
        } else {
            svar = svarBokstav == ja;
        }
    } while (feil);

    return svar;
}

/**
 *  Leser og returnerer en linje
 *
 *  @param   t - Ledetekst til brukeren
 *
 *  @return  string
 */
std::string lesString(const std::string t) {
    std::string string;
    std::cout << t << ':' << std::endl;
    std::getline(std::cin, string);
    
    return string;
}

std::string stringTilLiten(std::string t) {
    std::transform(t.begin(), t.end(), t.begin(), tolower);
    return t;
}