#include "Scene.h"

Scene* newScene(void (*initialization_method)(void), void (*update_method)(float), void (*destroy_method)(void))
{
    Scene* scene = malloc(sizeof(Scene));
    if (!scene)
        return NULL;

    scene->initialize = initialization_method;
    scene->update = update_method;
    scene->destroy = destroy_method;
    return scene;
}

void destroyScene (Scene *scene)
{
    if (scene) {
        free(scene);
    }
}
