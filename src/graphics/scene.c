

#include "scene.h"


Scene *SceneInit()
{
    Scene *scene = (Scene*)calloc(1,sizeof(Scene));
    return scene;
}
