/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: definition des methodes de la classe Led qui sert a allumer la Led d'une certaine couleur ou de l'eteindre
 *              
 * Date: 29 octobre 2021
 * */

#include "led.h"
#include <util/delay.h>

#include <avr/io.h>
Led *Led::obj = nullptr;

Led::Led(volatile uint8_t &port)
{
    PORT = &port;
    
}

Led &Led::getInstance(volatile uint8_t &port)
{
    if (!obj)
    {
        obj = new Led(port);
    }
    return *obj;
}

Led::~Led()
{
    free(obj);
}

void Led::fermerCouleurPrecedent()
{
    switch (couleur)
    {
    case Couleur::rouge:
        *PORT &= ~ROUGE;
        break;
    case Couleur::vert:
        *PORT &= ~VERT;
        break;
    }
}

void Led::ledOnRouge()
{
    fermerCouleurPrecedent();
    *PORT |= ROUGE;
    couleur = Couleur::rouge;
}

void Led::ledOnVert()
{
    fermerCouleurPrecedent();
    *PORT |= VERT;
    couleur = Couleur::vert;
}

void Led::ledOff()
{
    if (couleur)
        fermerCouleurPrecedent();
}

void Led::ledOnAmbre(uint8_t count)
{
    while (count > 0)
    {
        ledOnRouge();
        _delay_ms(5);
        ledOnVert();
        _delay_ms(7);
        count--;
    }
    ledOff();
}