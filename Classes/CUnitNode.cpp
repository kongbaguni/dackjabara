//
//  CUnitNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 8..
//
//

#include "CUnitNode.h"
#include "CUtil.h"
CUnitNode::CUnitNode():
_pSprite(NULL),
_pLabel(NULL),
_pTimer(NULL),
_pProgressTimer1(NULL),
_pProgressTimer2(NULL),
_iHPmax(30),
_iHP(30),
_iAttack(1),
_vec2Movement(Vec2(0,0))
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
    _iHP = _iHPmax;
    
    
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

bool CUnitNode::addDamage(int iDamage)
{
    _iHP-=iDamage;
    if(_iHP<0)
    {
        _iHP = 0;
        return false;
    }
    _pSprite->setColor(Color3B(255, 0, 0));
    unschedule(schedule_selector(CUnitNode::setColorReset));
    scheduleOnce(schedule_selector(CUnitNode::setColorReset), 1.0f);
    return true;
}
void CUnitNode::heal(int iHeal)
{
    _iHP+=iHeal;
    if(_iHP>=_iHPmax)
    {
        _iHP = _iHPmax;
    }
}
void CUnitNode::setHPmax(int iHPMax)
{
    if(iHPMax>_iHPmax)
    {
        _iHP = iHPMax;
    }
    _iHPmax = iHPMax;
}

void CUnitNode::update(float dt)
{
    float p = (float)getHP()/(float)_iHPmax*100.0f;
    _pProgressTimer2->setPercentage(p);
    
    setLocalZOrder(10000000-getPositionY());

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

void CUnitNode::setColorReset(float dt)
{
    _pSprite->setColor(Color3B(255, 255, 255));
}