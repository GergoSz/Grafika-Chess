#include "scene.h"
#include "boardstruct.h"
#include "board.h"
#include "available.h"



#define TRUE 1
#define FALSE 0

/*

Check the availability of the pieces on the board

    TODO: Check(seems pretty important), Draw, Castling, Pawn Promotion, and En Passant

*/



void showPAWNAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];
    
    if(p.isLight == FALSE){
		
        //  noone in front                                          noone where moving                              is first move
        if((scene->board.pieceLayout[px + 1][py].type == EMPTY) && (scene->board.pieceLayout[px + 2][py].type == EMPTY) && (px == 1)){
            scene->board.boardLayout[px + 2][py].color = AVAILABLE;
            insertFirst(length(), px, py, px + 2, py, p);
            i++;
        }
        //not out of board                                      noone in front
        if( (px + 1 < 8) && (scene->board.pieceLayout[px + 1][py].type == EMPTY)){
            scene->board.boardLayout[px + 1][py].color = AVAILABLE;
            //insertFirst(i, 1, 0);
            insertFirst(length(), px, py, px + 1, py, p);
            i++;
        }
        // +1 -1 exists and is enemy
        if((py > 0) && (scene->board.pieceLayout[px + 1][py - 1].type != EMPTY) && (scene->board.pieceLayout[px + 1][py - 1].isLight == TRUE)){
            scene->board.boardLayout[px + 1][py - 1].color = AVAILABLE;
            //insertFirst(i, 1, -1);
            insertFirst(length(), px, py, px + 1, py - 1, p);
            i++;
        }

        if((py < 7) && (scene->board.pieceLayout[px + 1][py + 1].type != EMPTY) && (scene->board.pieceLayout[px + 1][py + 1].isLight == TRUE)){
            scene->board.boardLayout[px + 1][py + 1].color = AVAILABLE;
            //insertFirst(i, 1, 1);
            insertFirst(length(), px, py, px + 1, py + 1, p);
            i++;
        }
    }else if(p.isLight == TRUE){
		
        //  noone in front                                          noone where moving                              is first move
        if((scene->board.pieceLayout[px - 1][py].type == EMPTY) && (scene->board.pieceLayout[px - 2][py].type == EMPTY) && (px == 6)){
            scene->board.boardLayout[px - 2][py].color = AVAILABLE;
            //insertFirst(i, -2, 0);
            insertFirst(length(), px, py, px - 2, py, p);
            i++;
        }
        //not out of board                                      noone in front
        if( (px - 1 >= 0) && (scene->board.pieceLayout[px - 1][py].type == EMPTY)){
            scene->board.boardLayout[px - 1][py].color = AVAILABLE;
            //insertFirst(i, -1, 0);
            insertFirst(length(), px, py, px - 1, py, p);
            i++;
        }
        // -1 -1 exists and is enemy
        if((py > 0) && (scene->board.pieceLayout[px - 1][py - 1].type != EMPTY) && (scene->board.pieceLayout[px - 1][py - 1].isLight == FALSE)){
            scene->board.boardLayout[px - 1][py - 1].color = AVAILABLE;
            //insertFirst(i, -1, -1);
            insertFirst(length(), px, py, px - 1, py - 1, p);
            i++;
        }

        if((py < 7) && (scene->board.pieceLayout[px - 1][py + 1].type != EMPTY) && (scene->board.pieceLayout[px - 1][py + 1].isLight == FALSE)){
            scene->board.boardLayout[px - 1][py + 1].color = AVAILABLE;
            //insertFirst(i, -1, 1);
            insertFirst(length(), px, py, px - 1, py + 1, p);
            i++;
        }
    }else{
		printf("ducked! No color written to piece");
	}
}

void showROOKAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];

    int x[4] = {1,0,-1,0};
    int y[4] = {0,1,0,-1};
    
    if(p.isLight == FALSE){
		int n = 1;
        int dir;
        //for every direction (same for rook bishop queen, only the directions change)
        for(dir = 0; dir < 4; dir++){
            //while noone infront
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                //set available and push to availability list 
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == TRUE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
       
    }else if(p.isLight == TRUE){
        int n = 1;
        int dir;
        for(dir = 0; dir < 4; dir++){
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == FALSE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
		
    }else{
		printf("ducked! No color written to piece");
	}
}

void showKNIGHTAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];

    int x[8] = {2,2,1,-1,-2,-2,-1,1};
    int y[8] = {1,-1,2,2,1,-1,2,2};
    
    if(p.isLight == FALSE){
        int dir;
        for(dir = 0; dir < 8; dir++){
            //only look for surrounding ones
            if( (scene->board.pieceLayout[px + x[dir]][py + y[dir]].type == EMPTY) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0) ){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir]][py + y[dir]].type != EMPTY) && (scene->board.pieceLayout[px + x[dir]][py + y[dir]].isLight == TRUE) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0)){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
        }
       
    }else if(p.isLight == TRUE){
        int dir;
        for(dir = 0; dir < 8; dir++){
             if( (scene->board.pieceLayout[px + x[dir]][py + y[dir]].type == EMPTY) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0) ){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir]][py + y[dir]].type != EMPTY) && (scene->board.pieceLayout[px + x[dir]][py + y[dir]].isLight == FALSE) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0)){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
        }
		
    }else{
		printf("ducked! No color written to piece");
	}
}

void showBISHOPAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];

    int x[4] = {1,-1,-1,1};
    int y[4] = {1,-1,1,-1};
    
    if(p.isLight == FALSE){
		int n = 1;
        int dir;
        for(dir = 0; dir < 4; dir++){
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == TRUE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
       
    }else if(p.isLight == TRUE){
        int n = 1;
        int dir;
        for(dir = 0; dir < 4; dir++){
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == FALSE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
		
    }else{
		printf("ducked! No color written to piece");
	}
}

void showQUEENAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];

    int x[8] = {1,-1,-1,1,1,0,-1,0};
    int y[8] = {1,-1,1,-1,0,1,0,-1};
    
    if(p.isLight == FALSE){
		int n = 1;
        int dir;
        for(dir = 0; dir < 8; dir++){
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == TRUE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
       
    }else if(p.isLight == TRUE){
        int n = 1;
        int dir;
        for(dir = 0; dir < 8; dir++){
            while( (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type == EMPTY) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0) ){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].type != EMPTY) && (scene->board.pieceLayout[px + x[dir] * n][py + y[dir] * n].isLight == FALSE) && (px + x[dir] * n >= 0) && (py + y[dir] * n < 8) && (px + x[dir] * n < 8) && (py + y[dir] * n >= 0)){
                scene->board.boardLayout[px + x[dir] * n][py + y[dir] * n].color = AVAILABLE;
                //insertFirst(i, x[dir] * n, y[dir] * n);
                insertFirst(length(), px, py, px + x[dir] * n, py + y[dir] * n, p);
                n++;
                i++;
            }
            n = 1;
        }
		
    }else{
		printf("ducked! No color written to piece");
	}
}
    
void showKINGAvailables(Scene* scene){
    int i = 1;
    int px = scene->board.selectedX;
    int py = scene->board.selectedY;
    Piece p = scene->board.pieceLayout[px][py];

    int x[8] = {1,-1,-1,1,1,0,-1,0};
    int y[8] = {1,-1,1,-1,0,1,0,-1};
    
    if(p.isLight == FALSE){
        int dir;
        for(dir = 0; dir < 8; dir++){
            //only look for surrounding ones
            if( (scene->board.pieceLayout[px + x[dir]][py + y[dir]].type == EMPTY) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0) ){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir]][py + y[dir]].type != EMPTY) && (scene->board.pieceLayout[px + x[dir]][py + y[dir]].isLight == TRUE) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0)){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
        }
       
    }else if(p.isLight == TRUE){
        int dir;
        for(dir = 0; dir < 8; dir++){
             if( (scene->board.pieceLayout[px + x[dir]][py + y[dir]].type == EMPTY) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0) ){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
            if((scene->board.pieceLayout[px + x[dir]][py + y[dir]].type != EMPTY) && (scene->board.pieceLayout[px + x[dir]][py + y[dir]].isLight == FALSE) && (px + x[dir] >= 0) && (py + y[dir] < 8) && (px + x[dir] < 8) && (py + y[dir] >= 0)){
                scene->board.boardLayout[px + x[dir]][py + y[dir]].color = AVAILABLE;
                //insertFirst(i, x[dir], y[dir]);
                insertFirst(length(), px, py, px + x[dir], py + y[dir], p);
                i++;
            }
        }
		
    }else{
		printf("ducked! No color written to piece");
	}
}
    