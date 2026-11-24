#include "raylib.h"
#include "jet.h"
#include "bullet/bullet.h"
#include "geometry/triangle.h"

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
void sparaProiettile(CompleteJet *c_jet);
void virare(CompleteJet *c_jet, Triangolo *t, int verso);
void ricarica(CompleteJet *c_jet);
void accellera(CompleteJet *c_jet);
//Dati 2 vettori, passati con CompletedJet, aereoFreno al aereofreno del jet, applica una resistenza aereodinamica verso la direnzione di viaggio
void rallenta(CompleteJet *c_jet);

//dato UN VETTORE, l'accellerazione per frame, l'aereodinamica e la velocita, calcolo quanto è l'accellerazione per ogni frame
float calculate_accelleration(float accellerazione_per_frame, float aereodinamicita, float speed, char stampa);
void drawTotSpeed(CompleteJet *c_jet);