#ifndef BOARD_H
#define BOARD_H

#define TRUE 1
#define FALSE 0

#include "scene.h"


void init_Board(Scene* scene);

void render_Board(Scene* scene);

void changeBoard(Scene* scene);

void toggleSelected(Scene* scene);

void moveSelection(Scene* scene, int x, int y);

void showAvailableMoves(Scene* scene, Piece piece);

void resetAvailables(Scene* scene);

//void getPAWNMoves(Scene* scene, Piece piece);

#endif