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

void CPlayerCharacterModel::chargeEnergy(int charge)
{
    if(_iEnergyUse==0)
    {
        return;
    }
    _iEnergyUse-=charge;
    if(_iEnergyUse<0)
    {
        _iEnergyUse = 0;
    }
}

float CPlayerCharacterModel::getEnergyPercent()
{
    float result = (float)(_iEnergyMax-_iEnergyUse)/(float)_iEnergyMax;
    return result;
}



CPlayerCharacterNode::CPlayerCharacterNode(void) :
_pParticle(NULL),
_iJumpCount(0),
_iDashSpeed(1),
_pCamera(NULL)
{
    
    
}
CPlayerCharacterNode::~CPlayerCharacterNode(void)
{
    CC_SAFE_RELEASE_NULL(_pParticle);
    CC_SAFE_RELEASE_NULL(_pCamera);
}

bool CPlayerCharacterNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 1, 2, "player_stand",0.2f,true);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 3, 4, "player_down",0.1f,false);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 4, 2, "player_up",0.1f,true);

    setHPmax(500);
    setAttack(10);
    auto sprite = getSprite();
    sprite->setSpriteFrame("unit/c1_01.png");
    sprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    sprite->setPosition3D(Vec3(0.0f,0.0f,0.0f));
    sprite->setPosition(Vec2(sprite->getContentSize().width/2,0));
    setContentSize(sprite->getContentSize());
    setAnchorPoint(sprite->getAnchorPoint());
    
    
    setParticle(ParticleSystemQuad::create("particle/p02.plist"));
    //_pParticle->setPosition3D(Vec3(0,0,-100));
    _pParticle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);
    _pParticle->setPosition(this->getPosition());
    _pParticle->setPosition3D(Vec3(200,100,0));
    _pParticle->setScale(0.5f);

    scheduleUpdate();
    standAction();
    _cModel.reset();
    
    Size winsize = Director::getInstance()->getWinSize();
    setCamera(Camera::createPerspective(50, winsize.width/winsize.height, 1, 3800));
    
    _pCamera->setRotation3D(Vec3(-10,0,0));
    _pCamera->setPosition3D(Vec3(getContentSize().width/2,winsize.height/3,winsize.height*0.7f));
    _pCamera->setCameraFlag(CameraFlag::DEFAULT);
    addChild(_pCamera);
    
 
    

    getProgressTimer1()->getParent()->setPosition(Vec2(58,240));

    

    return true;
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
void CPlayerCharacterNode::jumpAction()
{
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
        _iJumpCount++;
        return;
    }
    if(_iJumpCount>=2)
    {
        return;
    }
    bool useEnergy = _cModel.useEnergy(100);
    bool lowEnergy = _cModel.getEnergyPercent()<0.3f;
    if(!useEnergy | lowEnergy)
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
     aniList[0],
     aniList[1],
     CallFunc::create(CC_CALLBACK_0(CPlayerCharacterNode::standAction, this)),
     NULL);
    action->setTag((int)actionTag::JUMP);
    
    sprite->runAction(action);
    _pCamera->runAction(JumpBy::create(1.0f, Vec2(0, 0), 50, 1));
    
}
void CPlayerCharacterNode::dashAction()
{
    auto _pSprite = getSprite();
    if(_pSprite->getActionByTag((int)actionTag::DASH))
    {
        return;
    }
    
    Vec2 movement = CGameManager::getInstance()->getTouchMovement();
    if(movement.length()==0 || _cModel.getEnergyPercent()<0.3f)
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
void CPlayerCharacterNode::update(float dt)
{
    CUnitNode::update(dt);
    updateMovement(dt);
    
    //프로그레스바 갱신
    {
        float ff = _cModel.getEnergyPercent();
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
    
    Size winsize = Director::getInstance()->getWinSize();
    Size mapSize = CGameManager::getInstance()->getTileMap()->getContentSize();
    Vec2 movement = CGameManager::getInstance()->getTouchMovement()*_iDashSpeed;
    Vec2 prePos = pos+movement;
    float fPadding = 30.0f;
    const bool bROUT_TOP = prePos.y>mapSize.height/2-fPadding;
    const bool bROUT_BOTTOM = prePos.y<-mapSize.height/2+fPadding;
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
        CUtil::sTMXcrashTestValue value =CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getTileMap(), "bg", "wall", testpos);
        if(value._bCrash)
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
        
        value._pCrashTile->runAction(Sequence::create(FadeTo::create(0.5f,100),FadeTo::create(2.0f,255), NULL));
        
        if(CUtil::isCrashWithTMXTileMapSetting(CGameManager::getInstance()->getTileMap(), "bg", "charge", this)._bCrash)
        {
            _iChargeSpeed = 30;
        }
        else
        {
            _iChargeSpeed = 10;
        }
        
    }
    

    //에너지 소모 
    int energy = (int)movement.getLength();
    if(energy==0)
    {
        return;
    }
    
    if(energy<200 && _cModel.useEnergy(energy) )
    {
        //케릭터 이동
        this->setPosition(this->getPosition()+movement);
        //배경 스크롤
        //getParent()->setPositionX(getParent()->getPositionX()-movement.x);
        
        //파티클 이동
        if(_pParticle->getParent()==NULL)
        {
            getParent()->addChild(_pParticle);
        }
        _pParticle->setPosition(getPosition());
    }


}

void CPlayerCharacterNode::chargeEnergy(float dt)
{
    auto _pSprite = getSprite();

    Vec2 movement = CGameManager::getInstance()->getTouchMovement();
    if(movement.getLength()>0 || _pSprite->getActionByTag((int)actionTag::JUMP))
    {
        return;
    }
    _cModel.chargeEnergy(_iChargeSpeed);
    
    
}


