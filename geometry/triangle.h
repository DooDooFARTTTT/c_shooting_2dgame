#include "raylib.h"

typedef struct{
    Vector2 vertice_assoluto;
    Vector2 base_sx_assoluto;
    Vector2 base_dx_assoluto;

    Vector2 vertice_relativo;
    Vector2 base_sx_relativo;
    Vector2 base_dx_relativo;
} Triangolo;

void inizializzaTriangle(CompleteJet *c_jet, Triangolo *t, int size);
void disegnaTriangolo(Triangolo *t);
void disegnaProiettile(CompleteJet *c_jet);