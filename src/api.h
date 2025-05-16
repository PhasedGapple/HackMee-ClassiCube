#ifndef API_H
#define API_H

#include "Core.h"
#include "String.h"
#include "Entity.h"
#include "Event.h"
#include "Input.h"
#include "Game.h"
#include "World.h"
#include "Server.h"

void API_SortFill(Vec3 startPos, Vec3 endPos, BlockID block1);
void API_Fill();
void API_SortFillBot(Vec3 startPos, Vec3 endPos, BlockID block1);
void API_FillBot();
void API_PauseScreen1_Show();

#endif
