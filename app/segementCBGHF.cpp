
#include "projet.h"
void avancerApresDemiTour()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
        conducteur.reajustementCapteur();
    } while (!conducteur.peutTournerGauche());
    conducteur.ajustementDroite(NORMAL);
    _delay_ms(BUFFER);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void avancerSegmentCB1()
{
    Minuterie &minuterie = Minuterie::getInstance();
    uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
    minuterie.partirMinuterie(duree);
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
        conducteur.reajustementCapteur();
    } while (!conducteur.peutTournerGauche());
    minuterie.arreterMinuterie();
    conducteur.arreter();
    conducteur.tournerGauche(SLOW);
}

void avancerSegementBG()
{
    Minuterie &minuterie = Minuterie::getInstance();

    Conducteur &conducteur = Conducteur::getInstance();
    for (uint16_t count = minuterie.getCount(); count > 0; count--)
    {
        conducteur.suivreLigne(NORMAL);
        conducteur.reajustementCapteur();
    }
    conducteur.arreter();
    conducteur.virage135deg(NORMAL);
}

void avancerSegementFPoteau()
{
    Distance &distance = Distance::getInstance();
    Conducteur &conducteur = Conducteur::getInstance();
    Minuterie &minuterie = Minuterie::getInstance();
    uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
    minuterie.resetCount();
    minuterie.partirMinuterie(duree);
    distance.lireDistance(true);
    while (distance.getDistancePouce() > DISTANCE_LIMIT)
    {
        distance.lireDistance(true);
        musique();
        conducteur.suivreLigne(NORMAL);
        if (!conducteur.estSurLigne())
        {
            minuterie.arreterMinuterie();
            conducteur.ajustementDroite(NORMAL);
            _delay_ms(100);
            conducteur.ajustementGauche(NORMAL);
            _delay_ms(100);
            minuterie.partirMinuterie(duree);
        }
    };
    conducteur.mettreEnAttente();
    /**
     * formule de la distance du robot en fonction du temp (count) de la minuterie
     * */
    uint8_t distancePoteau = ((minuterie.getCount() + 35) / 3) + distance.getDistanceCm();
    distance.setDitanceCm(distancePoteau);
}

void segememtCBGHF()
{
    Conducteur &conducteur = Conducteur::getInstance();
    conducteur.demiTour();
    avancerApresDemiTour();
    avancerSegmentCB1();
    avancerSegementBG();
    conducteur.avancerEtTournerGauche();
    conducteur.avancerEtTournerGauche();
    conducteur.avancerEtTournerGauche();
    avancerSegementFPoteau();
}
