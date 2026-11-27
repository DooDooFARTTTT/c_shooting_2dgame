#include "triangle.h"
#include <math.h>

void buildTriangle(Triangolo *t, Vector2 position, int size){
    t->vertAbs.x = position.x;
    t->vertAbs.y = position.y - size;

    t->baseSxAbs.x = position.x - size;
    t->baseSxAbs.y = position.y + size;

    t->baseDxAbs.x = position.x + size;
    t->baseDxAbs.y = position.y + size;

    t->vertRel.x = t->vertAbs.x;
    t->vertRel.y = t->vertAbs.y;

    t->baseSxRel.x = t->baseSxRel.x;
    t->baseSxRel.y = t->baseSxRel.y;

    t->baseDxRel.x = t->baseDxRel.x;
    t->baseDxRel.y = t->baseDxRel.y;
}

void disegnaTriangolo(Triangolo *t){
    DrawTriangle(t->vertRel, t->baseSxRel, t->baseDxRel, BLUE);
}

void rotate_triangolo(Triangolo *t, Vector2 position, float directionDegree){
    Vector2 center = {position.x, position.y};
    float coseno = cos(conversioneInRadianti(directionDegree - 90));
    float seno = sin(conversioneInRadianti(directionDegree - 90));

    Vector2 vertice = t->vertAbs;
    Vector2 base_sx = t->baseSxAbs;
    Vector2 base_dx = t->baseDxAbs;

    Vector2 vertice2;
    Vector2 base_sx2;
    Vector2 base_dx2;

    vertice.x -= center.x;
    vertice.y -= center.y;

    base_sx.x -= center.x;
    base_sx.y -= center.y;

    base_dx.x -= center.x;
    base_dx.y -= center.y;

    vertice2.x = vertice.x;
    vertice2.y = vertice.y;

    base_sx2.x = base_sx.x;
    base_sx2.y = base_sx.y;

    base_dx2.x = base_dx.x;
    base_dx2.y = base_dx.y;

    vertice.x = vertice2.x * coseno - vertice2.y * seno;
    vertice.y = vertice2.x * seno + vertice2.y * coseno;

    base_sx.x = base_sx2.x * coseno - base_sx2.y * seno;
    base_sx.y = base_sx2.x * seno + base_sx2.y * coseno;

    base_dx.x = base_dx2.x * coseno - base_dx2.y * seno;
    base_dx.y = base_dx2.x * seno + base_dx2.y * coseno;


    vertice.x  = vertice.x  + center.x;
    vertice.y  = vertice.y  + center.y;

    base_sx.x  = base_sx.x  + center.x;
    base_sx.y  = base_sx.y  + center.y;

    base_dx.x  = base_dx.x  + center.x;
    base_dx.y  = base_dx.y  + center.y;

    t->vertAbs = vertice;
    t->baseSxAbs = base_sx;
    t->baseDxRel = base_dx;
}

void updateTrianglePos(Triangolo *t, Vector2 speed, Vector2 position){
    t->vertAbs.x += speed.x / FPS;
    t->vertAbs.y += speed.y / FPS;

    t->baseSxAbs.x += speed.x / FPS;
    t->baseSxAbs.y += speed.y / FPS;

    t->baseDxAbs.x += speed.x / FPS;
    t->baseDxAbs.y += speed.y / FPS;

    t->vertRel.x += speed.x / FPS;
    t->vertRel.y += speed.y / FPS;

    t->baseSxRel.x += speed.x / FPS;
    t->baseSxRel.y += speed.y / FPS;

    t->baseDxRel.x += speed.x / FPS;
    t->baseDxRel.y += speed.y / FPS;
}

//mi sembra ovvio
static inline double conversioneInRadianti(double degree){
    return (degree * PI) / 180;
}