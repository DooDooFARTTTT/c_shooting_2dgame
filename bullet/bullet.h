#pragma once

#include "raylib.h"

#define STANDARD_BULLET_SIZE 5
#define FPS 60


typedef struct Proiettile{
    float directionDegree;
    char size;
    bool alive;
    Vector2 position;
    Vector2 speed;
} Proiettile;

void BuildProiettile(Proiettile *p, float directionDegree, Vector2 speed, Vector2 position);
void disegnaProiettile(Proiettile *proiettile);
void updateBulletPos(Proiettile* proiettile);
void updateBulletPos(Proiettile* proiettile);