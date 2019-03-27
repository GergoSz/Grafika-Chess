#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "res/cube.obj");
	load_model(&(scene->bishop), "res/bishop.obj");
	load_model(&(scene->p), "res/pawn.obj");
	load_model(&(scene->king), "res/king.obj");
	load_model(&(scene->rook), "res/rook.obj");
	load_model(&(scene->knight), "res/knight.obj");
	
    scene->texture_id = load_texture("res/cube.png"); 

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 0.2;
}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 20.0f, 10.0f, 5.0f, 1.0f };

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

void draw_scene(const Scene* scene){

    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    glPushMatrix();
        //glTranslatef(0.0, 3.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
	draw_model(&(scene->p));
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 5.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->king));
    glPopMatrix();
    glPushMatrix();
        //glTranslatef(0.0, 0.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->bishop));
    glPopMatrix();
    glPushMatrix();
        glTranslatef(13.0, 20.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->king));
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 30.0, 0.0);
	    glRotatef(90,1,0,0);
        glScalef(0.6, 0.6, 0.6);
        draw_model(&(scene->rook));
    glPopMatrix();
	
    //glTranslatef(10.0, 30.0, 0.0);
	glRotatef(90,1,0,0);
    glScalef(30.0, 0.003, 30.0);
    draw_model(&(scene->cube));

}

/*void transform(){
    glPushMatrix();



    glPopMatrix();
}*/

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

