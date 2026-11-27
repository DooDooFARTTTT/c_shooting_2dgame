#pragma once

#include "..\jetParts/jetParts.h"

typedef struct Jet{
    Engine engine;
    Airframe airframe;
    Gun gun;
    Wings wings;
}Jet;


Jet buildJet(Engine *e, Airframe *a, Gun *g, Wings *w);