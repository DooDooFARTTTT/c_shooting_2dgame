#include "player.h"
#include "completeJet/completeJet.h"
#include <stdlib.h>
#include <string.h>

void buildPlayer(Player* player, char* name){
    player = malloc(sizeof(player));

    if(player == NULL){
        return;
    }

    strcpy(player->name, name);
}

