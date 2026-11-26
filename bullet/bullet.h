#include "raylib.h"

#define STANDARD_BULLET_SIZE 5

typedef struct Proiettile{
    float directionDegree;
    char size;
    Vector2 position;
    Vector2 speed;
} Proiettile;

void BuildProiettile(Proiettile *p, float directionDegree, Vector2 speed, Vector2 position); 
void disegnaProiettile(CompleteJet *c_jet);