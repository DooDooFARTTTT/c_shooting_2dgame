#include "bullet.h"


void inizializzaProiettile(CompleteJet *c_jet, Proiettile *p){
    p->direction_degree = c_jet->direzione_degree;
    p->position.x = c_jet->position.x;
    p->position.y = c_jet->position.y;
    float tot_speed = sqrt(c_jet->speed.x * c_jet->speed.x + c_jet->speed.y * c_jet->speed.y);

    tot_speed += 70;

    p->speed.x = tot_speed * -cos(conversioneInRadianti(c_jet->direzione_degree));
    p->speed.y = tot_speed * -sin(conversioneInRadianti(c_jet->direzione_degree));
    p->size = 5;
    p->owner = c_jet->j->name;
    c_jet->proiettili_in_campo[c_jet->numero_proiettili_in_campo] = p;
    c_jet->numero_proiettili_in_campo++;
    DrawText(TextFormat("spd: %.1f",tot_speed), 20, 260, 30, MAGENTA);
}

void disegnaProiettile(CompleteJet *c_jet){
    for(int i = 0; i < c_jet->numero_proiettili_in_campo; i++){
        if(checkIfIsOutOfScreen(c_jet->proiettili_in_campo[i]->position) == OUT_OF_SCREEN){
            free(c_jet->proiettili_in_campo[i]);
            c_jet->numero_proiettili_in_campo--;
            c_jet->proiettili_in_campo[i] = c_jet->proiettili_in_campo[c_jet->numero_proiettili_in_campo];
        }
        c_jet->proiettili_in_campo[i]->position.x += c_jet->proiettili_in_campo[i]->speed.x / FPS;
        c_jet->proiettili_in_campo[i]->position.y += c_jet->proiettili_in_campo[i]->speed.y / FPS;
        DrawCircle(c_jet->proiettili_in_campo[i]->position.x, c_jet->proiettili_in_campo[i]->position.y, c_jet->proiettili_in_campo[i]->size, RED);
    }
}