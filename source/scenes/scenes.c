#include "./scenes.h"

scene_t **scenes = NULL;
unsigned int number_of_scenes = 0;

void addSceneToSceneTree(scene_t *scene)
{
    __scenes = realloc(scenes, scene);
    if (!__scenes) {
        __scenes[number_of_scenes] = scene;
        scenes = __scenes;
    }
}
