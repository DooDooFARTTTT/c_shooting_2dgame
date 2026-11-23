#include "raylib.h"
#include "jet.h"
#include "bullet/bullet.h"

typedef struct{
    Jet *j;
    Proiettile *proiettili_in_campo[100];
    Vector2 speed;
    Vector2 position;
    float accellerazione_per_frame;
    float stall_speed;
    float peso;
    float direzione_degree;
    int numero_proiettili_in_campo;
    int resistenza_tot;
    int resistenza_attuale;
} CompleteJet;