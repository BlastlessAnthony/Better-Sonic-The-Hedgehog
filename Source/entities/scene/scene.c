#include "scene.h"

scene_t *newScene( void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void))
{
    scene_t *scene = malloc(sizeof(scene_t*));
    if (!scene) {return NULL;}

    scene->initialize = initialization_method;
    scene->update = update_method;
    scene->destroy = destroy_method;
    return (scene);
}
