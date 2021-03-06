//
//  CChikenNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CChikenNode.h"
#include "CGameManager.h"
#include "CBulletNode.h"

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
    if(!CAvatarUnitNode::init())
    {
        return false;
    }
    static bool bPreload = false;
    if(!bPreload)
    {
        SimpleAudioEngine::getInstance()->preloadEffect("effect/roosterCrow.mp3");
        bPreload = true;
    }
    
    setAttack(0);
    auto _pSprite = getSprite();
    _pSprite->setSpriteFrame("unit/egg.png");
  //  setContentSize(_pSprite->getContentSize());
   // setAnchorPoint(_pSprite->getAnchorPoint());
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
    if(getParent()==NULL)
    {
        return;
    }

    CUnitNode::update(dt);
    getLabel()->setString(textUtil::addCommaText(getLocalZOrder()));
    
    if(CGameManager::getInstance()->getIsGameOver())
    {
        removeFromParentAndCleanup(true);
        return;
    }


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
            float distanceParticle = pos.getDistance(player->getParticleAfterJump()->getPosition());
            
            float pSY =player->getSprite()->getPositionY();
            int iPlayerJumpCnt = player->getJumpCount()+1;
            
            
            bool bPlayerIsJumping = pSY > 30;
            
            bool bCrashWithPlayer = distance<50;
            bool bPlayerParticleJumpActive = player->getParticleAfterJump()->isActive();
            bool bCrashWithParticle = distanceParticle<50*iPlayerJumpCnt && bPlayerParticleJumpActive;
            bool bCrash = bCrashWithPlayer || bCrashWithParticle;
            
            bool bActionNotRun = getActionByTag((int)eAction::DEAD)==NULL;
            if(bCrash & bActionNotRun & !bPlayerIsJumping)
            {
                //if(bPlayerIsAfertJump)
                 {
                    _pSprite->setColor(Color3B(CRandom::getInstnace()->Random(155)+100,CRandom::getInstnace()->Random(155)+100 , 255));
                    addDamage(player);
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
                        switch(_eState)
                        {
                            case state::EGG:
                                player->heal(20);
                                break;
                            default:
                                break;
                        }
                        CGameManager::getInstance()->getNextTargetNode()->catchChicken(this);
                        CGameManager::getInstance()->getPlayerNode()->getModel()->addScoreWithChicken(this);

                        setMovement(Vec2::ZERO);
                        unscheduleUpdate();
                        getProgressTimer1()->getParent()->setVisible(false);
                        std::string str;
                        str+=textUtil::addCommaText(CGameManager::getInstance()->getPlayerNode()->getModel()->getScoreWithChicken(this));
                        str+=" : ";
                        str+=textUtil::addCommaText(CGameManager::getInstance()->getNextTargetNode()->getCombo());
                        getLabel()->setString(str);
                        getLabel()->setVisible(true);
                        getLabel()->setOpacity(0);
                        
                        getLabel()->runAction
                        (Sequence::create
                         (FadeIn::create(0.5f),
                          EaseElasticInOut::create(MoveBy::create(3.0f, Vec2(0,500)), 0.5f),
                          Spawn::create
                          (FadeOut::create(2.0f),
                           ScaleTo::create(2.0f, 3.0f),
                           NULL),
                          CallFunc::create(CC_CALLBACK_0(CChikenNode::dead, this)),
                          NULL
                          ));
                        getSpriteAttribute()->setVisible(false);
                        
                        auto action =Sequence::create
                        (EaseExponentialInOut::create(ScaleTo::create(0.5f, 1.5f, 0.5f)),
                         EaseExponentialInOut::create(ScaleTo::create(0.5f, 1.0f)),
                         Spawn::create
                         (RotateBy::create(1.0f, 180),
                          EaseExponentialInOut::create(MoveBy::create(1.0f, Vec2(0.0f,400.0f))),
                          NULL),
                         Spawn::create
                         (EaseExponentialInOut::create(ScaleTo::create(0.5f, 2.0f)),
                          FadeOut::create(0.5f),
                          NULL)
                         , NULL);
                        getSprite()->runAction(action);
                        player->setAttribute(getAttribute());
                        getLabelLevel()->setVisible(false);
                        player->addExp(getExp());
                        return;
                        
                        
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
                CUtil::sTMXcrashTestValue value = CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getGameField(), "meta", "wall", prePos, getMovement());
                
                if(value._pCrashTile!=NULL && !value._pCrashTile->getActionByTag(123))
                {
                    auto action =Sequence::create(FadeTo::create(0.5f,100),FadeTo::create(2.0f,255), NULL);
                    action->setTag(123);
                    
                    value._pCrashTile->runAction(action);
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
  
    //상태에 따라서 타이머 리셋
    {
        getTimer()->start();
        int iTime = 10, iTimeVal = 10;
        switch(_eState)
        {
            case state::EGG:
                iTime = 5;
                iTimeVal = 20;
                break;
            case state::CHICK:
                iTime = 5;
                iTimeVal = 3;
                break;
            case state::COCK:
                iTime = 3;
                iTimeVal = 5;
                break;
            case state::HEN:
                iTime = 2;
                iTimeVal = 3;
                break;
            default:
                break;
        }
        getTimer()->setMaxTime(CRandom::getInstnace()->Random(iTimeVal)+iTime);
    }
    
    int iRnd = CRandom::getInstnace()->Random(100);
    switch (_eState)
    {
        case state::EGG:
        {
            if(iRnd<40)
            {
                setState(state::EGG_BROKEN);
            }
            else
            {
                setState(state::CHICK);
            }
        }break;
        case state::CHICK:
        {
            if(iRnd<30)
            {
                setState(state::CHICK_DEAD);
            }
            else if(iRnd<80)
            {
                setState(state::HEN);
            }
            else
            {
                setState(state::COCK);
                getTimer()->setMaxTime(2);
            }
        }break;
        case state::CHICK_DEAD:
        case state::EGG_BROKEN:
        case state::DDONG:
        {
            getTimer()->pause();
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
            if(CRandom::getInstnace()->Random(2)==0)
            {
                ddongSSagi();
            }
            else
            {
                shot(5);
            }
        }break;
        case state::COCK:
        {
            if(CRandom::getInstnace()->Random(10)==0)
            {
                ddongSSagi();
            }
            else
            {
                shot(5);
            }
        }break;
        default:
            break;
    }
    addExp(10);
    
    resetTimer();
    
}
void CChikenNode::ddongSSagi()
{
    auto ddong = CChikenNode::create();
    ddong->setState(state::DDONG);
    getParent()->addChild(ddong);
    ddong->setPosition(getPosition());
    runAction(JumpBy::create(0.3f, Vec2::ZERO, 100, 1));
}

void CChikenNode::setState(CChikenNode::state eState)
{
    if(_eState==eState)
    {
        return;
    }
    _eState = eState;
    //상태에 맞게 그림 고치기
    {
        std::string frameName = "unit/";
        switch (_eState)
        {
            case state::EGG:
                frameName+="egg.png";
                setHPmax(10);
                break;
            case state::EGG_BROKEN:
                frameName+="eggBroken.png";
                setHPmax(1);
                break;
            case state::CHICK:
                frameName+="chick.png";
                setHPmax(15);
                break;
            case state::CHICK_DEAD:
                frameName+="chickDead.png";
                setHPmax(1);
                break;
            case state::COCK:
                frameName+="cock.png";
                setHPmax(25);
                break;
            case state::HEN:
                frameName+="hen.png";
                setHPmax(50);
                break;
            case state::DDONG:
                frameName+="ddong.png";
            default:
                break;
        }
        getSprite()->setSpriteFrame(frameName);
        
    }
}

void CChikenNode::shot(int shotLength)
{
    SimpleAudioEngine::getInstance()->playEffect("effect/roosterCrow.mp3");
    float f =CRandom::getInstnace()->Random(100)*0.01f;
    for(float i=0; i<shotLength; i++)
    {
        auto bullet = CBulletNode::create();
        bullet->setMovement(Vec2(sinf(i*f),cosf(i*f)));
        bullet->setPosition(getPosition());
        int tag = (int)CUtil::unitTag::UNIT_BULLET;
        CGameManager::getInstance()->getGameField()->addChild(bullet,tag,tag);
        bullet->setAttribute(getAttribute());
        bullet->setSpeedAcc(1.0f+((CRandom::getInstnace()->Random(100)*0.0001f)));
    }
    getSprite()->runAction(JumpBy::create(0.3f, Vec2::ZERO, 100, 1));
    
}

void CChikenNode::dead()
{
    removeFromParentAndCleanup(true);
}

void CChikenNode::resetTimer()
{
    switch(_eState)
    {
        case state::EGG_BROKEN:
        case state::CHICK_DEAD:
            return;
        default:
            break;
    }
    if(getParent()==NULL)
    {
        return;
    }
    if(getReferenceCount()==0 || getLabel()==NULL)
    {
        return;
    }
    int time = CRandom::getInstnace()->Random(10)+10;
    time*=1000;
    getTimer()->setMaxTime(time);
    getTimer()->start();
}