/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: header de la classe Led qui sert a allumer la Led d'une certaine couleur ou de l'eteindre
 *              
 * Date: 29 octobre 2021
 * */

#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <stdlib.h>

class Led
{
public:
  enum Couleur
  {
    rouge,
    vert
  };
  void ledOnRouge();
  void ledOnVert();
  void ledOnAmbre(uint8_t count);
  void ledOff();
  static Led &getInstance(volatile uint8_t &port);

private:
  void fermerCouleurPrecedent();
  const uint8_t ROUGE = (1 << PIN0);
  const uint8_t VERT = (1 << PIN1);
  Couleur couleur;
  volatile uint8_t *PORT;
  Led(volatile uint8_t &port);
  ~Led();
  static Led *obj;
};

#endif /* LED_H */
