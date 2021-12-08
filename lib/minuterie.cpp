/**
 * Autheur : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: definition des methodes de la classe Minuterie qui definie une  minuterie par interruption 
 *              
 * Date: 29 octobre 2021
 * */

#include "minuterie.h"
#include <stdlib.h>

Minuterie *Minuterie::obj = nullptr;
Minuterie::Minuterie()
{
}

Minuterie::~Minuterie()
{
    free(obj);
}

Minuterie &Minuterie::getInstance()
{
    if (!obj)
    {
        obj = new Minuterie();
    }
    return *obj;
}

void Minuterie::partirMinuterie(uint16_t duree)
{
  TCNT2 = 0; 
  OCR2A = duree;
  TCCR2B |= (1 << CS22) |(1 << CS21)| ( 1 << CS20) | (1 << WGM21);
  TCCR1C = 0;
  TIMSK2 |= (1 << OCIE2A);
}

void Minuterie::arreterMinuterie()
{
    TIMSK2 = 0;
}

void Minuterie::resetCount()
{
    count_ = 0;
}

void Minuterie::incrementCount()
{
    count_++;
}

uint16_t Minuterie::getCount()
{
    return count_;
}
