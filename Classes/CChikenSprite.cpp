//
//  CChikenSprite.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CChikenSprite.h"
CChikenSprite::CChikenSprite():
_eState(state::EGG),
_pTimer(NULL)
{
    
}
CChikenSprite::~CChikenSprite()
{
    CC_SAFE_RELEASE_NULL(_pTimer);
    
}

bool CChikenSprite::init()
{
    if(!Sprite::initWithSpriteFrameName("unit/egg.png"))
    {
        return  false;
    }
    setTimer(CTimer::create());
    _pTimer->setMaxTime(10000);
    _pTimer->start();
    schedule(schedule_selector(CChikenSprite::update),1.0f);
    setRotation3D(Vec3(90,0,0));
    setAnchorPoint(Vec2(0.5f,0.0f));
    setPosition3D(Vec3(0, 0, 50));
    return true;
}

void CChikenSprite::update(float dt)
{
    std::string frameName = "unit/";
    switch (_eState)
    {
        case state::EGG:
            frameName+="egg.png";
            break;
        case state::EGG_BROKEN:
            frameName+="eggBroken.png";
            break;
        case state::CHICK:
            frameName+="chick.png";
            break;
        case state::CHICK_DEAD:
            frameName+="chickDead.png";
            break;
        case state::COCK:
            frameName+="cock.png";
            break;
        case state::HEN:
            frameName+="hen.png";
            break;
        default:
            break;
    }
    initWithSpriteFrameName(frameName);
    
    if(_pTimer->getTime()>0)
    {
        return;
    }
    _pTimer->start();
    switch (_eState)
    {
        case state::EGG:
            _eState = state::EGG_BROKEN;
            break;
        default:
            break;
    }
    
    
}

void CChikenSprite::pause()
{
    Sprite::pause();
    _pTimer->pause();
}

void CChikenSprite::resume()
{
    Sprite::resume();
    _pTimer->resume();
}