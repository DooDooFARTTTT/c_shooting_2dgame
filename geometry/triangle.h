#pragma once

#include "raylib.h"

typedef struct{
    Vector2 vertAbs;
    Vector2 baseSxAbs;
    Vector2 baseDxAbs;

    Vector2 vertRel;
    Vector2 baseSxRel;
    Vector2 baseDxRel;
} Triangolo;


void buildTriangle(Triangolo *t, Vector2 position, int size);
void disegnaTriangolo(Triangolo *t);
void rotate_triangolo(Triangolo *t, Vector2 position, float directionDegree);