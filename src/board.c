#include "scene.h"
#include "board.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>


#define TRUE 1
#define FALSE 0

void init_Board(Scene* scene){

    int i;
    int j;

    scene->board.selectedX = 4;
    scene->board.selectedY = 4;
    scene->board.selectionMoved = TRUE;
    scene->board.moving = FALSE;

    insertFirst(0, 0, 0);

    //toggleSelected(&scene);

    static PieceType startingPositions[8][8] = {   { ROOK,     KNIGHT, BISHOP, QUEEN,  KING,   BISHOP, KNIGHT, ROOK}, 

                                                { PAWN,     PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN},

                                                { EMPTY,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  PAWN,  EMPTY},
                                                
                                                { EMPTY,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY},
                                                
                                                { EMPTY,    EMPTY,  EMPTY,  EMPTY,  PAWN,   EMPTY,  EMPTY,  EMPTY},
                                                
                                                { EMPTY,    EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY},
                                                
                                                { PAWN,     PAWN,   PAWN,   PAWN,   EMPTY,  PAWN,   EMPTY,   PAWN},
                                                
                                                { ROOK,     KNIGHT, BISHOP, QUEEN,  KING,   BISHOP, KNIGHT, ROOK}};

    static Piece startingPieces[8][8];

    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            Piece p;
            p.x = i;
            p.y = j;
            p.firstMove = TRUE;
            p.type = startingPositions[i][j];
            if(i > 1){
                p.isLight = TRUE;
            }else{
                p.isLight = FALSE;
            }
            startingPieces[i][j] = p;
        }
    }

    memmove(scene->board.pieceLayout,startingPieces,sizeof(scene->board.pieceLayout));

    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            Qube q;
            if((i%2 == 0 && j%2 != 0) || (j%2 == 0 && i%2 != 0)){ 
                q.color = DARK;
                q.defaultColor = DARK;
                q.x = i;
                q.y = j;
                scene->board.boardLayout[i][j] = q;
            }else{
                q.color = LIGHT;
                q.defaultColor = LIGHT;
                q.x = i;
                q.y = j;
                scene->board.boardLayout[i][j] = q;
            }
        }
    }

    scene->board.boardLayout[scene->board.selectedX][scene->board.selectedX].color = SELECTED;

}

void render_Board(Scene* scene){

    //boardchange
    if(scene->board.selectionMoved){
        changeBoard(scene);
    }

    //baseofboard
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->base_texture);
        glTranslatef(3.5,3.5,-0.5);
        glScalef(12.0, 12.0, 1.0);
        draw_model(&(scene->cube));
    glPopMatrix();

    int i;
    int j;
    
    //board
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){

            glPushMatrix();
            glTranslatef((double)j, 0.0, 0.0);
            glTranslatef(0.0, (double)i, 0.0);

            //Draw board cubes
            switch(scene->board.boardLayout[i][j].color){
                case DARK:
                    glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                    break;
                case LIGHT:
                    glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                    break;
                case SELECTED:
                    glBindTexture(GL_TEXTURE_2D, scene->selected_texture);
                    break;
                case AVAILABLE:
                    glBindTexture(GL_TEXTURE_2D, scene->available_texture);
                    break;
                case MOVING:
                    glBindTexture(GL_TEXTURE_2D, scene->moving_texture);
                    break;
            }

            draw_model(&(scene->cube));

            glScalef(0.5,0.5,0.5);
            glRotatef(90,1,0,0);


            //Do stuff when selected
            if(scene->board.selectedX == i && scene->board.selectedY == j){
                glTranslatef(0.0, 1.5, 0.0);
            }else{
                glTranslatef(0.0, 1.0, 0.0);
            }

            //Draw pieces to board
            if(scene->board.pieceLayout[i][j].type != NONE){
                if(scene->board.pieceLayout[i][j].isLight == FALSE){
                    glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                    glRotatef(90,0,-1,0);
                }else{
                    glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                    glRotatef(90,0,1,0);
                }
                switch(scene->board.pieceLayout[i][j].type){
                    case PAWN:
                        draw_model(&(scene->pawn));
                        break;
                    case ROOK:
                        draw_model(&(scene->rook));
                        break;
                    case KNIGHT:
                        draw_model(&(scene->knight));
                        break;
                    case BISHOP:
                        draw_model(&(scene->bishop));
                        break;
                    case QUEEN:
                        draw_model(&(scene->queen));
                        break;
                    case KING:
                        draw_model(&(scene->king));
                        break;
            
                    default:
                        break;
                }
            }

            glPopMatrix();

        }
    }
}

void changeBoard(Scene* scene){
    //Piece p = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
    resetAvailables(scene);
    Piece p = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
    showAvailableMoves(scene, p);
    scene->board.selectionMoved = FALSE;
}

void toggleSelected(Scene* scene){
    if(scene->board.moving == FALSE && scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type != EMPTY){
        scene->board.moving = TRUE;
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = MOVING;
    }else{
        resetAvailables(scene);
        scene->board.moving = FALSE;
        scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = SELECTED;
        scene->board.movingBaseX = 0;
        scene->board.movingBaseY = 0;
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
        
        if(isInList((scene->board.movingBaseX + x), (scene->board.movingBaseY + y)) == TRUE ){
            printf("Move\n");
            moveSelectedPiece(scene, x, y);
        }

    }else{
        printf("%d, %d", scene->board.selectedX, scene->board.selectedY);
        if((scene->board.selectedX + x < 8) && (scene->board.selectedX + x >= 0) && (scene->board.selectedY + y < 8) && (scene->board.selectedY + y >= 0)){
            scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].color = scene->board.boardLayout[scene->board.selectedX][scene->board.selectedY].defaultColor;
            scene->board.boardLayout[scene->board.selectedX + x][scene->board.selectedY + y].color = SELECTED;
            scene->board.selectedX += x;
            scene->board.selectedY += y;
            scene->board.selectionMoved = TRUE;
            
            //resetList();
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

    //scene->board.pieceLayout[scene->board.selectedX + x][scene->board.selectedY + y].type = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type;
    //scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY].type = EMPTY;



    //scene->board.boardLayout[scene->board.selectedY + x][scene->board.selectedY + y].color = AVAILABLE;
    scene->board.boardLayout[scene->board.selectedX + scene->board.movingBaseX][scene->board.selectedY + scene->board.movingBaseY].color = MOVING;

}

void showAvailableMoves(Scene* scene, Piece piece){
        switch(piece.type){
            case PAWN:
                resetList();
                showPAWNAvailables(scene);
                printList();
                break;
            case ROOK:
                //draw_model(&(scene->rook));
                break;
            case KNIGHT:
                //draw_model(&(scene->knight));
                break;
            case BISHOP:
                //draw_model(&(scene->bishop));
                break;
            case QUEEN:
                //draw_model(&(scene->queen));
                break;
            case KING:
                //draw_model(&(scene->king));
                break;
            
        }
}

void resetAvailables(Scene* scene){

    int i = 0;
    int j = 0;

    printf("reset");

    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            if((scene->board.boardLayout[i][j].color == AVAILABLE) || (scene->board.boardLayout[i][j].color == MOVING)){
                scene->board.boardLayout[i][j].color = scene->board.boardLayout[i][j].defaultColor;
            }
        }
    }

}
/*void getPAWNMoves(Scene* scene, Piece piece){
    printf("get");
    scene->board.boardLayout[piece.x][piece.y].color = AVAILABLE;

}*/