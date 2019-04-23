#include "camera.h"

#include <GL/glut.h>

#include <math.h>

#include "utils.h"
#include "model.h"
#include "scene.h"
#include "camera.h"


#define CAMERA_SPEED 5

void init_camera(Camera* camera)
{
    camera->position.x = 3.254400; //x: 1.564245,y: 1.807708,z: 1.117000
    camera->position.y = -3.347974;//x: 3.254400,y: -3.347974,z: 6.289003
    camera->position.z = 6.289003; 
    camera->rotation.x = 317.000000; //x: 336.000000,y: 0.000000,z: 229.000000
    camera->rotation.y = 0.0;
    camera->rotation.z = 89.000000;//x: 317.000000,y: 0.000000,z: 89.000000
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
    //camera->help_texture = load_texture("res/else.png");

    is_preview_visible = FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	double vertical_angle;


    //COLLISION FOR MAP EDGES
    if (camera->position.x >= 20) {
		camera->position.x += -CAMERA_SPEED * time;
	}
	else if (camera->position.x <= -5) {
		camera->position.x += CAMERA_SPEED * time;
	}

	if (camera->position.y >= 20) {
    	camera->position.y += -CAMERA_SPEED * time;
	}
	else if (camera->position.y <= -5) {
    	camera->position.y += CAMERA_SPEED * time;
	}
   // check_piece_collisions(&(scene->king), camera);
    //END OF COLLISION

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
	vertical_angle = degree_to_radian(camera->rotation.y + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
	camera->position.z += cos(vertical_angle) * camera->speed.z * time;
	camera->position.z += sin(vertical_angle) * camera->speed.z * time;
	//printf("x: %lf,y: %lf,z: %lf", camera->rotation.x, camera->rotation.y, camera->rotation.z);
	//printf("x: %lf,y: %lf,z: %lf", camera->position.x, camera->position.y, camera->position.z);
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 0.1, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 0.1);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal / 2;
    camera->rotation.x += vertical / 2;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed){
	camera->speed.z = speed;
}

void show_texture_preview()
{

glLoadIdentity();
   glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("res/crosshair.png"));
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -50);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -50);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -50);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -50);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

}

void show_help()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, load_texture("res/help.png"));
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -23);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -23);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -23);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -23);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

/*void check_piece_collisions(Model* model, Camera* camera) {
	
	double model_x = model->xpos + model->yoff;
	double model_y = model->ypos + model->xoff;
	double camera_x = camera->position.y;
	double camera_y = camera->position.x;
	double r_suare = pow(0.5, 2);
	
	if ( pow((camera_x - model_x), 2) + pow((camera_y - model_y), 2) <= r_suare ) {
		printf("%lf %lf\n", camera_x, camera_y);
	}
	

    //camera->position.y += 1.0 * time;
	
}*/
