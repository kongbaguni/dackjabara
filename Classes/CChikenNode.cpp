//
//  CChikenNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CChikenNode.h"
#include "CGameManager.h"

CChikenNode::CChikenNode():
_eState(state::EGG)
{
    
}
CChikenNode::~CChikenNode()
{
    unscheduleUpdate();
 //   CUnitNode::~CUnitNode();
    
}

bool CChikenNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    
    setAttack(0);
    auto _pSprite = getSprite();
    _pSprite->setSpriteFrame("unit/egg.png");
    setContentSize(_pSprite->getContentSize());
    setAnchorPoint(_pSprite->getAnchorPoint());
    //_pSprite->setPosition(Vec2(_pSprite->getContentSize().width/2, -_pSprite->getContentSize().height));
    _pSprite->setAnchorPoint(Vec2(0.5f,0.0f));
                          
  
//    setRotation3D(Vec3(0, 0, 0));
    resetTimer();
    getTimer()->start();
    
    //setPosition3D(Vec3(0,0,this->getContentSize().height/4-10));
    setAnchorPoint(Vec2(0.5, 0.0));
    setScale(0.5f);
    
    
    getTimer()->setMaxTime(CRandom::getInstnace()->Random(20)*1000+3000);
    
    getProgressTimer1()->getParent()->setScale(0.5f,1.0f);
  //  getProgressTimer1()->getParent()->setRotation3D(Vec3(90, 0, 0));
    getProgressTimer1()->getParent()->setPosition(45.f, -5.0f);
    
   
    return true;
}
void CChikenNode::onEnter()
{
    CUnitNode::onEnter();
    scheduleUpdate();

}

void CChikenNode::update(float dt)
{
    CUnitNode::update(dt);
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
        auto player = CGameManager::getInstance()->getPlayerNode();
        auto _pSprite = getSprite();
        if(player)
        {
            Vec2 posP = player->getPosition();
            Vec2 pos = getPosition();
            pos.x-=player->getContentSize().width/4;
            float distance = pos.getDistance(posP);
            float pSY =player->getSprite()->getPositionY();
            long pJumpTimeInterval = timeUtil::millisecondNow()-player->getJumpStartTime();
            
            bool bPlayerIsJumping = pSY > 30;
            bool bPlayerIsAfertJump = pJumpTimeInterval>300;
            bool bCrash = distance<40;
            bool bActionNotRun = getActionByTag((int)eAction::DEAD)==NULL;
            if(bCrash & bActionNotRun & !bPlayerIsJumping)
            {
                //if(bPlayerIsAfertJump)
                 {
                    _pSprite->setColor(Color3B(CRandom::getInstnace()->Random(155)+100,CRandom::getInstnace()->Random(155)+100 , 255));
                    addDamage(player->getAttack()*(player->getJumpCount()*10+1));
                    getSprite()->
                    runAction
                    (CCSequence::create
                     (EaseExponentialInOut::create(ScaleTo::create(0.3f, 1.2f, 0.3f)),
                      EaseExponentialInOut::create(ScaleTo::create(0.3f, 1.0f,1.0f)),
                      NULL
                      )
                     );
                      
                    if(getHP()==0)
                    {
                        getSprite()->runAction
                        (Sequence::create
                         (FadeOut::create(1.0f),
                          CallFunc::create(CC_CALLBACK_0(CChikenNode::dead, this))
                          , NULL));
                        
                    }
                }
                
            }else
            {
                _pSprite->setColor(Color3B(255,255,255));
                player->getSprite()->setColor(Color3B(255,255,255));
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
                prePos.y+=getContentSize().height/2;
                prePos.x-=getContentSize().width/4;
                CUtil::sTMXcrashTestValue value = CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getTileMap(), "bg", "wall", prePos, getMovement());
                
                if(value._pCrashTile!=NULL && !value._pCrashTile->getActionByTag(123))
                {
                    auto action =Sequence::create(FadeTo::create(0.5f,100),FadeTo::create(2.0f,255), NULL);
                    action->setTag(123);
                    
                    value._pCrashTile->runAction(action);
                    value._pCrashTile->setColor(Color3B(CRandom::getInstnace()->Random(155)+100,CRandom::getInstnace()->Random(155)+100 , 255));
                }
                
                bool bCrashWall =value._bCrash;
                
                if(bCrashWall)
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
        getProgressTimer1()->setPercentage(ff);
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
            if(getParent()->getChildrenCount()<50)
            {
                auto egg = CChikenNode::create();
                getParent()->addChild(egg);
                egg->setPosition(getPosition());
                getSprite()->runAction(JumpBy::create(0.3f, Vec2(0,0), 50, 1));
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
                    setHPmax(50);
                    break;
                case state::EGG_BROKEN:
                    frameName+="eggBroken.png";
                    setHPmax(10);
                    break;
                case state::CHICK:
                    frameName+="chick.png";
                    setHPmax(60);
                    break;
                case state::CHICK_DEAD:
                    frameName+="chickDead.png";
                    setHPmax(10);
                    break;
                case state::COCK:
                    frameName+="cock.png";
                    setHPmax(120);
                    break;
                case state::HEN:
                    frameName+="hen.png";
                    setHPmax(200);
                    break;
                default:
                    break;
            }
            getSprite()->setSpriteFrame(frameName);
            
        }
    }
    resetTimer();
    
    
}
void CChikenNode::dead()
{
    CGameManager::getInstance()->getPlayerNode()->getModel()->addScoreWithChicken(this);
    removeFromParent();
}

void CChikenNode::resetTimer()
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