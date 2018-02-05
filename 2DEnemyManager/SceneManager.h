#pragma once
#include "SingletonBase.h"
#include <string>
#include <map>

class GameNode;

class SceneManager : public SingletoneBase<SceneManager>
{
private:
	static GameNode* currentScene;	//ÇöÀç ¾À
	static GameNode* readyScene;	//¹Ù²ð ¾À(´ë±â ¾À)

	map<string, GameNode*> sceneList;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	GameNode* AddScene(string sceneName, GameNode* scene);

	void ChangeScene(string sceneName);
};