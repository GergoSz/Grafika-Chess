#ifndef BOARD_H
#define BOARD_H

#define TRUE 1
#define FALSE 0


typedef enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
} PieceType;

typedef enum {
    LIGHT,
    DARK,
    SELECTED,
    AVAILABLE
} QubeColor;

typedef struct Piece
{
    
    int x,y;
    PieceType type;
    int isLight;

}Piece;

typedef struct Qube
{
    
    int x,y;
    QubeColor color;

}Qube;


typedef struct Board{

    Qube boardLayout[8][8];
    Piece lightPieces[16];
    Piece darkPieces[16];

}Board;

#endif