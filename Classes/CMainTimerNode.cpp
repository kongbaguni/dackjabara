//
//  CMainTimerNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CMainTimerNode.h"
#include "CGameManager.h"

CMainTimerNode::CMainTimerNode() :
_pTimer(NULL),
_pLabel(NULL),
_pLabelScore(NULL)
{
    
}

CMainTimerNode::~CMainTimerNode()
{
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pLabel);
    CC_SAFE_RELEASE_NULL(_pLabelScore);
}

bool CMainTimerNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();
    setTimer(CTimer::create());

    setLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/digital%s.fnt"), "0"));

    _pLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
    _pLabel->setPosition(Vec2(0, -5));
    addChild(_pLabel);
    
    scheduleUpdate();
    _pTimer->setMaxTime(120000);
    _pTimer->start();
    
    setLabelScore(CLabelAnimate::createWithBMFont(CUtil::getHDSDname("fonts/digital%s.fnt"),0,100));
                  
    _pLabelScore->setAnchorPoint(Vec2(0.5f,1.0f));
    addChild(_pLabelScore);
    _pLabelScore->setPosition(Vec2(0, -40));
    _pLabelScore->setScale(0.7f);
    return true;
}

void CMainTimerNode::update(float dt)
{
    _pLabelScore->update(dt);
    const char* time = textUtil::addCommaText(_pTimer->getTime()/1000);
    _pLabel->setString(time);
    
    int score =
    CGameManager::getInstance()->getPlayerNode()->getModel()->getTotalScore()
    ;
    
    if(score==0)
    {
        _pLabelScore->setNumber(0);
        _pLabelScore->setString("0");
    }
    _pLabelScore->setTargetNumber(score);
    
    if(_pTimer->getTime()==0)
    {
        CGameManager::getInstance()->gameOver();
    }
    
}
