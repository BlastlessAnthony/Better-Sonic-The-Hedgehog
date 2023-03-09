#include "Scene Manager.h"
Scene* currentScene = NULL;

/// <summary>
/// Instantiates all the scenes before the game starts.
/// </summary>
void instaniateScenes(void) {
	sceneSegaSplashScreen = newScene(initializeSegaSplashScreenScene, updateSegaSplashScreenScene, destroySegaSplashScreen);
	sceneLogosSplashScreen = newScene(initializeLogosSplashScreenScene, updateLogosSplashScreenScene, destroyLogosSplashScreenScene);
}

/// <summary>
/// Changes the current scene.
/// </summary>
/// <param name="scene">The scene to change to.</param>
void changeToScene(Scene* scene) {
	if (currentScene) {
		(currentScene->destroy)();
	}
    
	currentScene = scene;
	if (scene) {
		(currentScene->initialize)();
	}
		
}


void destroyScenes(void)
{
    destroyScene(sceneSegaSplashScreen);
    destroyScene(sceneLogosSplashScreen);
}
