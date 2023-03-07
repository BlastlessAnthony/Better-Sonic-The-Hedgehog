#include "scene.h"

Scene* newScene(void (*initialization_method)(), void (*update_method)(float), void (*destroy_method)())
{
    Scene* scene = malloc(sizeof(Scene*));
    if (!scene)
        return NULL;

    scene->initialize = initialization_method;
    scene->update = update_method;
    scene->destroy = destroy_method;
    return scene;
}
