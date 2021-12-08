
/**
 * Autheur : Mathieu  Benoit, Jamesley Joseph , Philippe Hadjis, Nina Lounici
 * Description: header de la classe Minuterie qui definie une  minuterie par interruption 
 *              
 * Date: 29 octobre 2021
 * */
#ifndef MINUTERIE_H
#define MINUTERIE_H
#include <stdlib.h>
#include <avr/io.h>
class Minuterie
{
public:

   void partirMinuterie(uint16_t duree);
   static Minuterie& getInstance();
   void arreterMinuterie();
   void resetCount();
   uint16_t getCount();
   void incrementCount();
   
private:
   volatile uint16_t count_ = 0;
   static Minuterie *obj;
   Minuterie();
   ~Minuterie();
   // donnees membres
};

#endif /* MINUTERIE_H */
