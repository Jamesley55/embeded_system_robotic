#include "projet.h"

void testLed()
{
    Led &led = Led::getInstance(PORTB);
    led.ledOnRouge();
    _delay_ms(2000);
    led.ledOnVert();
    _delay_ms(2000);
    led.ledOff();
    _delay_ms(2000);
}

void testMusique()
{
    Sonore &sonore = Sonore::getInstance();
    uint8_t note = 45;
    while (note < 95)
    {
        sonore.jouerNote(note);
        _delay_ms(1000);
        note++;
    }
    sonore.arreter();
    _delay_ms(2000);
}

void testConducteur()
{
    Conducteur &conducteur = Conducteur::getInstance();
    conducteur.avancer(NORMAL);
    _delay_ms(500);
    conducteur.ajustementDirection(NORMAL, SLOW);
    _delay_ms(500);
    conducteur.ajustementDirection(SLOW, NORMAL);
    _delay_ms(500);
    conducteur.arreter();
    _delay_ms(2000);
}

void testSuivreLigne()
{
    Conducteur &conducteur = Conducteur::getInstance();
    Led &led = Led::getInstance(PORTB);
    led.ledOnRouge();
    _delay_ms(2000);
    led.ledOff();
    for (int i = 0; i < 200; i++)
    {
        conducteur.avancer(NORMAL);
    }
    led.ledOnVert();
    _delay_ms(2000);
}

void testCapteur()
{
    LCM disp(&DEMO_DDR, &DEMO_PORT);
    Distance &distance = Distance::getInstance();
    uint8_t nombreDeDonne = 100;
    while (nombreDeDonne > 0)
    {
        distance.lireDistance(false);
        disp << distance.getDistanceCm();
        _delay_ms(250);
        nombreDeDonne--;
        disp.clear();
    }
}

void testDemiTour()
{
    Conducteur &conducteur = Conducteur::getInstance();
    conducteur.demiTour();
    conducteur.arreter();
    while (true)
    {
        conducteur.suivreLigne(NORMAL);
    }
}

void testAvancerSegementBD()
{
    Distance &distance = Distance::getInstance();
    Conducteur &conducteur = Conducteur::getInstance();
    distance.lireDistance(false);
    while (distance.getDistancePouce() > DISTANCE_LIMIT)
    {
        distance.lireDistance(false);
        musique();
        conducteur.suivreLigne(NORMAL);
    };
    conducteur.mettreEnAttente();
}

void testCapteurDistance()
{
    Can can;
    LCM disp(&DEMO_DDR, &DEMO_PORT);

    uint8_t nombreDeDonne = 100;
    while (true)
    {
        uint8_t lecture = can.lecture(PA6) >> 2;
        disp << lecture;
        _delay_ms(2000);
        nombreDeDonne--;
        disp.clear();
    }
}

void testAvancerApresDemiTour()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.ajustementDroite(NORMAL);
    _delay_ms(BUFFER);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void testAvancerSegmentCB1()
{
    Minuterie &minuterie = Minuterie::getInstance();
    uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
    minuterie.partirMinuterie(duree);
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    minuterie.arreterMinuterie();
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(NORMAL);
}

void testAvancerSegementBG()
{
    Minuterie &minuterie = Minuterie::getInstance();
    Conducteur &conducteur = Conducteur::getInstance();
    for (uint16_t count = minuterie.getCount() - 8; count > 0; count--)
    {
        conducteur.suivreLigne(NORMAL);
    }
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.virage135deg(NORMAL);
}

void testAvancerSegementHC()
{
    Conducteur &conducteur = Conducteur::getInstance();

    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(NORMAL);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void testAvancerSegementCB2()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(NORMAL);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void testAvancerSegementBF()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(NORMAL);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(SUIVRE_LIGNE_BUFFER);
}

void testAvancerSegementFPoteau()
{
    Distance &distance = Distance::getInstance();
    Conducteur &conducteur = Conducteur::getInstance();
    distance.lireDistance(true);
    while (distance.getDistancePouce() > DISTANCE_LIMIT)
    {
        distance.lireDistance(true);
        musique();
        conducteur.suivreLigne(NORMAL);
    };
    LCM disp(&DEMO_DDR, &DEMO_PORT);
    if (distance.getDistancePouce())
        disp << "distance Pouce: " << distance.getDistancePouce();
    else
        disp << "pas  distance";
    conducteur.mettreEnAttente();
    _delay_ms(5000);
    disp.clear();
}

void testMinuterie()
{
    Minuterie &minuterie = Minuterie::getInstance();
    uint16_t duree = round(F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE));
    minuterie.partirMinuterie(duree);
    LCM disp(&DEMO_DDR, &DEMO_PORT);
    Led &led = Led::getInstance(PORTB);
    led.ledOnVert();
    if (minuterie.getCount())
        disp << minuterie.getCount();
    else
        disp << "No count";
    _delay_ms(5000);
    led.ledOnRouge();
    disp.clear();
}

void testCalculerVitesse()
{
    Minuterie &minuterie = Minuterie::getInstance();
    uint16_t duree = round((F_CPU / (PRESCALER_1024 * N * PERIODE_PAR_SECONDE)));
    minuterie.partirMinuterie(duree);
}

void testAvancerEtTournerGauche()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(SLOW);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(1000);
}

void testAvancerEtTournerGauche2()
{
    Conducteur &conducteur = Conducteur::getInstance();
    do
    {
        conducteur.suivreLigne(NORMAL);
        _delay_ms(SUIVRE_LIGNE_BUFFER);
    } while (!conducteur.peutTournerGauche());
    conducteur.arreter();
    _delay_ms(BUFFER);
    conducteur.tournerGauche(SLOW);
    conducteur.suivreLigne(NORMAL);
    _delay_ms(5000);
    conducteur.arreter();
}

void testAvancer12PoucesMur()
{
    Distance &distance = Distance::getInstance();
    Conducteur &conducteur = Conducteur::getInstance();
    distance.lireDistance(false);
    while (distance.getDistancePouce() > DISTANCE_LIMIT)
    {
        distance.lireDistance(false);
        musique();
        conducteur.suivreLigne(NORMAL);
    };
    conducteur.mettreEnAttente();
}

void testAjustement()
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
        while (!conducteur.estSurLigne())
            conducteur.tournerGauche(NORMAL);
    } while (minuterie.getCount() < 100);

    while (true)
        conducteur.suivreLigne(NORMAL);
}

void testDistanceSegementFPoteau()
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
            minuterie.partirMinuterie(duree);
        }
    };
    LCM disp(&DEMO_DDR, &DEMO_PORT);
    minuterie.arreterMinuterie();
    conducteur.arreter();
    uint16_t distancePoteau = ((minuterie.getCount() + 35) / 3);
    disp << "distance Poteau" << distancePoteau;
    _delay_ms(5000);
    disp.clear();
}

void runTest()
{
    testAvancerEtTournerGauche();
    testAvancerEtTournerGauche2();
    testAjustement();
    testAvancerSegementBD();
    testAvancerApresDemiTour();
    testAvancerSegmentCB1();
    testAvancerSegementBG();
    testAvancer12PoucesMur();
    testAvancerSegementCB2();
    testAvancerSegementBF();
    testAvancerSegementFPoteau();
    testDistanceSegementFPoteau();
    testSuivreLigne();
    testMinuterie();
    testLed();
    testMusique();
    testConducteur();
    testCapteur();
    testCapteurDistance();
    testDemiTour();
}