#include "bullet.h"

void BuildProiettile(Proiettile *p, float directionDegree, Vector2 speed, Vector2 position){
    float totSpeed = sqrt(speed.x * speed.x + speed.y * speed.y);

    totSpeed += 70;

    p->directionDegree = directionDegree;
    p->size = STANDARD_BULLET_SIZE;
    p->position.x = position.x;
    p->position.y = position.y;
    p->speed.x = totSpeed * -cos(conversioneInRadianti(directionDegree));
    p->speed.y = totSpeed * -sin(conversioneInRadianti(directionDegree));
}

void disegnaProiettile(Proiettile *proiettile){
    DrawCircle(proiettile->position.x, proiettile->position.y, proiettile->size, RED);
}

void updateBulletPos(Proiettile* proiettile){
    proiettile->position.x += proiettile->speed.x / FPS;
    proiettile->position.y += proiettile->speed.y / FPS;
}

void updateBulletPos(Proiettile* proiettile){
    float totSpeed = sqrt(proiettile->speed.x * proiettile->speed.x + proiettile->speed.y * proiettile->speed.y);
    DrawText(TextFormat("spd: %.1f", totSpeed), 20, 260, 30, MAGENTA);
}

/* boh la salvo cosi perchè si tanto mica pesa
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
}*/


/*questa deve diventare una funzione spara in c-jet, e poi era il builder di proiettile
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
}*/