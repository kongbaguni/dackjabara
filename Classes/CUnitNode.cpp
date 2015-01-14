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
_pProgressTimer1(NULL),
_pProgressTimer2(NULL),
_iHPmax(30),
_iDamage(0),
_iAttack(1)
{
    
}

CUnitNode::~CUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pSprite);
    CC_SAFE_RELEASE_NULL(_pLabel);
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pProgressTimer1);
    CC_SAFE_RELEASE_NULL(_pProgressTimer2);
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
    _pSprite->addChild(progress);
    progress->setPosition(Vec2(58,0));
    
    setProgressTimer1(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar1.png")));
    setProgressTimer2(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar2.png")));
    
    ProgressTimer* progressList[2] =
    {
        _pProgressTimer1,_pProgressTimer2
    };
    
    for(int i=0; i<2; i++)
    {
        //progressList[i]->setPosition3D(Vec3(0,0,1));
        
        progressList[i]->setPercentage(0.0f);
        progressList[i]->runAction(ProgressTo::create(1.0f, 100));
        progressList[i]->setType(ProgressTimer::Type::BAR);
        progressList[i]->setMidpoint(Vec2(0.0f,0.0f));
        progressList[i]->setBarChangeRate(Vec2(1.0f,0.0f));
        progressList[i]->setAnchorPoint(Vec2(0.0f,0.0f));
        progress->addChild(progressList[i]);
    }
    
    scheduleUpdate();

    return true;
}

void CUnitNode::addDamage(int iDamage)
{
    _iDamage+=iDamage;
    if(_iDamage>_iHPmax)
    {
        _iDamage = _iHPmax;
    }
}
int CUnitNode::getHP()
{
    int result = _iHPmax-_iDamage;
    return result;
}

void CUnitNode::update(float dt)
{
    float p = (float)getHP()/(float)_iHPmax*100.0f;
    _pProgressTimer2->setPercentage(p);
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