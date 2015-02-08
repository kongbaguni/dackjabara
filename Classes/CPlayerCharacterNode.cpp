//
//  CPlayerCharacterNode.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CPlayerCharacterNode.h"
#include "CAnimationHelper.h"
#include "CUtil.h"
#include "CGameManager.h"
#include "CControllerLayer.h"

CPlayerCharacterNode::CPlayerCharacterNode(void) :
_pParticle(NULL),
_iJumpCount(0),
_iDashSpeed(1),
_pCamera(NULL),
_lJumpStartTime(0),
_pModel(NULL),
_pParticleAfterJump(NULL),
_pParticlePitan(NULL),
_iMoveingSoundId(0)
{
    setModel(CPlayerCharacterModel::create());
    
    
}
CPlayerCharacterNode::~CPlayerCharacterNode(void)
{
    CC_SAFE_RELEASE_NULL(_pParticle);
    CC_SAFE_RELEASE_NULL(_pCamera);
    CC_SAFE_RELEASE_NULL(_pModel);
    CC_SAFE_RELEASE_NULL(_pParticleAfterJump);
    CC_SAFE_RELEASE_NULL(_pParticlePitan);
}

bool CPlayerCharacterNode::init()
{
    if(!CAvatarUnitNode::init())
    {
        return false;
    }
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 1, 2, "player_stand",0.2f,true);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 3, 4, "player_down",0.1f,false);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 4, 2, "player_up",0.1f,true);
    static bool bPreload = false;
    if(!bPreload)
    {
        SimpleAudioEngine::getInstance()->preloadEffect("effect/jump.mp3");
        SimpleAudioEngine::getInstance()->preloadEffect("effect/bowFire.mp3");
        SimpleAudioEngine::getInstance()->preloadEffect("effect/punch.mp3");
        SimpleAudioEngine::getInstance()->preloadEffect("effect/powerFailure.mp3");
        SimpleAudioEngine::getInstance()->preloadEffect("effect/sciFiRobot.mp3");
        bPreload = true;
    }
    
    setHPmax(500);
    setAttack(10);
    auto sprite = getSprite();
    sprite->setSpriteFrame("unit/c1_01.png");
    sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    sprite->setPosition3D(Vec3(0.0f,0.0f,0.0f));
    sprite->setPosition(Vec2(sprite->getContentSize().width/2,0));
    sprite->setScale(0.5f);
    setContentSize(sprite->getContentSize());
    setAnchorPoint(sprite->getAnchorPoint());
    
    
    setParticle(ParticleSystemQuad::create("particle/p02.plist"));
    //_pParticle->setPosition3D(Vec3(0,0,-100));
    _pParticle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);
    _pParticle->setPosition(this->getPosition());
    _pParticle->setPosition3D(Vec3(200,100,0));
    _pParticle->setScale(0.5f);
    
    setParticleAfterJump(ParticleSystemQuad::create("particle/p03.plist"));
    _pParticleAfterJump->setPosition(Vec2::ZERO);
    _pParticleAfterJump->stopSystem();

    scheduleUpdate();
    standAction();
    
    Size winsize = Director::getInstance()->getWinSize();
    setCamera(Camera::createPerspective(50, winsize.width/winsize.height, 1, 3800));
    
    _pCamera->setRotation3D(Vec3(-10,0,0));
    _pCamera->setPosition3D(Vec3(getContentSize().width/2,winsize.height/3,winsize.height*0.7f));
    _pCamera->setCameraFlag(CameraFlag::DEFAULT);
    addChild(_pCamera);
 

    getProgressTimer1()->getParent()->setPosition(Vec2(58,240));
    
    setParticlePitan(ParticleSystemQuad::create("particle/p05.plist"));
    _pParticlePitan->setPosition(getPosition());
    _pParticlePitan->stopSystem();

    

    return true;
}
void CPlayerCharacterNode::onEnter()
{
    Node::onEnter();
    addChild(CControllerLayer::getInstance());
    Size winsize = Director::getInstance()->getWinSize();
    
    CControllerLayer::getInstance()->setPosition(-winsize.width*0.25f, -winsize.height/7);
    CControllerLayer::getInstance()->setScale(0.63);
    _pParticle->setPosition(getPosition());
    
}
void CPlayerCharacterNode::onExit()
{
    Node::onExit();
    removeChild(CControllerLayer::getInstance());
}



void CPlayerCharacterNode::standAction()
{
    auto sprite = getSprite();
    auto action =sprite->getActionByTag((int)actionTag::STAND);
    if(action && !action->isDone())
    {
        return;
    }
    sprite->stopAllActions();
    auto animation = AnimationCache::getInstance()->getAnimation("player_stand");
    auto ani = RepeatForever::create(Animate::create(animation));
    auto jump = RepeatForever::create(CCSequence::create(MoveBy::create(1.0f, Vec2(0.0f, 10.0f)),MoveBy::create(1.0f, Vec2(0.0f, -10.0f)), NULL));
    
    ani->setTag((int)actionTag::STAND);
    sprite->runAction(ani);
    sprite->runAction(jump);
    _iJumpCount = 0;
    _iDashSpeed = 1;
    if(getSprite()->getPositionY()>1)
    {
        getSprite()->runAction(MoveTo::create(1.0f, Vec2(sprite->getContentSize().width/2,0)));
    }
}

void CPlayerCharacterNode::reset()
{
    _pModel->reset();
    if(_pParticle->getParent()==NULL)
    {
        getParent()->addChild(_pParticle);
        _pParticle->resetSystem();
    }
    getSprite()->setOpacity(255);
    getSprite()->setRotation(0);
    heal(getHPmax());
    getProgressTimer1()->getParent()->setVisible(true);
    _pParticle->resetSystem();
    standAction();
}
void CPlayerCharacterNode::jumpAction()
{
    jumpActionWithEnergyUse(100);
}
void CPlayerCharacterNode::jumpActionWithEnergyUse(int iEnergy)
{
    if(!_pModel->useEnergy(iEnergy) ||
       _pModel->getState()==CPlayerCharacterModel::state::DEAD ||
       getHP()==0 ||
       CGameManager::getInstance()->getIsGameOver()
       )
    {
        return;
    }
    
    auto sprite = getSprite();
    Vec2 centerBottom = Vec2(getContentSize().width/2,0);
    if(CGameManager::getInstance()->getMainTimerNode()->getTimer()->isPause())
    {
        return;
    }
    
    if(sprite->getActionByTag((int)actionTag::JUMP) &&
       (sprite->getPositionY()<80 || sprite->getPositionY()>110)
       )
    {
        return;
    }
    if(_iJumpCount>=2)
    {
        return;
    }
    _iJumpCount++;
    sprite->stopAllActions();
    
    Animate* aniList[] =
    {
        Animate::create(AnimationCache::getInstance()->getAnimation("player_down")),
        Animate::create(AnimationCache::getInstance()->getAnimation("player_up")),
        Animate::create(AnimationCache::getInstance()->getAnimation("player_stand")),
    };
    auto action = Sequence::create
    (
     aniList[0],
     Spawn::create
     (aniList[1],
      JumpTo::create(1.0f, centerBottom, 100.0f, 1),
      NULL
      ),
     CallFunc::create(CC_CALLBACK_0(CPlayerCharacterNode::jumpAfterParticle, this)),
     aniList[0],
     aniList[1],
     CallFunc::create(CC_CALLBACK_0(CPlayerCharacterNode::standAction, this)),
     NULL);
    action->setTag((int)actionTag::JUMP);
    
    sprite->runAction(action);
    _pCamera->runAction(JumpBy::create(1.0f, Vec2(0, 0), 50, 1));
    _lJumpStartTime = timeUtil::millisecondNow();
    SimpleAudioEngine::getInstance()->playEffect("effect/jump.mp3");
    SimpleAudioEngine::getInstance()->pauseEffect(_iMoveingSoundId);

    
}
void CPlayerCharacterNode::dashAction()
{
    auto _pSprite = getSprite();
    if(_pSprite->getActionByTag((int)actionTag::DASH))
    {
        return;
    }
    
    Vec2 movement = CControllerLayer::getInstance()->getTouchMovement();
    if(movement.length()==0 || _pModel->getEnergyPercent()<0.3f)
    {
        return;
    }
    _iDashSpeed = 3;
    _pSprite->stopAllActions();
    auto action =
    Sequence::create
    (Animate::create(AnimationCache::getInstance()->getAnimation("player_down")),
     DelayTime::create(0.1f),
     Animate::create(AnimationCache::getInstance()->getAnimation("player_up")),

     CallFunc::create(CC_CALLBACK_0(CPlayerCharacterNode::standAction, this)),
     NULL);
    
    action->setTag((int)actionTag::DASH);
    _pSprite->runAction(action);
    
}
void CPlayerCharacterNode::dead()
{
    CGameManager::getInstance()->gameOver();
}
void CPlayerCharacterNode::update(float dt)
{
    CUnitNode::update(dt);
    
    //플레이어가 죽었다. 어떡해.... 행동불능 처리.
    if(_pModel->getState()==CPlayerCharacterModel::state::DEAD ||
       CGameManager::getInstance()->getIsGameOver()
       )
    {
        return;
    }
    
    if(getHP()==0)
    {
        SimpleAudioEngine::getInstance()->playEffect("effect/powerFailure.mp3");
        getProgressTimer1()->getParent()->setVisible(false);
        bool d = (bool)CRandom::getInstnace()->Random(1);
        float fd = d ? 90 : -90;
        getSprite()->stopAllActions();
        _pModel->setState(CPlayerCharacterModel::state::DEAD);
        _pParticle->stopSystem();
        getSprite()->runAction
        (Sequence::create
         (RotateTo::create(1.0f, fd, fd),
          FadeOut::create(1.0f),
          CallFunc::create(CC_CALLBACK_0(CPlayerCharacterNode::dead, this))
         , NULL))
        ;
        return;
    }
    
    
    updateMovement(dt);
    //플레이어가 점프하여 높이값이 바뀌면 카메라 스케일 업
    {
        
        Size winsize = Director::getInstance()->getWinSize();
        Vec3 pos =
        Vec3(getContentSize().width/2,winsize.height/3,winsize.height*0.7f);
        
        float fY = getSprite()->getPositionY()/2;
        if(fY<10)
        {
            fY = 0;
        }
        _pCamera->setPosition3D(Vec3(pos.x,pos.y,pos.z+fY));
    }
    
    //프로그레스바 갱신
    {
        float ff = _pModel->getEnergyPercent();
        _pParticle->setStartColor(Color4F(1.0f, ff, ff, ff/2+0.5f));
        _pParticle->setEndColor(Color4F(0.0f, 0.0f, 1.0f, ff));
        chargeEnergy(dt);
        float percent = ff*100.0f;
        if(percent>99)
        {
            percent = 99;
        }
        getProgressTimer1()->setPercentage(percent);
    }
    std::string txt;
    txt+=textUtil::addCommaText(getLocalZOrder());
    txt+=textUtil::addCommaText(_pParticle->getLocalZOrder());
    
    getLabel()->setString(txt);

}
void CPlayerCharacterNode::updateMovement(float dt)
{
    auto _pSprite = getSprite();
    if(CGameManager::getInstance()->getParent()==NULL)
    {
        return;
    }
    if(this->getActionByTag((int)actionTag::DASH))
    {
        return;
    }
    
    Vec2 pos = getPosition();
    
    static Vec2 oldMovement = Vec2::ZERO;
    static bool oldFlip = false;
    Size winsize = Director::getInstance()->getWinSize();
    Size mapSize = CGameManager::getInstance()->getGameField()->getContentSize();
    Vec2 movement = CControllerLayer::getInstance()->getTouchMovement()*_iDashSpeed;
    if((oldMovement==Vec2::ZERO && movement != Vec2::ZERO)
       || oldFlip != getSprite()->isFlippedX())
    {
        SimpleAudioEngine::getInstance()->stopEffect(_iMoveingSoundId);
        _iMoveingSoundId = SimpleAudioEngine::getInstance()->playEffect("effect/sciFiRobot.mp3");
    }
    if(movement==Vec2::ZERO && oldMovement != Vec2::ZERO)
    {
        SimpleAudioEngine::getInstance()->stopEffect(_iMoveingSoundId);
    }
    oldMovement = movement;
    oldFlip = getSprite()->isFlippedX();

    
    Vec2 prePos = pos+movement;
    float fPadding = 30.0f;
    const bool bROUT_TOP = prePos.y>mapSize.height-fPadding;
    const bool bROUT_BOTTOM = prePos.y<fPadding;
    const bool bROUT_LEFT = prePos.x<fPadding;
    const bool bROUT_RIGHT = prePos.x>mapSize.width-fPadding;
    if(bROUT_TOP | bROUT_BOTTOM)
    {
        movement.y*=-1;
    }
    else if(bROUT_LEFT | bROUT_RIGHT)
    {
        movement.x*=-1;
    }
    else if(movement.x<0)
    {
        _pSprite->setFlippedX(false);
    }
    else if(movement.x > 0)
    {
        _pSprite->setFlippedX(true);
    }
    
    //타일맵하고 충돌검사
    if(movement!=Vec2(0,0) && _pSprite->getPositionY()<40)
    {
        Vec2 testpos = getPosition();
        testpos.y+=40;
        testpos+=movement;
        bool bCharge =CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getGameField(), "meta", "charge", testpos,movement)._bCrash;
        CUtil::sTMXcrashTestValue value =CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getGameField(), "meta", "wall", testpos, movement);
        CUtil::sTMXcrashTestValue value2 =CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getGameField(), "height", "height", testpos, movement);
        
        
        
        if(bCharge)
        {
            _iChargeSpeed = 100;
        }
        else
        {
            _iChargeSpeed = 10;
        }
        if(!bCharge & value._bCrash)
        {
            if(fabsf(movement.x)>0)
            {
                movement.x = 0;
            }
            if(fabsf(movement.y)>0)
            {
                movement.y = 0;
            }
        }
        
        
        if(value._pCrashTile!=NULL && !value._pCrashTile->getActionByTag(123))
        {
            auto action =Sequence::create(FadeTo::create(0.5f,100),FadeTo::create(2.0f,255), NULL);
            action->setTag(123);
            value._pCrashTile->runAction(action);
        }
        
        
    }
    

    //에너지 소모 
    int energy = (int)movement.getLength();
    if(energy==0)
    {
        return;
    }
    
    if(energy<200 && _pModel->useEnergy(energy) )
    {
        //케릭터 이동
        this->setPosition(this->getPosition()+movement);
        //배경 스크롤
        //getParent()->setPositionX(getParent()->getPositionX()-movement.x);
        
        //파티클 이동
        if(_pParticle->getParent()==NULL)
        {
            getParent()->addChild(_pParticle, getLocalZOrder()+1);
        }
        if(_pParticleAfterJump->getParent()==NULL)
        {
            getParent()->addChild(_pParticleAfterJump,getLocalZOrder()-1);
        }
        if(_pParticlePitan->getParent()==NULL)
        {
            getParent()->addChild(_pParticlePitan,getLocalZOrder()-1);
        }
        _pParticle->setPosition(getPosition());
        _pParticle->setLocalZOrder(getLocalZOrder()+1);
        _pParticleAfterJump->setLocalZOrder(getLocalZOrder()-1);
        _pParticlePitan->setLocalZOrder(getLocalZOrder()-1);
    }
    else
    {
        CCLOG("!!");
    }


}

void CPlayerCharacterNode::chargeEnergy(float dt)
{
    auto _pSprite = getSprite();

    Vec2 movement = CControllerLayer::getInstance()->getTouchMovement();
    if(movement.getLength()>0 || _pSprite->getActionByTag((int)actionTag::JUMP))
    {
        return;
    }
    _pModel->chargeEnergy(_iChargeSpeed);
    
    
}


void CPlayerCharacterNode::pause()
{
    _pCamera->pause();
    CUnitNode::pause();
}

void CPlayerCharacterNode::resume()
{
    _pCamera->resume();
    CUnitNode::resume();
}

void CPlayerCharacterNode::jumpAfterParticle()
{
    SimpleAudioEngine::getInstance()->playEffect("effect/bowFire.mp3");
    
    SimpleAudioEngine::getInstance()->resumeEffect(_iMoveingSoundId);
    _pParticleAfterJump->setScale(_iJumpCount*0.5f);
    _pParticleAfterJump->setPosition(getPosition());
    _pParticleAfterJump->resetSystem();

}

bool CPlayerCharacterNode::addDamage(CUnitNode *node)
{
    if(!CAvatarUnitNode::addDamage(node))
    {
        return false;
    }
    _pParticlePitan->resetSystem();
    _pParticlePitan->setPosition(getPosition());
    SimpleAudioEngine::getInstance()->playEffect("effect/punch.mp3");
    return true;
}