#include "projet.h"

void avancerEMur()
{
  Minuterie &minuterie = Minuterie::getInstance();
  minuterie.resetCount();
  uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
  minuterie.partirMinuterie(duree);
  Conducteur &conducteur = Conducteur::getInstance();
  do
  {
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
    conducteur.reajustementCapteur();
  } while (minuterie.getCount() < conducteur.getDistanceMur());
}

void segementFinal()
{
  Conducteur &conducteur = Conducteur::getInstance();
  conducteur.reculer(NORMAL);
  _delay_ms(RECULER_DELAY);
  conducteur.demiTour();
  conducteur.avancerEtTournerDroite();
  conducteur.avancerEtTournerDroite();
  avancerEMur();
  conducteur.mettreEnAttente();
}
