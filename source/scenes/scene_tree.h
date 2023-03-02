#ifndef __BSTH_SCENE_TREE_H_
#define __BSTH_SCENE_TREE_H_
#include <stdlib.h>
#include <string.h>
#include "scene.h"
/// @brief An object to hold multiple scenes.

typedef struct {
    unsigned int number_of_scenes;
    scene_t **scenes;
} scene_tree_t;

/// @brief Creates a new scene tree.
/// @returns A new scene tree or NULL if the malloc fails.
scene_tree_t *newSceneTree();

/// @brief Adds a scene to an existing scene tree.
/// @param scene The scene to add.
/// @returns A new scene tree to replace the existing one or the existing one if it failed.
scene_t *addSceneToSceneTree(scene_tree_t *scene_tree, scene_t *scene);

/// @brief Destroys a scene tree, but not its scenes.
/// @param scene_tree 
void destroySceneTree(scene_tree_t *scene_tree);
#endif //__BSTH_SCENE_TREE_H_
