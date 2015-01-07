//
//  CChikenSprite.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CChikenSprite.h"
#include "CGameManager.h"

CChikenSprite::CChikenSprite():
_eState(state::EGG),
_pTimer(NULL),
_vec2Movement(Vec2(0, 0))
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
    resetTimer();
    scheduleUpdate();
    return true;
}

void CChikenSprite::update(float dt)
{
    //상태에 맞게 그림 고치기
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
    }
    
    //움직일수 있는상태면 움직이게
    {
        float mx = CRandom::getInstnace()->Random(4)-2.0f;
        float my = CRandom::getInstnace()->Random(4)-2.0f;
        if(_vec2Movement.length()==0 | CRandom::getInstnace()->Random(100)==0)
        {
            switch (_eState)
            {
                case state::CHICK:
                case state::COCK:
                case state::HEN:
                    _vec2Movement = Vec2(mx,my);
                    break;
                default:
                    _vec2Movement = Vec2(0,0);
                    break;
            }
            
        }
    }
    //플레이어하고 충돌검사
    {
        CPlayerNode* player = CGameManager::getInstance()->getPlayerNode();
        Vec2 posP = player->getPosition();
        Vec2 pos = getPosition();
        float distance = pos.getDistance(posP);
        bool bPlayerIsJump = player->getSprite()->getPositionY()>10;
        bool bCrash = distance<40;
        bool bActionNotRun = getActionByTag((int)eAction::DEAD)==NULL;
        if(!bPlayerIsJump & bCrash & bActionNotRun)
        {
            player->getModel().chargeEnergy(1000);
            
            
            _vec2Movement = Vec2(0, 0);
            setRotation3D(Vec3(-90,0,0));
//            setFlippedY(true);
            auto action =
            Sequence::create
            (DelayTime::create(1.0f),
             Spawn::create
             (ScaleTo::create(1.0f, 2.0f),
              FadeTo::create(1.0f,0),
              NULL),
             CallFunc::create(CC_CALLBACK_0(CChikenSprite::dead, this)),
             NULL);
            action->setTag((int)eAction::DEAD);
            runAction(action);
            return;
        }
        
    }
    
    //충돌검사 타일맵하고 충돌검사
    {
        switch (_eState)
        {
            case state::CHICK:
            case state::COCK:
            case state::HEN:
            {
                Vec2 prePos = getPosition()+_vec2Movement;
                bool bCrashWall =CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getTileMap(), "bg", "wall", this)._bCrash;
                bool bCrashCharge =
                CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getTileMap(), "bg", "charge", this)._bCrash;
                if(bCrashWall | bCrashCharge)
                {
                  CUtil::eDirection8 move8 = CUtil::getMove8(_vec2Movement);
                    switch (move8) {
                        case CUtil::eDirection8::UP:
                        case CUtil::eDirection8::DOWN:
                        case CUtil::eDirection8::DOWN_LEFT:
                        case CUtil::eDirection8::DOWN_RIGHT:
                            _vec2Movement.y*=-1;
                            break;
                        case CUtil::eDirection8::LEFT:
                        case CUtil::eDirection8::RIGHT:
                            _vec2Movement.x*=-1;
                            break;
                        default:
                            _vec2Movement*=-1;
                            break;
                    }
                    
                    
                }
                setFlippedX(_vec2Movement.x<0);
                setPosition(getPosition()+_vec2Movement);
            }
                break;
            default:
                break;
        }
    }

    if(_pTimer->getTime()>0)
    {
        return;
    }
    _pTimer->start();
    int iRnd = CRandom::getInstnace()->Random(100);
    switch (_eState)
    {
        case state::EGG:
        {
            if(iRnd<40)
            {
                _eState = state::EGG_BROKEN;
            }
            else
            {
                _eState = state::CHICK;
            }
        }break;
        case state::CHICK:
        {
            if(iRnd<30)
            {
                _eState = state::CHICK_DEAD;
            }
            else if(iRnd<90)
            {
                _eState = state::HEN;
            }
            else
            {
                _eState = state::COCK;
            }
        }break;
        case state::CHICK_DEAD:
        case state::EGG_BROKEN:
        {
            removeFromParentAndCleanup(true);
        }break;
        case state::HEN:
        {
            if(getParent()->getChildrenCount()<100)
            {
                auto egg = CChikenSprite::create();
                getParent()->addChild(egg);
                egg->setPosition(getPosition());
                runAction(JumpBy::create(0.3f, Vec2(0,0), 50, 1));
            }
        }break;
        default:
            break;
    }
    resetTimer();
    
    
}
void CChikenSprite::dead()
{
    removeFromParent();
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

void CChikenSprite::resetTimer()
{
    if(getReferenceCount()==0)
    {
        return;
    }
    int time = CRandom::getInstnace()->Random(10)+10;
    time*=1000;
    _pTimer->setMaxTime(time);
    _pTimer->start();
}