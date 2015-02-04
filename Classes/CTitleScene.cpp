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

bool CTitleScene::init()
{
    if(!Scene::init())
    {
        return false;
    }

    Size winsize = Director::getInstance()->getWinSize();
    
    auto layer = LayerColor::create(Color4B(255, 0, 0,255), 1920, 1280);
    addChild(layer);
    
    auto layer2 = LayerColor::create(Color4B(0, 50, 0,100), 10, 10);
    layer2->setPosition(winsize.width/2-1920/4,winsize.height/2-1280/4);
    addChild(layer2);
    

    auto title = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "Dack Jab A Ra");
    title->setPosition(winsize.width/2, winsize.height/2);
    addChild(title);
    
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM/01 A Night Of Dizzy Spells.mp3");
    
    


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