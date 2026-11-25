#include "jet.h"

void buildJet(Jet* jet, Engine *e, Airframe *a, Gun *g, Wings *w){
    jet->engine = *e;
    jet->airframe = *a;
    jet->gun = *g;
    jet->wings = *w;
}