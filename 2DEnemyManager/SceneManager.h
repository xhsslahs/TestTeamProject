#pragma once
#include "SingletonBase.h"
#include <string>
#include <map>

class GameNode;

class SceneManager : public SingletoneBase<SceneManager>
{
private:
	static GameNode* currentScene;	//���� ��
	static GameNode* readyScene;	//�ٲ� ��(��� ��)

	map<string, GameNode*> sceneList;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	GameNode* AddScene(string sceneName, GameNode* scene);

	void ChangeScene(string sceneName);
};