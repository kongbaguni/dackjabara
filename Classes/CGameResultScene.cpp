//
//  CGameResultScene.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 1. 30..
//
//

#include "CGameResultScene.h"

#include "CUtil.h"
#include "CGameManager.h"
#include "CSceneManager.h"
CGameResultScene::CGameResultScene():
_pLabelTotalScore(NULL)
{
    
}
CGameResultScene::~CGameResultScene()
{
    CC_SAFE_RELEASE_NULL(_pLabelTotalScore);
    
}

bool CGameResultScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();
    
    auto bg = LayerColor::create(Color4B(255, 255, 155, 255));
    addChild(bg);
    
    
    setLabelTotalScore(Label::createWithBMFont(CUtil::getHDSDname("fonts/digital%s.fnt"), "0"));
    _pLabelTotalScore->setPosition(Vec2(winsize.width*0.5f,winsize.height*0.7f));
    addChild(_pLabelTotalScore);
    return true;
}



void CGameResultScene::onEnter()
{
    _pLabelTotalScore->setString(textUtil::addCommaText(CGameManager::getInstance()->getPlayerNode()->getModel()->getTotalScore()));
    Scene::onEnter();
    scheduleOnce(schedule_selector(CGameResultScene::returnToTitle), 5.0f);
    
}

void CGameResultScene::returnToTitle(float dt)
{
    Director::getInstance()->pushScene(TransitionCrossFade::create(1.0f, CSceneManager::getInstance()->getScene("title")));
}