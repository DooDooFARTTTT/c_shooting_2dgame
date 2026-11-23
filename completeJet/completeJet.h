#include "raylib.h"
#include "jet.h"
#include "bullet/bullet.h"

#define START_DIRECTION 90

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

void builCompleteJetNemico(CompleteJet *c_jet, Jet* jet, int offset_x, int offset_y);