#include "scene.h"
#include "boardstruct.h"
#include "board.h"
#include "available.h"

#define TRUE 1
#define FALSE 0

void showPAWNAvailables(Scene* scene){
    int i = 1;
    Piece p = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
    
    if(p.isLight == FALSE){
        //  noone in front                                          noone where moving                              is first move
        if((scene->board.pieceLayout[p.x + 1][p.y].type == EMPTY) && (scene->board.pieceLayout[p.x + 2][p.y].type == EMPTY) && (p.x == 1)){
            scene->board.boardLayout[p.x + 2][p.y].color = AVAILABLE;
            insertFirst(i, 2, 0);
            i++;
        }
        //not out of board                                      noone in front
        if( (p.x + 1 < 8) && (scene->board.pieceLayout[p.x + 1][p.y].type == EMPTY)){
            scene->board.boardLayout[p.x + 1][p.y].color = AVAILABLE;
            insertFirst(i, 1, 0);
            i++;
        }
        // +1 -1 exists and is enemy
        if((p.y > 0) && (scene->board.pieceLayout[p.x + 1][p.y - 1].type != EMPTY) && (scene->board.pieceLayout[p.x + 1][p.y - 1].isLight == TRUE)){
            scene->board.boardLayout[p.x + 1][p.y - 1].color = AVAILABLE;
            insertFirst(i, 1, -1);
            i++;
        }

        if((p.y < 7) && (scene->board.pieceLayout[p.x + 1][p.y + 1].type != EMPTY) && (scene->board.pieceLayout[p.x + 1][p.y + 1].isLight == TRUE)){
            scene->board.boardLayout[p.x + 1][p.y + 1].color = AVAILABLE;
            insertFirst(i, 1, 1);
            i++;
        }
    }else{
        //  noone in front                                          noone where moving                              is first move
        if((scene->board.pieceLayout[p.x - 1][p.y].type == EMPTY) && (scene->board.pieceLayout[p.x - 2][p.y].type == EMPTY) && (p.x == 6)){
            scene->board.boardLayout[p.x - 2][p.y].color = AVAILABLE;
            insertFirst(i, -2, 0);
            i++;
        }
        //not out of board                                      noone in front
        if( (p.x - 1 >= 0) && (scene->board.pieceLayout[p.x - 1][p.y].type == EMPTY)){
            scene->board.boardLayout[p.x - 1][p.y].color = AVAILABLE;
            insertFirst(i, -1, 0);
            i++;
        }
        // -1 -1 exists and is enemy
        if((p.y > 0) && (scene->board.pieceLayout[p.x - 1][p.y - 1].type != EMPTY) && (scene->board.pieceLayout[p.x - 1][p.y - 1].isLight == FALSE)){
            scene->board.boardLayout[p.x - 1][p.y - 1].color = AVAILABLE;
            insertFirst(i, -1, -1);
            i++;
        }

        if((p.y < 7) && (scene->board.pieceLayout[p.x - 1][p.y + 1].type != EMPTY) && (scene->board.pieceLayout[p.x - 1][p.y + 1].isLight == FALSE)){
            scene->board.boardLayout[p.x - 1][p.y + 1].color = AVAILABLE;
            insertFirst(7, -1, 1);
            i++;
        }
    }
}

void showROOKAvailables(Scene* scene){

}

void showKNIGHTAvailables(Scene* scene){

}

void showBISHOPAvailables(Scene* scene){

}

void showQUEENAvailables(Scene* scene){

}
    
void showKINGAvailables(Scene* scene){

}
    