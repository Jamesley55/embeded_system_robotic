
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#define DISTANCE_MAX_SONORE 24

void musique()
{
  Sonore &sonore = Sonore::getInstance();
  Distance &distance = Distance::getInstance();
  distance.lireDistance(true);
  if (distance.getDistancePouce() <= DISTANCE_LIMIT)
  {
    sonore.jouerNote(95);
  }
  else if (distance.getDistancePouce() == DISTANCE_MAX_SONORE)
  {
    sonore.jouerNote(55);
  }
  else if (distance.getDistancePouce() > DISTANCE_MAX_SONORE)
  {
    sonore.arreter();
  }
  else
  {
    /**
     * Formule  de la frequence sonore trouver par la droite passant par (12,2000), (24,200) 
     * */
    uint16_t frequence = -150 * distance.getDistancePouce() + 3800;
    sonore.jouerFrequence(frequence);
  }
}