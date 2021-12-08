#include "projet.h"

void contournerPoteau()
{
  Conducteur &conducteur = Conducteur::getInstance();
  conducteur.ajustementDirection(ZERO, NORMAL);
  _delay_ms(1000);
  conducteur.ajustementDirection(NORMAL, NORMAL);
  _delay_ms(1500);
  conducteur.ajustementDirection(NORMAL, ZERO);
  _delay_ms(700);
  conducteur.ajustementDirection(NORMAL, NORMAL);
  _delay_ms(6000);
  conducteur.ajustementDirection(NORMAL, ZERO);
  _delay_ms(1000);
  while (!conducteur.estSurLigneMillieu())
    conducteur.ajustementDirection(NORMAL, NORMAL);
  conducteur.arreter();
}

void avancer12PoucesMur()
{
  Distance &distance = Distance::getInstance();
  Conducteur &conducteur = Conducteur::getInstance();
  Minuterie &minuterie = Minuterie::getInstance();
  minuterie.resetCount();
  uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
  minuterie.partirMinuterie(duree);
  distance.lireDistance(false);
  while (distance.getDistancePouce() > DISTANCE_LIMIT)
  {
    distance.lireDistance(false);
    musique();
    conducteur.suivreLigne(NORMAL);
    conducteur.reajustementCapteur();
  };
  conducteur.setDistanceMur(minuterie.getCount() + FROLE_MUR_COUNT);
  conducteur.arreter();
  minuterie.resetCount();
  minuterie.partirMinuterie(duree);
  do
  {
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
    conducteur.reajustementCapteur();
  } while (minuterie.getCount() < FROLE_MUR_COUNT);
  conducteur.arreter();
}

void ajustementApresContournerPoteau()
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
    if (!conducteur.estSurLigne())
      conducteur.tournerGauche(SLOW);
  } while (minuterie.getCount() < BUFFER_COUNT);
  conducteur.arreter();
}

void segementFED()
{
  Conducteur &conducteur = Conducteur::getInstance();
  contournerPoteau();
  ajustementApresContournerPoteau();
  conducteur.avancerEtTournerGauche();
  conducteur.avancerEtTournerGauche();
  avancer12PoucesMur();
  conducteur.mettreEnAttente();
}