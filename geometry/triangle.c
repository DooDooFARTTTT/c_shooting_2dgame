#include "triangle.h"
#include "completeJet/completeJet.h"

void buildTriangle(Triangolo *t, Vector2 position, int size){
    t->vertAbs.x = position.x;
    t->vertAbs.y = position.y - size;

    t->baseSxAbs.x = position.x - size;
    t->baseSxAbs.y = position.y + size;

    t->baseDxAbs.x = position.x + size;
    t->baseDxAbs.y = position.y + size;

    t->vertRel.x = vertAbs.x;
    t->vertRel.y = vertAbs.y;

    t->baseSxRel.x = baseSxRel.x;
    t->baseSxRel.y = baseSxRel.y;

    t->baseDxRel.x = baseDxRel.x;
    t->baseDxRel.y = baseDxRel.y;
}

void disegnaTriangolo(Triangolo *t){
    DrawTriangle(t->vertice_relativo, t->base_sx_relativo, t->base_dx_relativo, BLUE);
}

void rotate_triangolo(Triangolo *t, Vector2 position, float directionDegree){
    Vector2 center = {position.x, position.y};
    float cos = cos(conversioneInRadianti(direzione_degree - 90));
    float sin = sin(conversioneInRadianti(direzione_degree - 90));

    Vector2 vertice = t->vertice_assoluto;
    Vector2 base_sx = t->base_sx_assoluto;
    Vector2 base_dx = t->base_dx_assoluto;

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

    vertice.x = vertice2.x * cos - vertice2.y * sin;
    vertice.y = vertice2.x * sin + vertice2.y * cos;

    base_sx.x = base_sx2.x * cos - base_sx2.y * sin;
    base_sx.y = base_sx2.x * sin + base_sx2.y * cos;

    base_dx.x = base_dx2.x * cos - base_dx2.y * sin;
    base_dx.y = base_dx2.x * sin + base_dx2.y * cos;


    vertice.x  = vertice.x  + center.x;
    vertice.y  = vertice.y  + center.y;

    base_sx.x  = base_sx.x  + center.x;
    base_sx.y  = base_sx.y  + center.y;

    base_dx.x  = base_dx.x  + center.x;
    base_dx.y  = base_dx.y  + center.y;

    t->vertice_relativo = vertice;
    t->base_sx_relativo = base_sx;
    t->base_dx_relativo = base_dx;
}
