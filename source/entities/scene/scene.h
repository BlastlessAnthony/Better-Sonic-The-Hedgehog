#ifndef __BSTH_SCENE_TEMPLATE_H__
#define __BSTH_SCENE_TEMPLATE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct scene_t {
    void (*initialize) (void);
    void (*update) (void);
    void (*destroy) (void);
} scene_t;

scene_t *newScene( void (*initialization_method)(void), void (*update_method)(void), void (*destroy_method)(void));

#endif //__BSTH_SCENE_TEMPLATE_H__
