/**
 * Auteurs : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: definition des methodes de la classe Moteur qui permet le mouvement des roues 
 *              
 * Date: 9 novembre 2021
 * */

#include "sonore.h"

Sonore *Sonore::obj = nullptr;
const double MIDI[][2] = {
    {45, 110},
    {46, 116.5409404},
    {47, 123.4708253},
    {48, 130.8127827},
    {49, 138.5913155},
    {50, 146.832384},
    {51, 155.5634919},
    {52, 164.8137785},
    {53, 174.6141157},
    {54, 184.9972114},
    {55, 195.997718},
    {56, 207.6523488},
    {57, 220},
    {58, 233.0818808},
    {59, 246.9416506},
    {60, 261.6255653},
    {61, 277.182631},
    {62, 293.6647679},
    {63, 311.1269837},
    {64, 329.6275569},
    {65, 349.2282314},
    {66, 369.9944227},
    {67, 391.995436},
    {68, 415.3046976},
    {69, 440},
    {70, 466.1637615},
    {71, 493.8833013},
    {72, 523.2511306},
    {73, 554.365262},
    {74, 587.3295358},
    {75, 622.2539674},
    {76, 659.2551138},
    {77, 698.4564629},
    {78, 739.9888454},
    {79, 783.990872},
    {80, 830.6093952},
    {81, 880},
    {82, 932.328},
    {83, 987.767},
    {84, 1046.502},
    {85, 1108.731},
    {86, 1174.659},
    {87, 1244.508},
    {88, 1318.51},
    {89, 1396.913},
    {90, 1479.978},
    {91, 1567.982},
    {92, 1661.219},
    {93, 1760},
    {94, 1864.655},
    {95, 1975.533}

};

Sonore &Sonore::getInstance()
{
    if (!obj)
    {
        obj = new Sonore();
    }
    return *obj;
}

Sonore::~Sonore()
{
    free(obj);
}

Sonore::Sonore()
{
    DDRB |= (1 << PIN3) | (1 << PIN5);
}

void Sonore::initialiser()
{
    TCCR0A |= (1 << WGM01) | (1 << COM0A0);
    TCCR0B |= (1 << CS02);
}

void Sonore::jouerNote(uint8_t note)
{
    initialiser();
    int prescaler = 256;
    if (note > 45 && note <= 95)
    {
        OCR0A = F_CPU / (2 * MIDI[note - 45][FrequenceIdx] * prescaler);
    }
}

void Sonore::jouerFrequence(uint16_t frequence)
{
    initialiser();
    uint8_t prec = MIDI[0][FrequenceIdx];
    for (int i = 1; i < 50; i++)
    {

        if (frequence >= prec && frequence < MIDI[i][FrequenceIdx])
        {
            jouerNote(45 + i);
            break;
        }
        else if (frequence == MIDI[i][FrequenceIdx])
        {
            jouerNote(45 + i);
            break;
        }
        else
        {
            prec = MIDI[i][FrequenceIdx];
        }
    }
}

void Sonore::arreter()
{
    OCR0A = 0;
    TCCR0A = 0;
    TCCR0B = 0;
}