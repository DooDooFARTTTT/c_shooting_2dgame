#include "raylib.h"
#include "completeJet/completeJet.h"

typedef struct{
    Vector2 vertice_assoluto;
    Vector2 base_sx_assoluto;
    Vector2 base_dx_assoluto;

    Vector2 vertice_relativo;
    Vector2 base_sx_relativo;
    Vector2 base_dx_relativo;
} Triangolo;

void buildTriangle(CompleteJet *c_jet, Triangolo *t, int size);
void disegnaTriangolo(Triangolo *t);
void disegnaProiettile(CompleteJet *c_jet);
void rotate_triangolo(CompleteJet *c_jet, Triangolo *t);