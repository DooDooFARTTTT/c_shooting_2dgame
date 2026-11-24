#include "triangle.h"


void inizializzaTriangle(CompleteJet *c_jet, Triangolo *t, int size){
    t->vertice_assoluto.x = c_jet->position.x;
    t->vertice_assoluto.y = c_jet->position.y - size;

    t->base_sx_assoluto.x = c_jet->position.x - size;
    t->base_sx_assoluto.y = c_jet->position.y + size;

    t->base_dx_assoluto.x = c_jet->position.x + size;
    t->base_dx_assoluto.y = c_jet->position.y + size;

    t->vertice_relativo.x = t->vertice_assoluto.x;
    t->vertice_relativo.y = t->vertice_assoluto.y;

    t->base_sx_relativo.x = t->base_sx_assoluto.x;
    t->base_sx_relativo.y = t->base_sx_assoluto.y;

    t->base_dx_relativo.x = t->base_dx_assoluto.x;
    t->base_dx_relativo.y = t->base_dx_assoluto.y;
}

void disegnaTriangolo(Triangolo *t){
    DrawTriangle(t->vertice_relativo, t->base_sx_relativo, t->base_dx_relativo, BLUE);
}