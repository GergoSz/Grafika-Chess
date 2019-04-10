#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "model.h"
#include "board.h"

typedef struct Scene
{
    Camera camera;
    Model cube;
	Model pawn;
    Model knight;
    Model bishop;
    Model rook;
    Model queen;
    Model king;
    Model skybox;
    Material material;
    Board board;
    GLuint light_texture;
    GLuint dark_texture;
    GLuint selected_texture;
    GLuint available_texture;
    GLuint skybox_texture;
    GLuint base_texture;
} Scene;

   //struct Model king;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene( Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void init_Board(Scene* scene);

void render_Board(Scene* scene);

void toggleSelected(Scene* scene);

void moveSelection(Scene* scene, int x, int y);

#endif /* SCENE_H */
