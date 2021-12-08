
/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: definition des methodes de la classe Conducteur qui permet le definir
 * different movement du moteur en fonction du capteur de ligne
 *
 * Date: 9 novembre 2021
 * */

#include "Conducteur.h"
Conducteur *Conducteur::obj = nullptr;

Conducteur::Conducteur()
{
    OCR1A = 0xff;
    OCR1B = 0xff;
    TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0);
    TCCR1B |= (1 << CS11) | (1 << WGM10);
    TCCR1C = 0;
    DDRA &= ~((1 << CAPTEUR_EXTREME_GAUCHE) | (1 << CAPTEUR_GAUCHE) |
              (1 << CAPTEUR_CENTRE) | (1 << CAPTEUR_DROITE) |
              (1 << CAPTEUR_EXTREME_DROITE));

    DDRD |= ((1 << PWM_ROUE_GAUCHE) | (1 << PWM_ROUE_DROITE) |
             (1 << DIRECTION_ROUE_GAUCHE) | (1 << DIRECTION_ROUE_DROITE));
}

Conducteur &Conducteur::getInstance()
{
    if (!obj)
    {
        obj = new Conducteur();
    }
    return *obj;
}

Conducteur::~Conducteur()
{
    free(obj);
}
void Conducteur::changeDirection(DIRECTION gauche, DIRECTION droite)
{
    if (droite == DIRECTION::avant)
    {
        PORTD &= ~(1 << PD7);
    }
    else
    {
        PORTD |= (1 << PD7);
    }

    if (gauche == DIRECTION::avant)
    {
        PORTD &= ~(1 << PD6);
    }
    else
    {
        PORTD |= (1 << PD6);
    }
}

void Conducteur::avancer(uint16_t puissance)
{
    changeDirection(DIRECTION::avant, DIRECTION::avant);
    ajustementDirection(puissance, puissance);
}

void Conducteur::reculer(uint16_t puissance)
{
    changeDirection(DIRECTION::arriere, DIRECTION::arriere);
    ajustementDirection(puissance, puissance);
}

void Conducteur::virage135deg(uint16_t puissance)
{
    changeDirection(DIRECTION::arriere, DIRECTION::avant);
    ajustementDirection(ZERO, puissance);
    _delay_ms(1800);
    arreter();
    trouverLigneNoir(puissance);
}

void Conducteur::reajustementCapteur()
{
    if (!estSurLigne())
    {
        ajustementDroite(NORMAL);
        _delay_ms(100);
        ajustementGauche(NORMAL);
        _delay_ms(100);
    }
}

void Conducteur::trouverLigneNoir(uint16_t puissance)
{
    while (!estSurLigne())
    {
        avancer(SLOW);
    };
    suivreLigne(puissance);
}

void Conducteur::demiTour()
{
    changeDirection(DIRECTION::arriere, DIRECTION::avant);
    ajustementDirection(SLOW, SLOW);
    _delay_ms(1700);
    while (!(PINA & (1 << CAPTEUR_CENTRE)))
        ;
    arreter();
    suivreLigne(NORMAL);
}

void Conducteur::tournerDroite(uint16_t puissance)
{
    avancer(puissance);
    _delay_ms(BUFFER);
    changeDirection(DIRECTION::avant, DIRECTION::avant);
    ajustementDirection(puissance, ZERO);
    while (!(PINA & (1 << CAPTEUR_DROITE) && PINA & (1 << CAPTEUR_CENTRE)))
        ;
    ajustementDroite(puissance);
}

void Conducteur::tournerGauche(uint16_t puissance)
{
    avancer(puissance);
    _delay_ms(BUFFER);
    changeDirection(DIRECTION::avant, DIRECTION::avant);
    ajustementDirection(ZERO, puissance);
    _delay_ms(BUFFER);
    while (!(PINA & (1 << CAPTEUR_GAUCHE) && PINA & (1 << CAPTEUR_CENTRE)))
        ;
    ajustementGauche(puissance);
}

void Conducteur::arreter()
{
    ajustementDirection(ZERO, ZERO);
    _delay_ms(BUFFER);
}

void Conducteur::ajustementDirection(uint16_t puissanceGauche, uint16_t puissanceDroite)
{
    OCR1A = 0xff - puissanceDroite;
    OCR1B = 0xff - puissanceGauche;
}

bool Conducteur::peutTournerGauche()
{
    return (
        ((PINA & (1 << CAPTEUR_EXTREME_GAUCHE)) &&
         (PINA & (1 << CAPTEUR_GAUCHE)) &&
         (PINA & (1 << CAPTEUR_CENTRE))));
}

bool Conducteur::peutTournerDroite()
{
    return (
        ((PINA & (1 << CAPTEUR_EXTREME_DROITE)) &&
         (PINA & (1 << CAPTEUR_DROITE)) &&
         (PINA & (1 << CAPTEUR_CENTRE))));
}

void Conducteur::ajustementGauche(uint16_t puissance)
{
    changeDirection(DIRECTION::avant, DIRECTION::avant);
    ajustementDirection(SLOW, puissance);
}

void Conducteur::ajustementDroite(uint16_t puissance)
{
    changeDirection(DIRECTION::avant, DIRECTION::avant);
    ajustementDirection(puissance, SLOW);
}

void Conducteur::avancerEtTournerGauche()
{
    do
    {
        suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
        reajustementCapteur();
    } while (!peutTournerGauche());
    arreter();
    tournerGauche(SLOW);
    suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void Conducteur::avancerEtTournerDroite()
{
    do
    {
        suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
        reajustementCapteur();
    } while (!peutTournerDroite());
    arreter();
    tournerDroite(SLOW);
    suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

bool Conducteur::suivreLigne(uint16_t puissance)
{
    _delay_ms(SUIVRE_LIGNE_BUFFER);
    if (!estSurLigne())
    {
        _delay_ms(Debounce);
        if (!estSurLigne())
        {
            arreter();
            return false;
        }
    }
    else if (!(PINA & (1 << CAPTEUR_CENTRE)))
    {
        if (PINA & (1 << CAPTEUR_GAUCHE) || PINA & (1 << CAPTEUR_EXTREME_GAUCHE))
        {
            ajustementGauche(puissance);
        }
        else if (PINA & (1 << CAPTEUR_DROITE) || PINA & (1 << CAPTEUR_EXTREME_DROITE))
        {
            ajustementDroite(puissance);
        }
    }
    else
    {
        avancer(puissance);
    }
    return true;
}

bool Conducteur::estSurLigne()
{
    return (PINA & (1 << CAPTEUR_EXTREME_GAUCHE) ||
            PINA & (1 << CAPTEUR_GAUCHE) ||
            PINA & (1 << CAPTEUR_CENTRE) ||
            PINA & (1 << CAPTEUR_DROITE) ||
            PINA & (1 << CAPTEUR_EXTREME_DROITE));
}

void Conducteur::setDistanceMur(uint16_t distance)
{
    distanceMur = distance;
}

uint16_t Conducteur::getDistanceMur()
{
    return distanceMur;
}

bool Conducteur::estSurLigneMillieu()
{
    return (PINA & (1 << CAPTEUR_CENTRE));
}

void Conducteur::mettreEnAttente()
{
    arreter();
    enableMoteur = false;
    affichageDistance = true;
}

void Conducteur::desactiverAfficheDistance()
{
    affichageDistance = false;
}

void Conducteur::demareMoteur()
{
    enableMoteur = true;
}

bool Conducteur::moteurEnMarche()
{
    return enableMoteur;
}

bool Conducteur::peutAfficherDistance()
{
    return affichageDistance;
}
