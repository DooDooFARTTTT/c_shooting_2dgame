#include "triangle.h"
#include "completeJet/completeJet.h"

void buildTriangle(Triangolo *t, Vector2 position, int size){
    t->vertice_assoluto.x = position.x;
    t->vertice_assoluto.y = position.y - size;

    t->base_sx_assoluto.x = position.x - size;
    t->base_sx_assoluto.y = position.y + size;

    t->base_dx_assoluto.x = position.x + size;
    t->base_dx_assoluto.y = position.y + size;

    t->vertice_relativo.x = vertice_assoluto.x;
    t->vertice_relativo.y = vertice_assoluto.y;

    t->base_sx_relativo.x = base_sx_assoluto.x;
    t->base_sx_relativo.y = base_sx_assoluto.y;

    t->base_dx_relativo.x = base_dx_assoluto.x;
    t->base_dx_relativo.y = base_dx_assoluto.y;
}

void disegnaTriangolo(Triangolo *t){
    DrawTriangle(t->vertice_relativo, t->base_sx_relativo, t->base_dx_relativo, BLUE);
}

void rotate_triangolo(CompleteJet *c_jet, Triangolo *t){
    Vector2 center = {c_jet->position.x, c_jet->position.y};
    float coseno = cos(conversioneInRadianti(c_jet->direzione_degree - 90));
    float seno = sin(conversioneInRadianti(c_jet->direzione_degree - 90));

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

    t->vertice_relativo = vertice;
    t->base_sx_relativo = base_sx;
    t->base_dx_relativo = base_dx;
}
