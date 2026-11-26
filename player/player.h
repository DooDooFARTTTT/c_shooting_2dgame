#pragma once

#include "..\completeJet/completeJet.h"

typedef struct Player{
    char name[64];
    int points;
    CompleteJet CompleteJet;
}Player;

void buildPlayer(Player* player, char* name, CompleteJet CompleteJet);