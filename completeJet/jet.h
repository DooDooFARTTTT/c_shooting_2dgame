#include "raylib.h"
#include "jetParts/jetParts.h"

typedef struct{
    char name[32];
    Engine *engine;
    Airframe *airframe;
    Gun *gun;
    Wings *wings;
} Jet;



void buildJet(Jet* jet, char *name, Engine *e, Airframe *a, Gun *g, Wings *w);