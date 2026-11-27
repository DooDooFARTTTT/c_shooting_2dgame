#include "raylib.h"
#include "player/player.h"
#include "bullet/bullet.h"
#include "completeJet/completeJet.h"
#include "completeJet/jet.h"
#include "geometry/triangle.h"
#include "jetParts/jetParts.h"

#define FRONT 1
#define BACKWARD -1
#define OUT_OF_SCREEN 67
#define PLAYER 0
#define RESET_INCOHERENCE 104



/*
CompleteJet *builCompleteJetPtr(char *name, Triangolo *t, Engine *e, Airframe *a, Gun *g, Wings *w, int offset_x, int offset_y){
    //ISTANZION UN C_JET
    CompleteJet *c_jet = malloc(sizeof(CompleteJet));

    //COMPONENTI DEL JET
    Jet *j = malloc(sizeof(Jet));
    strcpy(c_jet->j->name, name);
    j->engine = e;
    j->airframe = a;
    j->gun = g;
    j->wings = w;

    //DATI DEL JET
    c_jet->j = j;
    c_jet->peso = e->peso + a->peso + g->peso + w->peso;
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

    return c_jet;
}

void builCompleteJetNemicoPtr(char *name, CompleteJet *c_jet, Engine *e, Airframe *a, Gun *g, Wings *w, int offset_x, int offset_y){
    //COMPONENTI DEL JET
    strcpy(c_jet->j->name, name);
    c_jet->j->engine = e;
    c_jet->j->airframe = a;
    c_jet->j->gun = g;
    c_jet->j->wings = w;

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
*/


/*
void inizializzaTriangleNemico(CompleteJet *c_jet, Triangolo *t, int size, float offset_x, float offset_y){
    t->vertice_assoluto.x = c_jet->position.x - offset_x;
    t->vertice_assoluto.y = c_jet->position.y - size - offset_y;

    t->base_sx_assoluto.x = c_jet->position.x - size - offset_x;
    t->base_sx_assoluto.y = c_jet->position.y + size - offset_y;

    t->base_dx_assoluto.x = c_jet->position.x + size - offset_x;
    t->base_dx_assoluto.y = c_jet->position.y + size - offset_y;

    t->vertice_relativo.x = t->vertice_assoluto.x;
    t->vertice_relativo.y = t->vertice_assoluto.y;

    t->base_sx_relativo.x = t->base_sx_assoluto.x;
    t->base_sx_relativo.y = t->base_sx_assoluto.y;

    t->base_dx_relativo.x = t->base_dx_assoluto.x;
    t->base_dx_relativo.y = t->base_dx_assoluto.y;
}*/

//mi sembra ovvio
static inline double conversioneInRadianti(double degree){
    return (degree * PI) / 180;
}


char checkIfIsOutOfScreen(Vector2 position){
    if(position.x < 0 || position.x > SCREEN_WIDTH || position.y < 0 || position.y > SCREEN_HEIGHT)
        return OUT_OF_SCREEN;
    return 0;
}





void resetta_gioco(CompleteJet *c_jet, Triangolo *t){
    c_jet->directionDegree = START_DIRECTION;
    c_jet->position.x = SCREEN_WIDTH / 2;
    c_jet->position.y = SCREEN_HEIGHT / 2;
    c_jet->speed.x = 0;
    c_jet->speed.y = 0;

    c_jet->triangolo = buildTriangle(c_jet->position, 10);

    for(int i = 0; i < MAX_ALIVE_BULLETS; i++)
        c_jet->proiettiliInCampo[i].alive = false;

    c_jet->numAliveProjectile = 0;
}

/*
void resetta_gioco_nemico(CompleteJet *c_jet, Triangolo *t, int offset_x, int offset_y){
    c_jet->direzione_degree = START_DIRECTION;
    c_jet->position.x = screenWidth / 2 - offset_x;
    c_jet->position.y = screenHeight / 2 - offset_y;
    c_jet->speed.x = 0;
    c_jet->speed.y = 0;
    c_jet->resistenza_attuale = c_jet->resistenza_tot;
    inizializzaTriangle(c_jet, t, 10);

    for(int i = 0; i < c_jet->numero_proiettili_in_campo; i++)
        free(c_jet->proiettili_in_campo[i]);

    c_jet->numero_proiettili_in_campo = 0;
}


}*/



char checkInVita(CompleteJet *c_jet){
    if(c_jet->resistenzaAttuale <= 0)
        return 1;

    return 0;
}


/*
DrawTriangle((Vector2) {screenWidth / 2, screenHeight/2 - 30 }, //VERTICE
(Vector2){screenWidth / 2 - 15, screenHeight/2}, //BASE SINISTRA
(Vector2){screenWidth / 2 + 15, screenHeight/2}, VIOLET); //BASE DESTRA
*/
/*
//stampa
char per_colpire(CompleteJet *aereo_puntato, Proiettile *p){
    Vector2 predizione_posizione;
    predizione_posizione.x = p->position.x;
    predizione_posizione.y = p->position.y;
    float coseno = cos(conversioneInRadianti(p->direction_degree));
    float seno = sin(conversioneInRadianti(p->direction_degree));
    
    while((predizione_posizione.x < screenWidth && predizione_posizione.x > 0) && (predizione_posizione.y < screenHeight && predizione_posizione.y > 0)){
        predizione_posizione.x += -(2 * coseno);
        predizione_posizione.y += -(2 * seno);
        if(CheckCollisionCircles(aereo_puntato->position, 10, predizione_posizione, 5)){
            DrawText("in mira", 20, 330, 30, RED);
            return 1;
        }
    }
    return 0;
}

void spostati_se_bersagliato(CompleteJet *c_nemico_jet, Proiettile *p){
    if(per_colpire(c_nemico_jet, p) == 1){
        accellera(c_nemico_jet);
    }
}*/

int main(){
    InitWindow(900, 560, "raylib [core] example - basic window");
    SetTargetFPS(FPS);

    Engine fast1 = {70, 90, 25, 1000};
    Wings wings1 = {25, 40, 30, 15, 40};
    Airframe dog1 = {45, 25, 90, 10, 200};
    Gun splatter = {15, 20, 4, 100, 500};
    
    Engine fast_cheat = {70, 90, 25, 20000};
    Wings wings_cheat = {25, 40, 30, 85, 150};
    Airframe dog_cheat = {45, 25, 90, 5, 20};
    Gun splatter_cheat = {15, 20, 40, 100, 200};

/*
    //char *name, Triangolo *t, Engine *e, Airframe *a, Gun *g, Wings *w, int offset_x, int offset_y
    CompleteJet c_jet;
    CompleteJet *c_jet_ptr = &c_jet;
    Jet j;
    c_jet_ptr->j = &j;
    Triangolo t;
    Triangolo *t_ptr = &t;
    builCompleteJet("stm1", c_jet_ptr, &fast_cheat, &dog_cheat, &splatter_cheat, &wings_cheat);
    inizializzaTriangle(c_jet_ptr, t_ptr, 10);

    CompleteJet c_nemico_jet;
    CompleteJet *c_nemico_jet_ptr = &c_nemico_jet;

    Jet j_nemico;
    c_nemico_jet_ptr->j = &j_nemico;

    Triangolo t_nemico;
    Triangolo *t_nemico_ptr = &t_nemico;
    builCompleteJetNemico("nemico", c_nemico_jet_ptr, &fast1, &dog1, &splatter, &wings1, 0, 100);
    inizializzaTriangle(c_nemico_jet_ptr, t_nemico_ptr, 10);
*/
    Player *player1 = buildPlayer("gianfranco");
    player1->completeJet = builCompleteJet(buildJet(&fast1, &dog1, &splatter, &wings1), buildTriangle((Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 10), 0, 0);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            if(IsKeyDown(KEY_S)) rallenta(&player1->completeJet);
            if(IsKeyDown(KEY_W)) accellera(&player1->completeJet);
            if(IsKeyDown(KEY_D)) virare(&player1->completeJet, &player1->completeJet.triangolo, 1);
            if(IsKeyDown(KEY_A)) virare(&player1->completeJet, &player1->completeJet.triangolo, -1);
            if(IsKeyDown(KEY_SPACE)){sparaProiettile(&player1->completeJet); DrawText(TextFormat("n.b: %d", player1->completeJet.numAliveProjectile), 20, 300, 30, YELLOW);}
            
            if(IsKeyDown(KEY_R)){
                resetta_gioco(&player1->completeJet, &player1->completeJet.triangolo);
            }

            

            updateComJetPos(&player1->completeJet);
            updateTrianglePos(&player1->completeJet.triangolo, player1->completeJet.speed, player1->completeJet.position);
            ricarica(&player1->completeJet);
            
/*
            if(checkInVita(c_nemico_jet_ptr) == 0){
                checkCollisionBullets(c_nemico_jet_ptr, c_jet_ptr);
                disegnaTriangolo(t_nemico_ptr);
                DrawCircle(c_jet_ptr->position.x, c_jet_ptr->position.y, 10, RED);
                DrawCircle(c_nemico_jet_ptr->position.x, c_nemico_jet_ptr->position.y, 10, RED);
                aggiornaPosizione(c_nemico_jet_ptr, t_nemico_ptr);
            }else{
                DrawText("HAI VINTO", 200, screenHeight/2, 100, RED);
            }
*/

            /*if(player1->completeJet.position.y >= (float)SCREEN_HEIGHT - 10 || player1->completeJet.position.x <= 0 + 10)
                DrawText("Qisha Dodo", (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2, 20, LIGHTGRAY);*/

            



            if(player1->completeJet.numAliveProjectile > 0){
                //disegnaProiettile(&player1->completeJet);
                /*for(int i = 0; i < c_jet_ptr->numero_proiettili_in_campo; i++){
                    spostati_se_bersagliato(c_nemico_jet_ptr, c_jet_ptr->proiettili_in_campo[i]);
                }*/
            }
            
            

            //DrawText(TextFormat("E_hp: %d", c_nemico_jet_ptr->resistenza_attuale), 450, 10, 30, RED);
            DrawText(TextFormat("Y pos: %.2f", player1->completeJet.position.y), 20, 10, 30, RED);
            DrawText(TextFormat("X pos: %.2f", player1->completeJet.position.x), 20, 40, 30, RED);
            DrawText(TextFormat("Y spd: %.2f", player1->completeJet.speed.y), 20, 70, 30, GREEN);
            DrawText(TextFormat("X spd: %.2f", player1->completeJet.speed.x), 20, 100, 30, GREEN);
            DrawText(TextFormat("%.2f", player1->completeJet.weight), 20, SCREEN_HEIGHT - 20, 30, ORANGE);
            drawTotSpeed(&player1->completeJet);
            disegnaTriangolo(&player1->completeJet.triangolo);
            //DrawText(TextFormat("enm spd: %.2f",sqrt(c_nemico_jet_ptr->speed.y * c_nemico_jet_ptr->speed.y) + (c_nemico_jet_ptr->speed.x * c_nemico_jet_ptr->speed.x)), 20, 400, 30, ORANGE);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    

    CloseWindow();
    
    return 0;
}