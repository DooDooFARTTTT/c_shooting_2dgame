#include "completeJet.h"
const int screenWidth = 900;
const int screenHeight = 562;


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