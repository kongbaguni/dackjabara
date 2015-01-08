//
//  CUnitNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 8..
//
//

#include "CUnitNode.h"
CUnitNode::CUnitNode():
_pSprite(NULL),
_pLabel(NULL),
_pTimer(NULL),
_pProgressTimer(NULL)
{
    
}

CUnitNode::~CUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pSprite);
    CC_SAFE_RELEASE_NULL(_pLabel);
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pProgressTimer);
}

bool CUnitNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    setLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), ""));
    addChild(_pLabel);
    _pLabel->setScale(0.5f);
    _pLabel->setVisible(false);
    
    setSprite(Sprite::create());
    addChild(_pSprite);
    
    setTimer(CTimer::create());
 
    setRotation3D(CUtil::getRotate3D());
    
    
    auto progress = Sprite::createWithSpriteFrameName("unit/progressBarBG.png");
    setProgressTImer(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar.png")));
    progress->addChild(_pProgressTimer);
    _pSprite->addChild(progress);
    _pProgressTimer->setPosition3D(Vec3(0,0,1));
    progress->setPosition(Vec2(58,0));
    _pProgressTimer->setPercentage(0.0f);
    _pProgressTimer->runAction(ProgressTo::create(1.0f, 100));
    _pProgressTimer->setType(ProgressTimer::Type::BAR);
    _pProgressTimer->setMidpoint(Vec2(0.0f,0.0f));
    _pProgressTimer->setBarChangeRate(Vec2(1.0f,0.0f));
    _pProgressTimer->setAnchorPoint(Vec2(0.0f,0.0f));

    return true;
}


void CUnitNode::pause()
{
    Node::pause();
    _pSprite->pause();
    _pTimer->pause();
    _pLabel->pause();
}

void CUnitNode::resume()
{
    Node::resume();
    _pSprite->resume();
    _pTimer->resume();
    _pLabel->resume();
}