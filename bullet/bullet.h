#include "raylib.h"


typedef struct{
    float direction_degree;
    Vector2 position;
    Vector2 speed;
    char *owner;
    char size;
} Proiettile;

void inizializzaProiettile(CompleteJet *c_jet, Proiettile *p); 
void disegnaProiettile(CompleteJet *c_jet);