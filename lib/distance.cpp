/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: definition des methodes de la classe Led qui sert a allumer la Led d'une certaine couleur ou de l'eteindre
 *
 * Date: 15 novembre 2021
 * */

#include "distance.h"
#include "can.h"
#include <util/delay.h>

#include <avr/io.h>
#include <math.h>
#include <led.h>
#include <lcm_so1602dtr_m_fw.h>

#include <lcm_so1602dtr_m_fw.h>
Distance *Distance::obj = nullptr;

Distance::Distance()
{
  DDRB &= ~(1 << DISTANCE);
}

Distance::~Distance()
{
  free(obj);
}

Distance &Distance::getInstance()
{
  if (!obj)
  {
    obj = new Distance();
  }
  return *obj;
}

uint8_t Distance::getDistanceCm()
{
  return distanceCm ? distanceCm : __UINT8_MAX__;
}

uint8_t Distance::getDistancePouce()
{
  distancePouce = getDistanceCm() / constanteConversion;
  return distancePouce;
}

void Distance::lireDistance(bool isPoteau)
{
  Can can;
  LCM disp(&DDRC, &PORTC);

  uint16_t echantillion = 0;
  for (uint8_t i = 0; i < TAILLE_ECHANTILLION; i++)
  {
    echantillion += can.lecture(DISTANCE) >> 2;
  }
  uint8_t lecture = echantillion / TAILLE_ECHANTILLION;

  if (isPoteau)
  {
    if (lecture > 120)
    {
      distanceCm = 10;
    }
    else if (lecture <= 27)
    {
      distanceCm = 80;
    }
    else
    {
      // formule trouver par calibrage https://docs.google.com/spreadsheets/d/1egLM7037Mm5DoP2ZqAspQY-X8IcR496iM7fL5_gWt3k/edit?usp=sharing
      distanceCm = round(4877 * pow(lecture, -1.26));
    }
  }
  else
  {
    if (lecture > 116)
    {
      distanceCm = 10;
    }
    else if (lecture <= 36)
    {
      distanceCm = 65;
    }
    else
    {
      // formule trouver par calibrage https://docs.google.com/spreadsheets/d/1egLM7037Mm5DoP2ZqAspQY-X8IcR496iM7fL5_gWt3k/edit?usp=sharing
      distanceCm = round(6537 * pow(lecture, -1.35));
    }
  }
}

void Distance::setDitanceCm(uint8_t distance)
{
  distanceCm = distance;
}
