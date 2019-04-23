#include "callbacks.h"
#include "board.h"

#define BUFSIZE 512
#define VIEWPORT_RATIO (16.0 / 9.0)
#define VIEWPORT_ASPECT 50.0
#define CAMERA_SPEED 5

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }

    if(!esc){
        show_help();
    }

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int button, int state, int x, int y)
{
    if(state != GLUT_DOWN)
    return;

    int window_width = glutGet(GLUT_WINDOW_WIDTH);
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);

    GLbyte color[4];
    GLfloat depth;
    unsigned int index;
    
    glReadPixels(x, window_height - y - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, window_height - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
    if(index <= 32){
        pieceClicked(&scene, index);
    }else{ 
        qubeClicked(&scene, index);
    }
    

    //TODO: this:    mouseSeleted();
    
	/*GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;

    glGetIntegerv(GL_VIEWPORT, viewport);

    glSelectBuffer(BUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);

    glInitNames();
    glPushName(-1);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
      create 5x5 pixel pick region near cursor location 
    gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3] - y),
        5.0, 5.0, viewport);
    glOrtho(0.0, 8.0, 0.0, 8.0, -0.5, 2.5);
    render_Board(scene, GL_SELECT);
    glPopMatrix();
    glFlush();

    hits = glRenderMode(GL_RENDER);
    processHits(hits, selectBuf);*/
	
  /* if ((button == 3) || (button == 4)) 
   {
      
       if (state == GLUT_UP) return; 
       (button == 3) ? set_camera_speed(&camera, 1) : set_camera_speed(&camera, -1);
   }else{  
       (state == GLUT_DOWN) ? set_camera_speed(&camera, -1) : set_camera_speed(&camera, 1);
		mouse_position.x = x;
		mouse_position.y = y;
   }
	set_camera_speed(&camera, 0.0);*/
}

void motion(int x, int y)
{
    
}

void processPassiveMouseMotion(int x, int y){

    if (esc) { 
        int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
        int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

        rotate_camera(&camera, centerX - x, centerY - y);
        
        glutPostRedisplay();
        glutWarpPointer(centerX, centerY);
    } 

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, CAMERA_SPEED);
        break;
    case 's':
        set_camera_speed(&camera, -CAMERA_SPEED);
        break;
    case 'a':
        set_camera_side_speed(&camera, CAMERA_SPEED);
        break;
    case 'd':
        set_camera_side_speed(&camera, -CAMERA_SPEED);
        break;
	case 'e':
        set_camera_vertical_speed(&camera, CAMERA_SPEED);
        break;
	case 'q':
        set_camera_vertical_speed(&camera, -CAMERA_SPEED);
        break;
    case 't':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;
    case 'l':
        //makeUglyMove(scene);
        break;
        /*
    case '5':
        toggleSelected(&scene);
        break;
    case '1':
        moveSelection(&scene, -1, -1);
        break;
    case '2':
        moveSelection(&scene, -1, 0);
        break;
    case '3':
        moveSelection(&scene, -1, 1);
        break;
    case '4':
        moveSelection(&scene, 0, -1);
        break;
    case '6':
        moveSelection(&scene, 0, 1);
        break;
    case '7':
        moveSelection(&scene, 1, -1);
        break;
    case '8':
        moveSelection(&scene, 1, 0);
        break;
    case '9':
        moveSelection(&scene, 1, 1);
        break;
        */
    case 27:
		if (esc) {
            esc = FALSE;
        }
        else {
            int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
            int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

            glutPostRedisplay();
            glutWarpPointer(centerX, centerY);
            esc = TRUE;
        }
		break;
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
	case 'e':
	case 'q':
        set_camera_vertical_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    

    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}
