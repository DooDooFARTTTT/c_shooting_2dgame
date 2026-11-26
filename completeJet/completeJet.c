#include "completeJet.h"
#include "jetParts/jetParts.h"
#include "stdlib.h"

const int screenWidth = 900;
const int screenHeight = 562;

typedef struct CompleteJet{
    Jet jet;
    Triangolo triangolo;
    Proiettile proiettiliInCampo[100];
    
    Vector2 speed;
    Vector2 position;

    float weight;
    float accPerFrame;
    float stallSpeed;
    float directionDegree;
    
    int numAliveProjectile;
    int resistenzaTot;
    int resistenzaAttuale;
}CompleteJet;

void builCompleteJet(CompleteJet *c_jet, Jet* jet, Triangolo* triangolo, int offsetX, int offsetY){
    //COMPONENTI DI COMPLETED JET
    c_jet->jet = *jet;
    c_jet->triangolo = *triangolo;

    //DATI DI COMPLETED JET
    c_jet->speed.x = 0;
    c_jet->speed.y = 0;
    c_jet->position.x = screenWidth / 2 - offsetX;
    c_jet->position.y = screenHeight / 2 - offsetY;
    c_jet->weight = jet->engine.peso + jet->airframe.peso + jet->gun.peso + jet->wings.peso;;
    c_jet->accPerFrame =  8.0f * (jet->engine.potenza / c_jet->weight);
    c_jet->stallSpeed = c_jet->weight / 15;
    c_jet->directionDegree = START_DIRECTION;
    c_jet->numAliveProjectile = 0;
    c_jet->resistenzaTot = jet->engine.resistenza + jet->airframe.resistenza + jet->wings.resistenza;
    c_jet->resistenzaAttuale = c_jet->resistenzaTot;
}

void sparaProiettile(CompleteJet *c_jet){
    if(c_jet->proiettiliInCampo > MAX_ALIVE_BULLETS){
        DrawText("max ammo", 20, 500, 30, BLUE);
    }
}

void virare(CompleteJet *c_jet, Triangolo* triangolo, int verso){
    float x_speed = c_jet->speed.x;
    float y_speed = c_jet->speed.y;
    float tot_speed = sqrt((x_speed * x_speed) + (y_speed * y_speed));

    if(tot_speed <= c_jet->stallSpeed)
        return;


    float ratio = (c_jet->jet.wings.perfect_turn_speed * 100) / tot_speed;
    ratio = fabs((ratio - 100) / 100) + 1;



    float degreeRotated = (c_jet->jet.wings.turn_capability / ratio) / 15;

    if(verso == 1)
        c_jet->directionDegree += degreeRotated;
    else
        c_jet->directionDegree -= degreeRotated;
    ricalcolo_gognometrico_velocita(c_jet, tot_speed);
    c_jet->speed.x *= 1 - degreeRotated / (FPS * 1);
    c_jet->speed.y *= 1 - degreeRotated / (FPS * 1);
    rotate_triangolo(triangolo, c_jet->position, c_jet->directionDegree);

    DrawText(TextFormat("Turn capacity: %.4f", degreeRotated), 20, 220, 30, PURPLE);
}

void ricarica(CompleteJet *c_jet){
    if(c_jet->jet.gun.ricarica_rimasta > 0)
        c_jet->jet.gun.ricarica_rimasta -= 1000 / FPS;
    
    DrawText(TextFormat("ricarica: %.2f",c_jet->jet.gun.ricarica_rimasta), 20, 360, 30, GREEN);
}

//dati i due vettori per riferimento, e la direzione del jet, determina l'accellerazione per i due vettori
//e li moltiplica per il cos "x" e il sin "y" basato sulla conversione in radianti della direzione degree.
//il tutto diviso per il numero di FPS
void accellera(CompleteJet *c_jet){
    float tot_speed = sqrt((c_jet->speed.x * c_jet->speed.x) + (c_jet->speed.y * c_jet->speed.y));

    float accellerazione = calculate_accelleration(c_jet->accPerFrame, c_jet->jet.airframe.aereodinamicita, tot_speed, 0);

    c_jet->speed.x -= accellerazione * cos((conversioneInRadianti(c_jet->directionDegree))) / FPS;
    c_jet->speed.y -= accellerazione * sin((conversioneInRadianti(c_jet->directionDegree))) / FPS;
}

void rallenta(CompleteJet *c_jet){
    c_jet->speed.x -= calcolaResistenza(c_jet->speed.x, c_jet->jet.airframe.aereodinamicita) / (c_jet->jet.airframe.aereofreno / 2);
    c_jet->speed.y -= calcolaResistenza(c_jet->speed.y, c_jet->jet.airframe.aereodinamicita) / (c_jet->jet.airframe.aereofreno / 2);
}

//dato UN VETTORE, l'accellerazione per frame, l'aereodinamica e la velocita, calcolo quanto è l'accellerazione per ogni frame
float calculate_accelleration(float accPerFrame, float aereodinamicita, float speed, char stampa){
    float resistenza = calcolaResistenza(speed, aereodinamicita);
    if(stampa == 0)
        DrawText(TextFormat("X: %.4f",resistenza), 20, 130, 30, WHITE);
    else
        DrawText(TextFormat("Y: %.4f",resistenza), 20, 160, 30, WHITE);

    if(resistenza > 0)
        return accPerFrame - resistenza;
    return accPerFrame + resistenza;
}

void drawTotSpeed(CompleteJet *c_jet){
    float tot_speed = sqrt((c_jet->speed.x * c_jet->speed.x) + (c_jet->speed.y * c_jet->speed.y));

    if(tot_speed <= c_jet->stallSpeed)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, MAROON);
    else if(tot_speed <= c_jet->jet.wings.perfect_turn_speed * 0.55)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, RED);
    else if(tot_speed <= c_jet->jet.wings.perfect_turn_speed * 0.80)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, ORANGE);
    else if(tot_speed > c_jet->jet.wings.perfect_turn_speed * 0.80 && tot_speed < c_jet->jet.wings.perfect_turn_speed * 0.95 )
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, YELLOW);
    else if(tot_speed >= c_jet->jet.wings.perfect_turn_speed * 0.95 && tot_speed <= c_jet->jet.wings.perfect_turn_speed * 1.05)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, GREEN);
    else if(tot_speed > c_jet->jet.wings.perfect_turn_speed * 1.05)
        DrawText(TextFormat("spd: %.1f",tot_speed), 20, 190, 30, BLUE);
}