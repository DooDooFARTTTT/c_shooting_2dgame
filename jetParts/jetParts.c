#include "jetParts.h"

void buildWings(float peso, float costo, float resistenza, float turnCapability, float perfectTurnSpd){
    Wings newWings = {peso, costo, resistenza, turnCapability, perfectTurnSpd};
    return newWings;
}

void buildEngine(float peso, float costo, float resistenza, float potenza){
    Engine newEngine = {peso, costo, resistenza, potenza};
    return newEngine;
}

void buildAirframe(float peso, float costo, float resistenza, float aereodinamicita, float aereofreno){
    Airframe newAirframe = {peso, costo, resistenza, aereodinamicita, aereofreno};
    return newAirframe;
}

void buildGun(float peso, float costo, float bulletDamage, float ammo, float firerate){
    Gun newGun = {peso, costo, bulletDamage, ammo, firerate, 0};
    return newGun;
}
