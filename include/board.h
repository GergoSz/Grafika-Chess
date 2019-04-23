#ifndef BOARD_H
#define BOARD_H

#define TRUE 1
#define FALSE 0

#include "scene.h"

#include <GL/glut.h>


void init_Board(Scene* scene);

void render_Board(Scene* scene, GLenum mode);

void changeBoard(Scene* scene);

void pieceClicked(Scene* scene, GLuint stencilIndex);

void showAvailableMoves(Scene* scene, Piece piece);

void resetBoardChanges(Scene* scene, QubeColor colour);

void setAllLegalMoves(Scene* scene);

#endif