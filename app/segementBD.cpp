#include "projet.h"
#define NOMBRE_DE_CHEMIN_GAUCHE 2

void segementBD()
{
  Distance &distance = Distance::getInstance();
  Conducteur &conducteur = Conducteur::getInstance();
  distance.lireDistance(false);
  uint8_t peutJouerMusique = 0;
  do
  {
    distance.lireDistance(false);
    if (conducteur.peutTournerDroite())
    {
      peutJouerMusique++;
      conducteur.ajustementGauche(NORMAL);
      _delay_ms(BUFFER);
    }
    if (peutJouerMusique >= NOMBRE_DE_CHEMIN_GAUCHE)
      musique();
    conducteur.suivreLigne(NORMAL);
    conducteur.reajustementCapteur();
  } while (distance.getDistancePouce() > DISTANCE_LIMIT || peutJouerMusique < NOMBRE_DE_CHEMIN_GAUCHE);
  conducteur.mettreEnAttente();
}
