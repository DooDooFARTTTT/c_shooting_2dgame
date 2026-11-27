#include "player.h"
#include <stdlib.h>
#include <string.h>

Player* buildPlayer(char* name){
    Player *newPlayer = (Player*)malloc(sizeof(Player));

    if(newPlayer == NULL){
        return NULL;
    }

    strcpy(newPlayer->name, name);
    return newPlayer;
}

