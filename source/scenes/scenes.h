#ifndef __BSTH_SCENE_MANAGER_H__
#define __BSTH_SCENE_MANAGER_H__
#include "scene.h"
#include "name_creator/name_creator.h"

extern unsigned int number_of_scenes;
extern scene_t **scene_tree;

void addSceneToSceneTree(scene_t *scene);
void addNewSceneToSceneTree(void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void));

#endif //__BSTH_SCENE_MANAGER_H__
