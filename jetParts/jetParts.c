#include "jetParts.h"

void buildWings(Wings *wings, float peso, float costo, float resistenza, float turnCapability, float perfectTurnSpd){
    wings->peso = peso;
    wings->costo = costo;
    wings->resistenza = resistenza;
    wings->turn_capability = turnCapability;
    wings->perfect_turn_speed = perfectTurnSpd;
}

void buildEngine(Engine *engine, float peso, float costo, float resistenza, float potenza){
    engine->peso = peso;
    engine->costo = costo;
    engine->resistenza = resistenza;
    engine->potenza = potenza;
}

void buildAirframe(Airframe *airframe, float peso, float costo, float resistenza, float aereodinamicita, float aereofreno){
    airframe->peso = peso;
    airframe->costo = costo;
    airframe->resistenza = resistenza;
    airframe->aereodinamicita = aereodinamicita;
    airframe->aereofreno = aereofreno;
}

void buildGun(Gun* gun, float peso, float costo, float bulletDamage, float ammo, float firerate){
    gun->peso = peso;
    gun->costo = costo;
    gun->damage_per_bullet = bulletDamage;
    gun->munizioni = ammo;
    gun->firerate = firerate;
    gun->ricarica_rimasta = 0;
}
