#include "raylib.h"

typedef struct{
    Vector2 vertice_assoluto;
    Vector2 base_sx_assoluto;
    Vector2 base_dx_assoluto;

    Vector2 vertice_relativo;
    Vector2 base_sx_relativo;
    Vector2 base_dx_relativo;
} Triangolo;