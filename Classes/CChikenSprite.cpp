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
_vec2Movement(Vec2(0, 0))
{
    
}
CChikenSprite::~CChikenSprite()
{
    unscheduleUpdate();
 //   CUnitNode::~CUnitNode();
    
}

bool CChikenSprite::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    
    auto _pSprite = getSprite();
    _pSprite->setSpriteFrame("unit/egg.png");
    setContentSize(_pSprite->getContentSize());
    setAnchorPoint(_pSprite->getAnchorPoint());
    _pSprite->setPosition(Vec2(_pSprite->getContentSize().width/2, -_pSprite->getContentSize().height));
    _pSprite->setAnchorPoint(Vec2(0.5f,0.0f));
                          
  
    setRotation3D(Vec3(0, 0, 0));
    resetTimer();
    getTimer()->start();
    
    scheduleUpdate();
    setPosition3D(Vec3(0,0,this->getContentSize().height/4-10));
    setAnchorPoint(Vec2(0.5, 0.0));
    setScale(0.5f);
    
    
    getTimer()->setMaxTime(CRandom::getInstnace()->Random(20)*1000+3000);
    
    getProgressTImer()->getParent()->setScale(0.5f);
    getProgressTImer()->getParent()->setPosition(45.f, -5.0f);
   
    return true;
}

void CChikenSprite::update(float dt)
{
    getLabel()->setString(textUtil::addCommaText(getLocalZOrder()));


    //움직일수 있는상태면 움직이게
    {
        float mx = CRandom::getInstnace()->Random(4)-2.0f;
        float my = CRandom::getInstnace()->Random(4)-2.0f;
        if(_vec2Movement.length()==0)
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
        auto _pSprite = getSprite();
        if(player)
        {
            Vec2 posP = player->getPosition();
            Vec2 pos = getPosition();
            float distance = pos.getDistance(posP);
            bool bPlayerIsJump = player->getSprite()->getPositionY()>10;
            bool bCrash = distance<20;
            bool bActionNotRun = getActionByTag((int)eAction::DEAD)==NULL;
            if(!bPlayerIsJump & bCrash & bActionNotRun)
            {
                _pSprite->setColor(Color3B(255, 0, 0));
                
                
                //            _vec2Movement = Vec2(0, 0);
                ////            setFlippedY(true);
                //            auto action =
                //            Sequence::create
                //            (DelayTime::create(1.0f),
                //             Spawn::create
                //             (MoveBy::create(1.0f, Vec2(0,300)),
                //              FadeTo::create(1.0f,0),
                //              NULL),
                //             CallFunc::create(CC_CALLBACK_0(CChikenSprite::dead, this)),
                //             NULL);
                //            action->setTag((int)eAction::DEAD);
                //            runAction(action);
                //            return;
            }else
            {
                _pSprite->setColor(Color3B(255, 255, 255));
            }
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
                getSprite()->setFlippedX(_vec2Movement.x<0);
                setPosition(getPosition()+_vec2Movement);
            }
                break;
            default:
                break;
        }
    }

    {
        float time = getTimer()->getTime();
        float maxTimt = getTimer()->getMaxTime();
        float ff = time / maxTimt *100.0f;
        if(ff>99)
        {
            ff = 99;
        }
        getProgressTImer()->setPercentage(ff);
        if(ff>0)
        {
            return;
        }
    }
    getTimer()->start();
    getTimer()->setMaxTime(CRandom::getInstnace()->Random(20)+10);
    int iRnd = CRandom::getInstnace()->Random(100);
    state oldState = _eState;
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
            return;
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
    
    if(oldState!=_eState)
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
            getSprite()->setSpriteFrame(frameName);
            
        }
    }
    resetTimer();
    
    
}
void CChikenSprite::dead()
{
    removeFromParent();
}

void CChikenSprite::resetTimer()
{
    if(getReferenceCount()==0 || getLabel()==NULL)
    {
        return;
    }
    int time = CRandom::getInstnace()->Random(10)+10;
    time*=1000;
    getTimer()->setMaxTime(time);
    getTimer()->start();
}