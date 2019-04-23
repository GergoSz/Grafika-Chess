#include "scene.h"
#include "board.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>


#define TRUE 1
#define FALSE 0

void toggleSelected(Scene* scene){
    if(scene->board.moving == FALSE && scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type != EMPTY){
        scene->board.moving = TRUE;
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = MOVING;
    }else{
        //resetBoardChanges(scene, colour);
        scene->board.moving = FALSE;
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = SELECTED;
		
		//printf("%d, %d : %d, %d", (scene->board.selectedX), (scene->board.selectedX + scene->board.movingBaseX), (scene->board.selectedY), (scene->board.selectedY + scene->board.movingBaseY) );
		if( !((scene->board.selectedX == (scene->board.selectedX + scene->board.movingBaseX) ) && (scene->board.selectedY == (scene->board.selectedY + scene->board.movingBaseY))) ){
			Piece p = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
			p.isLight = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].isLight;
			printf("%d", p.isLight);
			scene->board.pieceLayout[scene->board.selectedX + scene->board.movingBaseX][scene->board.selectedY + scene->board.movingBaseY] = p;
			scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type = EMPTY;
			scene->board.selectedX += scene->board.movingBaseX;
			scene->board.selectedY += scene->board.movingBaseY;
            resetBoardChanges(scene, SELECTED);
            scene->board.selectionMoved = TRUE;
		}
        scene->board.movingBaseX = 0;
        scene->board.movingBaseY = 0;
		changeBoard(scene);
    }

    //printf("asd");
    /*if(scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color != SELECTED){
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedX].color = SELECTED;
        return;
    }else{
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedX].color = scene->board.boardLayout[scene->board.selectedX][scene->board.selectedX].defaultColor;
    }*/
}

void moveSelection(Scene* scene, int x, int y){
    //TODO: DEFAULTCOLOR fixed  (I dont remember what this means but i think i fixed it)
    if(scene->board.moving == TRUE){
        
        printf("Only move if move is in list!\n");
        
        if(isInList((scene->board.movingBaseX + x), (scene->board.movingBaseY + y)) == TRUE){
            if(scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type != KNIGHT){
                printf("Move\n");
                moveSelectedPiece(scene, x, y);
            }else{
                //moveKnightPiece(scene, x, y);
            }
            
        }

    }else{
        printf("%d, %d", scene->board.selectedX, scene->board.selectedY);
        if((scene->board.selectedX + x < 8) && (scene->board.selectedX + x >= 0) && (scene->board.selectedY + y < 8) && (scene->board.selectedY + y >= 0)){
            scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].defaultColor;
            scene->board.boardLayout[scene->board.selectedX + x][scene->board.selectedY + y].color = SELECTED;
            scene->board.selectedX += x;
            scene->board.selectedY += y;
            scene->board.selectionMoved = TRUE;
            
            resetList();
        }
    }

    /*if(scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type != EMPTY){
        showAvailableMoves(&scene, scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY]);
    }*/
}

void moveSelectedPiece(Scene* scene, int x, int y){
    
	scene->board.boardLayout[scene->board.selectedX + scene->board.movingBaseX][scene->board.selectedY + scene->board.movingBaseY].color = AVAILABLE;

    scene->board.movingBaseX += x;
    scene->board.movingBaseY += y;
    //scene->board.boardLayout[scene->board.selectedY + x][scene->board.selectedY + y].color = AVAILABLE;
    scene->board.boardLayout[scene->board.selectedX + scene->board.movingBaseX][scene->board.selectedY + scene->board.movingBaseY].color = MOVING;

}