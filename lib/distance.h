#ifndef Distance_H
#define Distance_H
#define DISTANCE PA6
#include <avr/io.h>
#include <stdlib.h>
#define DISTANCE_MAX 80
#define TAILLE_ECHANTILLION 16
class Distance
{
public:
  static Distance &getInstance();
  void lireDistance(bool isPoteau);
  uint8_t getDistanceCm();
  uint8_t getDistancePouce();
  void setDitanceCm(uint8_t distance);
  bool distanceAffichableEnCm = false;

private:
  static Distance *obj;
  Distance();
  ~Distance();
  uint8_t distanceCm = DISTANCE_MAX;
  uint8_t distancePouce;
  double constanteConversion = 2.54;
};

#endif /* Distance_H */
