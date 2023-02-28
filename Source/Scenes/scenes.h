#ifndef __BSTH_SCENES_H__
#define __BSTH_SCENES_H__
#include <stdlib.h>
#include "./Name_Creator/name_creator.h"
#include "entities/scene/scene.h"


extern scene_t **scenes;
extern unsigned int number_of_scenes;
void addSceneToSceneTree(scene_t *scene);

#endif //__BSTH_SCENES_H__
