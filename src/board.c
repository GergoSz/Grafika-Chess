#include "scene.h"
#include "board.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>


#define TRUE 1
#define FALSE 0

void init_Board(Scene* scene){
	printf("INIT BOARD!");
    int i;
    int j;

    scene->board.selectedX = 4;
    scene->board.selectedY = 5;
    scene->board.moving = FALSE;

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
    GLuint sel = 1;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            Piece p;
            p.x = i;
            p.y = j;
            p.firstMove = TRUE;
            p.type = startingPositions[i][j];
            if(p.type != EMPTY){
                p.stencilIndex = sel;
                sel++;
            }else{
                p.stencilIndex = 0;
            }
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
                q.stencilIndex = sel;    
                sel++;
                scene->board.boardLayout[i][j] = q;
            }else{
                q.color = LIGHT;
                q.defaultColor = LIGHT;
                q.x = i;
                q.y = j;                
                q.stencilIndex = sel;
                sel++;
                scene->board.boardLayout[i][j] = q;
            }
        }
    }

}

void render_Board(Scene* scene, GLenum mode){

    //boardchange
    if(scene->board.selectionMoved){
        changeBoard(scene);
    }

    //baseofboard
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, scene->base_texture);
        glTranslatef(3.5,3.5,-0.5);
        glScalef(12.0, 12.0, 1.0);
        glStencilFunc(GL_ALWAYS, 0, -1);
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
                    glStencilFunc(GL_ALWAYS, scene->board.boardLayout[i][j].stencilIndex, -1);
                    glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                    break;
                case LIGHT:
                    glStencilFunc(GL_ALWAYS, scene->board.boardLayout[i][j].stencilIndex, -1);
                    glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                    break;
                case SELECTED:
                    glStencilFunc(GL_ALWAYS, scene->board.boardLayout[i][j].stencilIndex, -1);
                    glBindTexture(GL_TEXTURE_2D, scene->selected_texture);
                    break;
                case AVAILABLE:
                    glStencilFunc(GL_ALWAYS, scene->board.boardLayout[i][j].stencilIndex, -1);
                    glBindTexture(GL_TEXTURE_2D, scene->available_texture);
                    break;
                case MOVING:
                    glStencilFunc(GL_ALWAYS, scene->board.boardLayout[i][j].stencilIndex, -1);
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
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
                        draw_model(&(scene->pawn));
                        break;
                    case ROOK:
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
                        draw_model(&(scene->rook));
                        break;
                    case KNIGHT:
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
                        draw_model(&(scene->knight));
                        break;
                    case BISHOP:
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
                        draw_model(&(scene->bishop));
                        break;
                    case QUEEN:
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
                        draw_model(&(scene->queen));
                        break;
                    case KING:
                        glStencilFunc(GL_ALWAYS, scene->board.pieceLayout[i][j].stencilIndex, -1);
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
    resetBoardChanges(scene, AVAILABLE);
    resetBoardChanges(scene, MOVING);
    Piece p = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
    showAvailableMoves(scene, p);
    scene->board.selectionMoved = FALSE;
}

void pieceClicked(Scene* scene, GLuint stencilIndex){
    int i;
    int j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            if( (scene->board.pieceLayout[i][j].stencilIndex == stencilIndex) && scene->board.pieceLayout[i][j].isLight){
                printf("%d, %d, %u\n", i, j, scene->board.pieceLayout[i][j].stencilIndex);
                resetBoardChanges(scene, SELECTED);
                scene->board.boardLayout[i][j].color = SELECTED;
                scene->board.selectedX = i;
                scene->board.selectedY = j;
                scene->board.selectionMoved = TRUE;
                changeBoard(scene);
                break;break;
            }
        }
    }


}

void qubeClicked(Scene* scene, GLuint stencilIndex){

    int i;
    int j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            if(scene->board.boardLayout[i][j].stencilIndex == stencilIndex && scene->board.boardLayout[i][j].color == AVAILABLE){
                printf("%d, %d, %u\n", i, j, scene->board.boardLayout[i][j].stencilIndex);
                Piece p = scene->board.pieceLayout[i][j];
                scene->board.pieceLayout[i][j] = scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY];
                p.type = EMPTY;
                scene->board.pieceLayout[scene->board.selectedX][scene->board.selectedY] = p;
                scene->board.selectedX = i;
                scene->board.selectedY = j;
                scene->board.selectionMoved = TRUE;
                changeBoard(scene);
                break;break;
            }
        }
    }

}

void showAvailableMoves(Scene* scene, Piece piece){
        switch(piece.type){
            case PAWN:
                showPAWNAvailables(scene);
                break;
            case ROOK:
                showROOKAvailables(scene);
                break;
            case KNIGHT:
                showKNIGHTAvailables(scene);
                break;
            case BISHOP:
                showBISHOPAvailables(scene);
                break;
            case QUEEN:
                showQUEENAvailables(scene);
                break;
            case KING:
                showKINGAvailables(scene);
                break;
        }
}

void resetBoardChanges(Scene* scene, QubeColor colour){

    int i = 0;
    int j = 0;

    printf("reset");

    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            if(scene->board.boardLayout[i][j].color == colour){
                scene->board.boardLayout[i][j].color = scene->board.boardLayout[i][j].defaultColor;
            }
        }
    }

}

//writes all legal move to the list
void setAllLegalMoves(Scene* scene){
    resetList();
    int i, j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            resetBoardChanges(scene, AVAILABLE);
            resetBoardChanges(scene, SELECTED);
            scene->board.selectedX = i;
            scene->board.selectedY = j;
            showAvailableMoves(scene, scene->board.pieceLayout[i][j]);
        }
    }
    printList();
}

void setLegalMoves(Scene* scene, int isLight){
    resetList();
    int i, j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            if(scene->board.pieceLayout[i][j].isLight == isLight){
                resetBoardChanges(scene, AVAILABLE);
                resetBoardChanges(scene, SELECTED);
                scene->board.selectedX = i;
                scene->board.selectedY = j;
                showAvailableMoves(scene, scene->board.pieceLayout[i][j]);
            }
        }
    }
    printList();
}