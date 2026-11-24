#include "raylib.h"
#include "player/player.h"
#include "bullet/bullet.h"
#include "completeJet/completeJet.h"
#include "completeJet/jet.h"
#include "geometry/triangle.h"
#include "jetParts/jetParts.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FRONT 1
#define BACKWARD -1
#define OUT_OF_SCREEN 67
#define PLAYER 0
#define RESET_INCOHERENCE 104

const int FPS = 60;
const int screenWidth = 900;
const int screenHeight = 562;



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
    if(position.x < 0 || position.x > screenWidth || position.y < 0 || position.y > screenHeight)
        return OUT_OF_SCREEN;
    return 0;
}

//Data la velocità di UN VETTORE, e il valore aereodinamico dell'airframe di un jet, ritorna un float di resistenza aereodinamica
float calcolaResistenza(float speed, float aereodinamicita){
    return speed * fabs(speed) * (aereodinamicita / 1000.0f);
}

//Dati 2 vettori, passati con CompletedJet, aereoFreno al aereofreno del jet, applica una resistenza aereodinamica verso la direnzione di viaggio
void rallenta(CompleteJet *c_jet){
    c_jet->speed.x -= calcolaResistenza(c_jet->speed.x, c_jet->j->airframe->aereodinamicita) / (c_jet->j->airframe->aereofreno / 2);
    c_jet->speed.y -= calcolaResistenza(c_jet->speed.y, c_jet->j->airframe->aereodinamicita) / (c_jet->j->airframe->aereofreno / 2);
}

//dato UN VETTORE, l'accellerazione per frame, l'aereodinamica e la velocita, calcolo quanto è l'accellerazione per ogni frame
float calculate_accelleration(float accellerazione_per_frame, float aereodinamicita, float speed, char stampa){
    float resistenza = calcolaResistenza(speed, aereodinamicita);
    if(stampa == 0)
        DrawText(TextFormat("X: %.4f",resistenza), 20, 130, 30, WHITE);
    else
        DrawText(TextFormat("Y: %.4f",resistenza), 20, 160, 30, WHITE);

    if(resistenza > 0)
        return accellerazione_per_frame - resistenza;
    return accellerazione_per_frame + resistenza;
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

void ricalcolo_gognometrico_velocita(CompleteJet *c_jet, float tot_speed){
    float x_speed = -tot_speed * cos((conversioneInRadianti(c_jet->direzione_degree)));
    float y_speed = -tot_speed * sin((conversioneInRadianti(c_jet->direzione_degree)));
    c_jet->speed.x = x_speed;
    c_jet->speed.y = y_speed;
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



void resetta_gioco(CompleteJet *c_jet, Triangolo *t){
    c_jet->direzione_degree = START_DIRECTION;
    c_jet->position.x = screenWidth / 2;
    c_jet->position.y = screenHeight / 2;
    c_jet->speed.x = 0;
    c_jet->speed.y = 0;

    inizializzaTriangle(c_jet, t, 10);

    for(int i = 0; i < c_jet->numero_proiettili_in_campo; i++)
        free(c_jet->proiettili_in_campo[i]);

    c_jet->numero_proiettili_in_campo = 0;
}

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

void aggiornaPosizione(CompleteJet *c_jet, Triangolo *t){
    c_jet->position.x += c_jet->speed.x / FPS;
    c_jet->position.y += c_jet->speed.y / FPS;


    t->vertice_assoluto.x += c_jet->speed.x / FPS;
    t->vertice_assoluto.y += c_jet->speed.y / FPS;

    t->base_sx_assoluto.x += c_jet->speed.x / FPS;
    t->base_sx_assoluto.y += c_jet->speed.y / FPS;

    t->base_dx_assoluto.x += c_jet->speed.x / FPS;
    t->base_dx_assoluto.y += c_jet->speed.y / FPS;

    t->vertice_relativo.x += c_jet->speed.x / FPS;
    t->vertice_relativo.y += c_jet->speed.y / FPS;

    t->base_sx_relativo.x += c_jet->speed.x / FPS;
    t->base_sx_relativo.y += c_jet->speed.y / FPS;

    t->base_dx_relativo.x += c_jet->speed.x / FPS;
    t->base_dx_relativo.y += c_jet->speed.y / FPS;
}

void drawTotSpeed(CompleteJet *c_jet){
    float tot_speed = sqrt((c_jet->speed.x * c_jet->speed.x) + (c_jet->speed.y * c_jet->speed.y));

    if(tot_speed <= c_jet->stall_speed)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, MAROON);
    else if(tot_speed <= c_jet->j->wings->perfect_turn_speed * 0.55)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, RED);
    else if(tot_speed <= c_jet->j->wings->perfect_turn_speed * 0.80)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, ORANGE);
    else if(tot_speed > c_jet->j->wings->perfect_turn_speed * 0.80 && tot_speed < c_jet->j->wings->perfect_turn_speed * 0.95 )
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, YELLOW);
    else if(tot_speed >= c_jet->j->wings->perfect_turn_speed * 0.95 && tot_speed <= c_jet->j->wings->perfect_turn_speed * 1.05)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, GREEN);
    else if(tot_speed > c_jet->j->wings->perfect_turn_speed * 1.05)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, BLUE);
}



char checkInVita(CompleteJet *c_jet){
    if(c_jet->resistenza_attuale <= 0)
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


    while (!WindowShouldClose()){
        BeginDrawing();
            if(IsKeyDown(KEY_S)) rallenta(c_jet_ptr);
            if(IsKeyDown(KEY_W)) accellera(c_jet_ptr);
            if(IsKeyDown(KEY_D)) virare(c_jet_ptr, t_ptr, 1);
            if(IsKeyDown(KEY_A)) virare(c_jet_ptr, t_ptr, -1);
            if(IsKeyDown(KEY_SPACE)){sparaProiettile(c_jet_ptr); DrawText(TextFormat("n.b: %d",c_jet_ptr->numero_proiettili_in_campo), 20, 300, 30, YELLOW);}
            
            if(IsKeyDown(KEY_R)) {resetta_gioco(c_jet_ptr, t_ptr); resetta_gioco_nemico(c_nemico_jet_ptr, t_nemico_ptr, 0, 100);}

            ClearBackground(BLACK);
            aggiornaPosizione(c_jet_ptr, t_ptr);
            ricarica(c_jet_ptr);
            

            if(checkInVita(c_nemico_jet_ptr) == 0){
                checkCollisionBullets(c_nemico_jet_ptr, c_jet_ptr);
                disegnaTriangolo(t_nemico_ptr);
                DrawCircle(c_jet_ptr->position.x, c_jet_ptr->position.y, 10, RED);
                DrawCircle(c_nemico_jet_ptr->position.x, c_nemico_jet_ptr->position.y, 10, RED);
                aggiornaPosizione(c_nemico_jet_ptr, t_nemico_ptr);
            }else{
                DrawText("HAI VINTO", 200, screenHeight/2, 100, RED);
            }

            if(c_jet_ptr->position.y >= (float)screenHeight - 10 || c_jet_ptr->position.x <= 0 + 10)
                DrawText("Qisha Dodo", (float)screenWidth / 2, (float)screenHeight / 2, 20, LIGHTGRAY);

            disegnaTriangolo(t_ptr);



            if(c_jet_ptr->numero_proiettili_in_campo > 0){
                disegnaProiettile(c_jet_ptr);
                for(int i = 0; i < c_jet_ptr->numero_proiettili_in_campo; i++){
                    spostati_se_bersagliato(c_nemico_jet_ptr, c_jet_ptr->proiettili_in_campo[i]);
                }
            }
            
            

            DrawText(TextFormat("E_hp: %d", c_nemico_jet_ptr->resistenza_attuale), 450, 10, 30, RED);
            DrawText(TextFormat("Y pos: %.2f",c_jet_ptr->position.y), 20, 10, 30, RED);
            DrawText(TextFormat("X pos: %.2f",c_jet_ptr->position.x), 20, 40, 30, RED);
            DrawText(TextFormat("Y spd: %.2f",c_jet_ptr->speed.y), 20, 70, 30, GREEN);
            DrawText(TextFormat("X spd: %.2f",c_jet_ptr->speed.x), 20, 100, 30, GREEN);
            DrawText(TextFormat("%.2f",c_jet_ptr->peso), 20, screenHeight - 20, 30, ORANGE);
            drawTotSpeed(c_jet_ptr);
            DrawText(TextFormat("enm spd: %.2f",sqrt(c_nemico_jet_ptr->speed.y * c_nemico_jet_ptr->speed.y) + (c_nemico_jet_ptr->speed.x * c_nemico_jet_ptr->speed.x)), 20, 400, 30, ORANGE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    

    CloseWindow();
    
    return 0;
}