#include "scene_tree.h"

scene_tree_t *newSceneTree()
{
    scene_tree_t *__scene_tree = malloc(sizeof(scene_tree_t*));
    if (!__scene_tree)
        return NULL;

    __scene_tree->number_of_scenes = 0;
    __scene_tree->scenes = NULL;
    return __scene_tree;
}

scene_t *addSceneToSceneTree(scene_tree_t *scene_tree, scene_t *scene)
{
    scene_tree_t *__scene_tree = realloc(scene_tree, sizeof(scene_tree));
    if (!__scene_tree)
        printf("Failed to add scene to scene tree.");
        free(__scene_tree);
        return scene_tree;

    __scene_tree->scenes = calloc(scene_tree->number_of_scenes+1, sizeof(scene_t*)+100);
    memcpy(__scene_tree->scenes, scene_tree->scenes, sizeof(scene_tree->scenes));
    free(scene_tree);
    return __scene_tree;
}

void destroySceneTree(scene_tree_t *scene_tree)
{
    
}
