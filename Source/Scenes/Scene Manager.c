#include "Scene Manager.h"
Scene* currentScene = NULL;

/// <summary>
/// Instantiates all the scenes before the game starts.
/// </summary>
void instaniateScenes() {
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

	currentScene = realloc(currentScene, sizeof(scene));
	currentScene = scene;
	if (scene) {
		(currentScene->initialize)();
	}
		
}
