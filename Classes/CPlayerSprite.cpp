//
//  CPlayerSprite.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CPlayerSprite.h"
#include "CAnimationHelper.h"
#include "CUtil.h"
#include "CGameManager.h"

CPlayerSprite::CPlayerSprite(void) :
_pSprite(NULL),
_pLabel(NULL),
_pParticle(NULL)
{
    
    
}
CPlayerSprite::~CPlayerSprite(void)
{
    CC_SAFE_RELEASE_NULL(_pSprite);
    CC_SAFE_RELEASE_NULL(_pLabel);
    CC_SAFE_RELEASE_NULL(_pParticle);
}

bool CPlayerSprite::init()
{
    if(!Node::init())
    {
        return false;
    }
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 1, 2, "player_stand",0.2f,true);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 3, 4, "player_down",0.1f,true);
    CAnimationHelper::addAnimation("unit/c1_%02d.png", 4, 2, "player_up",0.1f,true);

    setSprite(Sprite::createWithSpriteFrameName("unit/c1_01.png"));
    _pSprite->setAnchorPoint(Vec2(0.5f, 0.0f));
    _pSprite->setPosition3D(Vec3(0.0f,0.0f,5.0f));

    addChild(_pSprite);
    setLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "0 : 0"));
    addChild(_pLabel);
    _pLabel->setScale(0.5f);
    
    setParticle(ParticleSystemQuad::create("particle/p02.plist"));
    //_pParticle->setPosition3D(Vec3(0,0,-100));
    _pParticle->setPositionType(cocos2d::ParticleSystem::PositionType::RELATIVE);
    _pParticle->setPosition(this->getPosition());

    scheduleUpdate();
    standAction();
    setRotation3D(CUtil::getRotate3D());
    return true;
}



void CPlayerSprite::standAction()
{
    auto action =_pSprite->getActionByTag((int)actionTag::STAND);
    if(action && !action->isDone())
    {
        return;
    }
    auto animation = AnimationCache::getInstance()->getAnimation("player_stand");
    auto ani = RepeatForever::create(Animate::create(animation));
    auto jump = RepeatForever::create(CCSequence::create(MoveTo::create(1.0f, Vec2(0.0f, 10.0f)),MoveTo::create(1.0f, Vec2(0.0f, 0.0f)), NULL));
    
    ani->setTag((int)actionTag::STAND);
    _pSprite->runAction(ani);
    _pSprite->runAction(jump);
    _iJumpCount = 0;
}
void CPlayerSprite::jumpAction()
{
    if(_pSprite->getActionByTag((int)actionTag::JUMP) &&
       (_pSprite->getPositionY()<80 || _pSprite->getPositionY()>110)
       )
    {
        _iJumpCount++;
        return;
    }
    if(_iJumpCount>=2)
    {
        return;
    }
    _iJumpCount++;
    _pSprite->stopAllActions();
    
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
      JumpTo::create(1.0f, Vec2(0.0f, 0.0f), 100.0f, 1),
      NULL
      ),
     aniList[0],
     aniList[1],
     CallFunc::create(CC_CALLBACK_0(CPlayerSprite::standAction, this)),
     NULL);
    action->setTag((int)actionTag::JUMP);
    
    _pSprite->runAction(action);
    
}

void CPlayerSprite::update(float dt)
{
    if(CGameManager::getInstance()->getParent()==NULL)
    {
        return;
    }
    Vec2 pos = getPosition();
    _pLabel->setString(String::createWithFormat("%0.2f : %0.2f",pos.x, pos.y)->_string);
    
    Size winsize = Director::getInstance()->getWinSize();
    Size mapSize = CGameManager::getInstance()->getTileMap()->getContentSize();
    Vec2 movement = CGameManager::getInstance()->getTouchMovement();
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
    if(movement!=Vec2(0,0))
    {
        auto tileMap = CGameManager::getInstance()->getTileMap();
        Vec2 fixPos = CUtil::getCoordWithVec2(tileMap, prePos);
        
        TMXLayer* layer = CGameManager::getInstance()->getTileMap()->getLayer("bg");
        
        uint32_t iGid = layer->getTileGIDAt(fixPos);
        auto value = tileMap->getPropertiesForGID(iGid);
        if(value.getType()==Value::Type::MAP)
        {
            ValueMap valueMap = value.asValueMap();
            std::string key = "wall";
            ValueMap::const_iterator w = valueMap.find(key);
            if(w!=valueMap.end())
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
        }

        Vec2 fixPosNow = CUtil::getCoordWithVec2(tileMap, getPosition());
        auto tile = layer->getTileAt(fixPosNow);
        tile->runAction
        (Sequence::create
         (FadeTo::create(0.5f, 30),
          FadeTo::create(0.5f, 255),
          NULL)
         );
        
        auto tile2 = layer->getTileAt(fixPos);
        tile2->runAction
        (Sequence::create
         (ScaleTo::create(0.5f, 0.1f),
          ScaleTo::create(0.5f, 1.0f),
          NULL)
         );
        
    }
    


    //케릭터 이동
    this->setPosition(this->getPosition()+movement);
    //배경 스크롤
    getParent()->setPositionX(getParent()->getPositionX()-movement.x);

    //파티클 이동
    if(_pParticle->getParent()==NULL)
    {
        getParent()->addChild(_pParticle);
    }
    _pParticle->setPosition(getPosition());
    
    
}

