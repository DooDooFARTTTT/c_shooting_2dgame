#pragma once

typedef struct Wings{
    float peso;
    float costo;
    float resistenza;
    float turn_capability;
    float perfect_turn_speed;
} Wings;

typedef struct Engine{
    float peso;
    float costo;
    float resistenza;
    float potenza;
} Engine;

typedef struct Airframe{
    float peso;
    float costo;
    float resistenza;
    float aereodinamicita;
    float aereofreno;
} Airframe;

typedef struct Gun{
    float peso;
    float costo;
    float damage_per_bullet;
    float munizioni;
    float firerate;
    float ricarica_rimasta;
} Gun;

void buildWings(Wings *wings, float peso, float costo, float resistenza, float turnCapability, float perfectTurnSpd);
void buildEngine(Engine *engine, float peso, float costo, float resistenza, float potenza);
void buildAirframe(Airframe *airframe, float peso, float costo, float resistenza, float aereodinamicita, float aereofreno);
void buildGun(Gun *gun, float peso, float costo, float bulletDamage, float ammo, float firerate);