//
//  CMainTimerNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CMainTimerNode.h"

CMainTimerNode::CMainTimerNode() :
_pTimer(NULL),
_pLabel(NULL)
{
    
}

CMainTimerNode::~CMainTimerNode()
{
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pLabel);
}

bool CMainTimerNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();
    setTimer(CTimer::create());

    setLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "0"));
    _pLabel->setPosition(Vec2(winsize.width/2,winsize.height));
    _pLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
    addChild(_pLabel);
    
    scheduleUpdate();
    _pTimer->setMaxTime(120000);
    _pTimer->start();
    return true;
}

void CMainTimerNode::update(float dt)
{
    const char* time = textUtil::addCommaText(_pTimer->getTime()/1000);
    _pLabel->setString(time);
}


