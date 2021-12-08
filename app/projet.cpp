/**
 * Author: Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description:  Programme qui gere les etats de notre robot
 *
 * Date: 8 decembre 2021
 *
 *  * NOTE IMPORTBNTE: 6.
  Description Matériel:
    PA0: IR ligne #1
    PA1: IR ligne #2
    PA2: IR ligne #3
    PA3: IR ligne #4
    PA4: IR ligne #5
    PA5: IR calibration
    PA6: IR distance
    PA7: LED -
    VCC: IR ligne VCC
    GND: IR ligne VCC

    PB0: LED +
    PB1: LED -
    PB2:
    PB3: Sonore
    PB4:
    PB5: Sonore
    PB6:
    PB7:
    VCC: IR Distance VCC
    GND: IR Distance GND

    PC0: LCD
    PC1: LCD
    PC2: LCD
    PC3: LCD
    PC4: LCD
    PC5: LCD
    PC6: LCD
    PC7: LCD
    VCC: LCD VCC
    GND: LCD GND

    PD0
    PD1
    PD2: Bouton interupt carte mère INT0
    PD3: Bouton interupt breadboard INT1
    PD4: PWM Rouge Gauche(E)
    PD5: PWM Roue Droite (E)
    PD6: Direction Roue Gauche (D)
    PD7: Direction Roue Droite (D)
    VCC: Button poussoir VCC
    GND: Button poussoir GND

 * Travail : TP9
 * Section # : 1
 * Équipe # : 0613
 * Correcteur :
----------------------------------------------------------------------------------------------
 */

#include "projet.h"
void static inline w(void)
{
  cp_wait_ms(2000);
}

volatile uint8_t gEtats = 0;
volatile bool distanceCm = false;

ISR(INT0_vect)
{
  Conducteur &conducteur = Conducteur::getInstance();
  if (!conducteur.moteurEnMarche())
  {
    _delay_ms(DEBOUNCE);
    conducteur.demareMoteur();
    if (gEtats < ETAT_MAX)
    {
      gEtats++;
    }
    conducteur.desactiverAfficheDistance();
    distanceCm = false;
    _delay_ms(TEMPS_DEMARAGE);
    EIFR |= (1 << INTF0);
  }
}

ISR(INT1_vect)
{
  Conducteur &conducteur = Conducteur::getInstance();
  if (conducteur.peutAfficherDistance())
  {
    _delay_ms(DEBOUNCE);
    distanceCm = !distanceCm;
    EIFR |= (1 << INTF1);
  }
}

ISR(TIMER2_COMPA_vect)
{
  Minuterie &minuterie = Minuterie::getInstance();
  minuterie.incrementCount();
}

enum SegementParcours
{
  AB = 0,
  BD = 1,
  CBGHF = 2,
  FED = 3,
  Final = 4
};

void initialisation()
{
  cli();
  DDRB |= ((1 << LED_CATHODE) | (1 << LED_ANODE));
  DDRD &= ~((1 << INTERUPT) | (1 << POUSSOIR));
  EIMSK |= (1 << INT0) | (1 << INT1);
  EICRA |= (1 << ISC00) | (1 << ISC10) | (1 << ISC11) | (1 << ISC01);
  sei();
}

int main()
{
  initialisation();
  if (TEST_MODE_ACTIVATE)
    runTest();
  Conducteur &conducteur = Conducteur::getInstance();
  Led &led = Led::getInstance(PORTB);
  LCM afficheur(&DEMO_DDR, &DEMO_PORT);
  Distance &distance = distance.getInstance();
  Sonore &sonore = Sonore::getInstance();
  uint8_t isDone = false;
  while (!isDone)
  {
    afficheur.clear();
    sonore.arreter();
    if (conducteur.moteurEnMarche())
    {

      led.ledOnVert();
      switch (gEtats)
      {
      case SegementParcours::BD:
        segementBD();
        break;
      case SegementParcours::CBGHF:
        segememtCBGHF();
        break;
      case SegementParcours::FED:
        segementFED();
        break;
      case SegementParcours::Final:
        segementFinal();
        isDone = true;
        break;
      }
    }
    else
    {
      led.ledOnRouge();
      if (conducteur.peutAfficherDistance())
      {
        if (distanceCm)
        {
          afficheur << "Distance Cm: " << distance.getDistanceCm();
          w();
        }
        else
        {
          afficheur << "Distance Pouce: " << distance.getDistancePouce();
          w();
        }
      }
    }
  }
  led.ledOff();
  afficheur.clear();
  return 0;
}
