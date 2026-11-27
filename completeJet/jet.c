#include "jet.h"

Jet buildJet(Engine *e, Airframe *a, Gun *g, Wings *w){
    Jet jet = {*e, *a, *g, *w};
    return jet;
}