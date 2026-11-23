#include "jet.h"
#include "jetParts/jetParts.h"



void buildJet(Jet* jet, char *name, Engine *e, Airframe *a, Gun *g, Wings *w){
    strcpy(jet->name, name);
    jet->engine = e;
    jet->airframe = a;
    jet->gun = g;
    jet->wings = w;
}