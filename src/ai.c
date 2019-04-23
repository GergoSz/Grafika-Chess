#include "scene.h"
#include "board.h"
#include <time.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

void makeUglyMove(Scene* scene){
    srand(time(NULL));
    setLegalMoves(scene, FALSE);

    int r = rand() % length();
    printf("%d", r);
    struct node *ptr = find(r);

    int i,j;

    printf("(%d,%d,%d,%d,%d) : ",ptr->key,ptr->fromX,ptr->fromY,ptr->toX,ptr->toY,ptr->stencilIndex);
               /* resetBoardChanges(scene, SELECTED);
                scene->board.boardLayout[ptr->fromX][ptr->fromY].color = SELECTED;
                scene->board.selectedX = i;
                scene->board.selectedY = j;
                scene->board.selectionMoved = TRUE;
                changeBoard(scene);
                break;break;*/
    Piece p = scene->board.pieceLayout[ptr->fromX][ptr->fromY];
    scene->board.pieceLayout[ptr->toY][ptr->toY] = scene->board.pieceLayout[ptr->fromX][ptr->fromY];
    p.type = EMPTY;
    scene->board.pieceLayout[ptr->fromX][ptr->fromY] = p;
}

