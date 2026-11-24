#include "completeJet.h"
#include "stdlib.h"

const int screenWidth = 900;
const int screenHeight = 562;
const int FPS = 60;

void builCompleteJetNemico(CompleteJet *c_jet, Jet* jet, int offset_x, int offset_y){
    //COMPONENTI DEL JET
    c_jet->j = jet;

    float peso = c_jet->j->engine->peso + c_jet->j->airframe->peso + c_jet->j->gun->peso + c_jet->j->wings->peso;

    //DATI DEL JET
    c_jet->peso = peso;
    c_jet->direzione_degree = START_DIRECTION;
    c_jet->speed.x = 0;
    c_jet->speed.y = 0;
    c_jet->position.x = screenWidth / 2 - offset_x;
    c_jet->position.y = screenHeight / 2 - offset_y;
    c_jet->accellerazione_per_frame =  8.0f * (c_jet->j->engine->potenza / c_jet->peso);
    c_jet->stall_speed = c_jet->peso / 15;
    c_jet->numero_proiettili_in_campo = 0;
    c_jet->resistenza_tot = c_jet->j->engine->resistenza + c_jet->j->airframe->resistenza + c_jet->j->wings->resistenza;
    c_jet->resistenza_attuale = c_jet->resistenza_tot;
}

//CODICE RISCHIOSO
void sparaProiettile(CompleteJet *c_jet){
    if(c_jet->j->gun->ricarica_rimasta > 0)
        return; 
    
    if(c_jet->numero_proiettili_in_campo >= sizeof(c_jet->proiettili_in_campo) / sizeof(Proiettile*)){
        free(c_jet->proiettili_in_campo[c_jet->numero_proiettili_in_campo - 1]);
        c_jet->numero_proiettili_in_campo--;    //da fixare per eliminare il proiettile più vecchio
    }

    Proiettile *p = malloc(sizeof(Proiettile));
    if (p == NULL) {
        printf("Errore: Memoria Proiettile\n");
        return;
    }

    inizializzaProiettile(c_jet, p);
    c_jet->j->gun->ricarica_rimasta = c_jet->j->gun->firerate;
}


void virare(CompleteJet *c_jet, Triangolo *t, int verso){
    float x_speed = c_jet->speed.x;
    float y_speed = c_jet->speed.y;
    float tot_speed = sqrt((x_speed * x_speed) + (y_speed * y_speed));

    if(tot_speed <= c_jet->stall_speed)
        return;



    float ratio = (c_jet->j->wings->perfect_turn_speed * 100) / tot_speed;
    ratio = fabs((ratio - 100) / 100) + 1;



    float degree_rotated = (c_jet->j->wings->turn_capability / ratio) / 15;

    if(verso == 1)
        c_jet->direzione_degree += degree_rotated;
    else
        c_jet->direzione_degree -= degree_rotated;
    ricalcolo_gognometrico_velocita(c_jet, tot_speed);
    c_jet->speed.x *= 1 - degree_rotated / (FPS * 1);
    c_jet->speed.y *= 1 - degree_rotated / (FPS * 1);
    rotate_triangolo(c_jet, t);

    DrawText(TextFormat("Turn capacity: %.4f",degree_rotated), 20, 220, 30, PURPLE);
}

void ricarica(CompleteJet *c_jet){
    if(c_jet->j->gun->ricarica_rimasta > 0)
        c_jet->j->gun->ricarica_rimasta -= 1000 / FPS;
    
    DrawText(TextFormat("ricarica: %.2f",c_jet->j->gun->ricarica_rimasta), 20, 360, 30, GREEN);
}

//dati i due vettori per riferimento, e la direzione del jet, determina l'accellerazione per i due vettori
//e li moltiplica per il cos "x" e il sin "y" basato sulla conversione in radianti della direzione degree.
//il tutto diviso per il numero di FPS
void accellera(CompleteJet *c_jet){
    float tot_speed = sqrt((c_jet->speed.x * c_jet->speed.x) + (c_jet->speed.y * c_jet->speed.y));

    float accellerazione = calculate_accelleration(c_jet->accellerazione_per_frame, c_jet->j->airframe->aereodinamicita, tot_speed, 0);

    c_jet->speed.x -= accellerazione * cos((conversioneInRadianti(c_jet->direzione_degree))) / FPS;
    c_jet->speed.y -= accellerazione * sin((conversioneInRadianti(c_jet->direzione_degree))) / FPS;
}