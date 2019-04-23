#ifndef NUMSELECTION_h
#define NUMSELECTION_H


#define TRUE 1
#define FALSE 0

#include "scene.h"

#include <GL/glut.h>

void toggleSelected(Scene* scene);

void moveSelection(Scene* scene, int x, int y);

void moveSelectedPiece(Scene* scene, int x, int y);

#  endif
