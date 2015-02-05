//
//  CTitleScene.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CUtil.h"
#include "CGameManager.h"
using namespace CocosDenshion;

CTitleScene::CTitleScene()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CUtil::getHDSDname("texturePacker/title%s.plist"));
    
}
CTitleScene::~CTitleScene()
{
    
}
bool CTitleScene::init()
{
    if(!Scene::init())
    {
        return false;
    }

    Size winsize = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(255, 0, 0,255), 1920, 1280);
    addChild(layer);
    
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/01 A Night Of Dizzy Spells.mp3");
    auto bg = Sprite::createWithSpriteFrameName("title.png");
    bg->setPosition(Vec2(winsize.width/2,winsize.height/2));
    addChild(bg);
    
    


    return true;
}

void CTitleScene::changeScene(float dt)
{
    Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("home"));
}

void CTitleScene::onEnter()
{
    Scene::onEnter();
    CGameManager::getInstance()->newGameInit();
    schedule(schedule_selector(CTitleScene::changeScene), 3.0f);

}


void CTitleScene::onExit()
{
    Scene::onExit();
}