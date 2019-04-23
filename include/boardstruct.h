#ifndef BOARDSTRUCT_H
#define BOARDSTRUCT_H

#define TRUE 1
#define FALSE 0

#include "scene.h"


typedef enum {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} PieceType;

typedef enum {
    MOVING,
    LIGHT,
    DARK,
    SELECTED,
    AVAILABLE
} QubeColor;

typedef struct Piece{

    int x,y;
    PieceType type;
    int isLight;
    int firstMove;
    GLuint stencilIndex;

}Piece;

typedef struct Qube{

    int x,y;
    QubeColor defaultColor;
    QubeColor color;
    GLuint stencilIndex;

}Qube;


typedef struct Board{

    Qube boardLayout[8][8];
    Piece pieceLayout[8][8];
    int selectionMoved;
    int selectedX;
    int selectedY;
    int moving;
    int movingBaseX;
    int movingBaseY;
    /*Piece lightPieces[16];
    Piece darkPieces[16];*/
    

}Board;


#endif