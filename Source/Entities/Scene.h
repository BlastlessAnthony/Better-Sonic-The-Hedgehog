#ifndef __BSTH_SCENE_TEMPLATE_H__
#define __BSTH_SCENE_TEMPLATE_H__

#include <stdio.h>
#include <stdlib.h>

/// @brief An object that holds function pointers to other source files.
typedef struct {
    void (*initialize) (void);
    void (*update) (float);
    void (*destroy) (void);
} Scene;

/**
 * @brief Creates a new scene.
 * 
 * @param initialization_method The function called when the game is first ran or the scene is swiched.
 * @param update_method The function called every frame.
 * @param destroy_method The function called when the scene is switched.
 * @returns A created scene or NULL
 * if the malloc fails. Be careful!
 */
extern Scene *newScene( void (*initialization_method)(void), void (*update_method)(float), void (*destroy_method)(void));

extern void destroyScene (Scene *scene);

#endif //__BSTH_SCENE_TEMPLATE_H__
