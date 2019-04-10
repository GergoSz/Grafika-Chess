#include "scene.h"
#include "board.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->skybox), "res/skybox.obj");
    load_model(&(scene->cube), "res/cube.obj");
	load_model(&(scene->pawn), "res/pawn.obj");
	load_model(&(scene->knight), "res/knight.obj");
	load_model(&(scene->bishop), "res/bishop.obj");
	load_model(&(scene->rook), "res/rook.obj");
    load_model(&(scene->queen), "res/queen.obj");
    load_model(&(scene->king), "res/king.obj");
	
    scene->light_texture = load_texture("res/lighttexture.png");
    scene->dark_texture = load_texture("res/else.png");
    scene->skybox_texture = load_texture("res/skybox.png");
    scene->base_texture= load_texture("res/base.png");


    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 1.0;
}

void set_lighting()
{
    float ambient_light[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float diffuse_light[] = { 1.5f, 1.5f, 1.5f, 1.0f };
    float specular_light[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    float position[] = { 10.0f, 10.0f, 20.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(Scene* scene){

    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    draw_skybox(scene);
    init_Board(scene);
    
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

static void myShadowMatrix(float ground[4], float light[4])
{
    float  dot;
    float  shadowMat[4][4];

    dot = ground[0] * light[0] +
          ground[1] * light[1] +
          ground[2] * light[2] +
          ground[3] * light[3];
    
    shadowMat[0][0] = dot - light[0] * ground[0];
    shadowMat[1][0] = 0.0 - light[0] * ground[1];
    shadowMat[2][0] = 0.0 - light[0] * ground[2];
    shadowMat[3][0] = 0.0 - light[0] * ground[3];
    
    shadowMat[0][1] = 0.0 - light[1] * ground[0];
    shadowMat[1][1] = dot - light[1] * ground[1];
    shadowMat[2][1] = 0.0 - light[1] * ground[2];
    shadowMat[3][1] = 0.0 - light[1] * ground[3];
    
    shadowMat[0][2] = 0.0 - light[2] * ground[0];
    shadowMat[1][2] = 0.0 - light[2] * ground[1];
    shadowMat[2][2] = dot - light[2] * ground[2];
    shadowMat[3][2] = 0.0 - light[2] * ground[3];
    
    shadowMat[0][3] = 0.0 - light[3] * ground[0];
    shadowMat[1][3] = 0.0 - light[3] * ground[1];
    shadowMat[2][3] = 0.0 - light[3] * ground[2];
    shadowMat[3][3] = dot - light[3] * ground[3];

    glMultMatrixf((const GLfloat*)shadowMat);
}

void init_Board(Scene* scene){
    
    static PieceType startingPieces[8][8] = {   { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK}, 
                                        { PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
                                        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                                        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                                        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                                        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                                        { PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
                                        { ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK} };

    memmove(scene->board.pieceLayout,startingPieces,sizeof(scene->board.pieceLayout));

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
            Qube q;
            glPushMatrix();
            glTranslatef((double)j, 0.0, 0.0);
            glTranslatef(0.0, (double)i, 0.0);
            if((i%2 == 0 && j%2 != 0) ||(j%2 == 0 && i%2 != 0)){ 
                q.color = DARK;
                q.x = i;
                q.y = j;
                scene->board.boardLayout[i][j] = q;
                
                    glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                        
                
            }else{
                q.color = LIGHT;
                q.x = i;
                q.y = j;
                scene->board.boardLayout[i][j] = q;
                glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                      
                    
	                
            }
            draw_model(&(scene->cube));

            glScalef(0.5,0.5,0.5);
            glRotatef(90,1,0,0);
            glTranslatef(0.0, 1.0, 0.0);


            if(scene->board.pieceLayout[q.x][q.y] != NONE){
                if(q.x < 4){
                    glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                    glRotatef(90,0,-1,0);
                }else{
                    glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                    glRotatef(90,0,1,0);
                }
                switch(scene->board.pieceLayout[q.x][q.y]){
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
    //pieces
   /* for(i = 0; i < 16; i++){
        glPushMatrix();
            if(i < 8){
                glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                glTranslatef((double)i, 1.0, 0.5);
            }else
            {
                glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                glTranslatef((double)i-8, 6.0, 0.5);
            }
            glScalef(0.5,0.5,0.5);
            glRotatef(90,1,0,0);
            draw_model(&(scene->pawn));
        glPopMatrix();
    }
    for(i = 0; i < 3; i++){
        for(j = 0; j < 4; j++){
            glPushMatrix();
            if(i < 2){
                glBindTexture(GL_TEXTURE_2D, scene->light_texture);
                glTranslatef(((double)j * 7) + i, 0.0, 0.5);
            }else
            {
                glBindTexture(GL_TEXTURE_2D, scene->dark_texture);
                glTranslatef((((double)j-2) * 7) - i, 7.0, 0.5);
            }
            glScalef(0.5,0.5,0.5);
            glRotatef(90,1,0,0);
            switch (i)
            {
            case 0:
                draw_model(&(scene->rook));
                break;
            case 2:
                draw_model(&(scene->knight));
                break;
            case 3:
                draw_model(&(scene->bishop));
                break;
            
            default:
                break;
            }
        glPopMatrix();
        }
    }*/

}

void draw_skybox(Scene* scene){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);
        //glTranslatef(1.0, 0.0, 0.0);
        //glTranslatef(0.0, 1.0, 0.0);
        glScalef(1.2, 1.2, 1.2);
	    draw_model(&(scene->skybox));
    glPopMatrix();
}