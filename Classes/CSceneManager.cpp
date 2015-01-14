//
//  CSceneManager.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 11..
//
//

#include "CSceneManager.h"

CSceneManager::CSceneManager()
{
    
}
CSceneManager::~CSceneManager()
{
    _mapScene.clear();
}

CSceneManager* CSceneManager::getInstance()
{
    static CSceneManager* instance = nullptr;
    if(instance == nullptr)
    {
        instance = new CSceneManager();
    }
    return instance;
}

void CSceneManager::addScene(cocos2d::Scene *scene, std::string key)
{
    typedef std::pair <std::string, Scene*> scene_pair;
    scene->retain();
    _mapScene.insert(scene_pair(key,scene));
                     
}

Scene* CSceneManager::getScene(std::string key)
{
    Scene* scene =  _mapScene[key];
    return scene;
}
