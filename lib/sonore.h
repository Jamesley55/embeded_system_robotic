
#ifndef SONORE_H
#define SONORE_H
#include <avr/io.h>
#include <stdlib.h>

class Sonore
{
public:
    static Sonore &getInstance();
    void jouerNote(uint8_t note);
    void jouerFrequence(uint16_t frequence);
    void initialiser();
    void arreter();
    void setNote(uint8_t Note);

private:
    static Sonore *obj;
    Sonore();
    ~Sonore();
    uint8_t note;
    const uint8_t NoteIdx = 0;
    const uint8_t FrequenceIdx = 1;
    const uint8_t periodIdx = 2;
    const uint8_t tempActifIdx = 3;
};
#endif