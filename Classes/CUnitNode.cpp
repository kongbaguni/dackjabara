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
_pTimer(NULL),
_iHPmax(30),
_iHP(30),
_iAttack(1),
_vec2Movement(Vec2(0,0)),
_eAttribute(eAttribute::NONE)
{
    _vDamageLabelList.clear();
    
}

CUnitNode::~CUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pSprite);
    CC_SAFE_RELEASE_NULL(_pTimer);
}

bool CUnitNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    setSprite(Sprite::create());
    addChild(_pSprite);
    
    setTimer(CTimer::create());
 
    setRotation3D(CUtil::getRotate3D());
    _iHP = _iHPmax;
    

    return true;
}

bool CUnitNode::addDamage(CUnitNode *unit)
{
    // 속성공격 
    int iDamageSum = 1;
    eAttribute tAtt = unit->getAttribute();
    switch(_eAttribute)
    {
        case eAttribute::FIRE:
            if(tAtt== eAttribute::WATER)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::WATER:
            if(tAtt == eAttribute::WOOD)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::WOOD:
            if(tAtt == eAttribute::FIRE)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::DARK:
            if(tAtt == eAttribute::LIGHT)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::LIGHT:
            if(tAtt == eAttribute::DARK)
            {
                iDamageSum = 2;
            }
            default:
            break;
    }
    
    int iDamage = unit->getAttack()*iDamageSum;
    if(addDamage(iDamage))
    {
        return true;
    }
    return false;
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
    
    std::string txt = textUtil::addCommaText(iDamage);
    txt+=" Point Damage";
    popupLabel(txt, Color3B(255,0,0));
    return true;
}

void CUnitNode::popupLabel(std::string text, cocos2d::Color3B color)
{
    if(_vDamageLabelList.size()>10)
    {
        auto first =_vDamageLabelList.front();
        removeChild(first);
        _vDamageLabelList.erase(_vDamageLabelList.begin());
    }
    
    auto labelDamage = Label::createWithBMFont(CUtil::getHDSDname("fonts/title2%s.fnt"), text);
    labelDamage->setColor(color);
    addChild(labelDamage);
    _vDamageLabelList.pushBack(labelDamage);
    labelDamage->runAction
    (Spawn::create
     (MoveBy::create(1.0f, Vec2(0, 100)),
      FadeOut::create(1.0f),
      NULL));
    
}
void CUnitNode::heal(int iHeal)
{
    if(_iHP<_iHPmax)
    {
        std::string txt = textUtil::addCommaText(iHeal);
        txt+=" Point Healing";
        popupLabel(txt,Color3B(50,250,150));
    }
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


void CUnitNode::pause()
{
    Node::pause();
    _pSprite->pause();
    _pTimer->pause();
}

void CUnitNode::resume()
{
    Node::resume();
    _pSprite->resume();
    _pTimer->resume();
}

void CUnitNode::setColorReset(float dt)
{
    _pSprite->setColor(Color3B(255, 255, 255));
}