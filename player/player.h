#pragma once

#include "..\completeJet/completeJet.h"

typedef struct Player{
    char name[64];
    int points;
    CompleteJet completeJet;
}Player;

Player* buildPlayer(char* name);
