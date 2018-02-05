#include "stdafx.h"

GameNode* SceneManager::currentScene = NULL;
GameNode* SceneManager::readyScene = NULL;

void SceneManager::Init()
{
	currentScene = NULL;
	readyScene = NULL;
}

void SceneManager::Release()
{
	map<string, GameNode*>::iterator it;

	for (it = sceneList.begin(); it != sceneList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second = currentScene)
				it->second->Release();
			delete it->second;
			it = sceneList.erase(it);
		}
		else
		{
			it++;
		}
	}

	sceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene)
		currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
		currentScene->Render(hdc);
}

GameNode * SceneManager::AddScene(string sceneName, GameNode * scene)
{
	if (!scene)
		return NULL;

	sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

void SceneManager::ChangeScene(string sceneName)
{
	map<string, GameNode*>::iterator it;

	it = sceneList.find(sceneName);

	if (it == sceneList.end())
		return;

	if (it->second == currentScene)
		return;

	it->second->Init();

	if (currentScene)
		currentScene->Release();

	currentScene = it->second;
}
