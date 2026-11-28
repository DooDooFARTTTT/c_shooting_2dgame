#pragma once

#include "raylib.h"
#include "jet.h"
#include "..\bullet/bullet.h"
#include "..\geometry/triangle.h"

#define START_DIRECTION 90
#define FPS 60
#define MAX_ALIVE_BULLETS 100

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 562

typedef struct CompleteJet{
    Jet jet;
    Triangolo triangolo;
    Proiettile proiettiliInCampo[100];
    
    Vector2 speed;
    Vector2 position;

    float accPerFrame;
    float stallSpeed;
    float weight;
    float directionDegree;
    
    int numAliveProjectile;
    int resistenzaTot;
    int resistenzaAttuale;
}CompleteJet;

CompleteJet builCompleteJet(Jet jet, Triangolo triangolo, int offsetX, int offsetY);
void sparaProiettile(CompleteJet *c_jet);
void deallocateBullet(CompleteJet* c_jet, Proiettile *proiettile);
void virare(CompleteJet *c_jet, Triangolo *t, int verso);
void ricarica(CompleteJet *c_jet);
void accellera(CompleteJet *c_jet);
//Dati 2 vettori, passati con CompletedJet, aereoFreno al aereofreno del jet, applica una resistenza aereodinamica verso la direnzione di viaggio
void rallenta(CompleteJet *c_jet);

//dato UN VETTORE, l'accellerazione per frame, l'aereodinamica e la velocita, calcolo quanto è l'accellerazione per ogni frame
float calculate_accelleration(float accellerazione_per_frame, float aereodinamicita, float speed, char stampa);
void drawTotSpeed(CompleteJet *c_jet);
void updateComJetPos(CompleteJet* c_jet);
void ricalcolo_gognometrico_velocita(CompleteJet *c_jet, float tot_speed);
float calcolaResistenza(float speed, float aereodinamicita);
static inline double conversioneInRadianti(double degree);