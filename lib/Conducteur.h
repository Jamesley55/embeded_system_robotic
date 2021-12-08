
/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: header de la classe Conducteur qui permet le mouvement des roues
 *
 * Date: 9 novembre 2021
 *
 * Description:
 * NOTE IMPORTANTE: 6.
   Description Matériel
    Enable Conducteur 1 -> PORTD 5
    Enable Conducteur 2 -> PORTD 6
    Direction Conducteur 1 -> PORTD 3
    Direction Conducteur 2 -> PORTD 4
    PORT A est en mode sortie
*/

#ifndef Conducteur_H
#define Conducteur_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "minuterie.h"

#define PWM_ROUE_GAUCHE PD4
#define PWM_ROUE_DROITE PD5
#define DIRECTION_ROUE_GAUCHE PD6
#define DIRECTION_ROUE_DROITE PD7
#define CAPTEUR_EXTREME_GAUCHE PA0
#define CAPTEUR_GAUCHE PA1
#define CAPTEUR_CENTRE PA2
#define CAPTEUR_DROITE PA3
#define CAPTEUR_EXTREME_DROITE PA4
#define FAST 0xff
#define NORMAL 0x90
#define SLOW 0x60
#define ZERO 0x0
#define Debounce 10
#define DISTANCE_LIMIT 12
#define SUIVRE_LIGNE_BUFFER 30
#define BUFFER 300
#define PRESCALER_1024 1024
#define N 2
#define PERIODE_PAR_SECONDE 10

enum DIRECTION
{
   avant,
   arriere
};

class Conducteur
{
public:
   static Conducteur &getInstance();
   void avancer(uint16_t puissance);
   void tournerDroite(uint16_t puissance);
   void tournerGauche(uint16_t puissance);
   void reculer(uint16_t puissance);
   void ajustementDirection(uint16_t puissanceDroite, uint16_t puissanceGauche);
   bool suivreLigne(uint16_t puissance);
   void demiTour();
   void arreter();
   bool peutTournerDroite();
   bool peutTournerGauche();
   void mettreEnAttente();
   void desactiverAfficheDistance();
   void demareMoteur();
   bool moteurEnMarche();
   bool peutAfficherDistance();
   void setDistanceMur(uint16_t distance);
   uint16_t  getDistanceMur();
   bool estSurLigne();
   bool estSurLigneMillieu();
   void trouverLigneNoir(uint16_t puissance);
   void virage135deg(uint16_t puissance);
   void ajustementGauche(uint16_t puissance);
   void ajustementDroite(uint16_t puissance);
   void avancerEtTournerGauche();
   void avancerEtTournerDroite();
   void reajustementCapteur();

private:
   void changeDirection(DIRECTION droit, DIRECTION gauche);
   static Conducteur *obj;
   Conducteur();
   ~Conducteur();
   void ajustementPwm();
   uint16_t distanceMur;
   volatile bool affichageDistance = false;
   volatile bool enableMoteur = false;
};

#endif /* Conducteur_H */
