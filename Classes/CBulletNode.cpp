//
//  CBulletNode.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 2..
//
//

#include "CBulletNode.h"
#include "CGameManager.h"
CBulletNode::CBulletNode():
_pParticle(NULL),
_fSpeedAcc(1.0f)
{
    
}
CBulletNode::~CBulletNode()
{
    CC_SAFE_RELEASE_NULL(_pParticle);
    
}
bool CBulletNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    setRotation3D(Vec3::ZERO);
    setParticle(ParticleSystemQuad::create("particle/p04_bullet.plist"));
    addChild(_pParticle);
    _pParticle->stopSystem();
    scheduleUpdate();
    setAttack(100);
    getProgressTimer1()->getParent()->setVisible(false);
    
    getSpriteAttribute()->removeFromParent();
    addChild(getSpriteAttribute());
    getSpriteAttribute()->runAction(RepeatForever::create(EaseExponentialInOut::create(RotateBy::create(2.0f, 720.0f))));
    

    return true;
}

void CBulletNode::onEnter()
{
    Node::onEnter();
    _pParticle->resetSystem();
}

void CBulletNode::update(float dt)
{
    setMovement(getMovement()*_fSpeedAcc);
    setPosition(getPosition()+getMovement());
    _pParticle->setLocalZOrder(getSprite()->getLocalZOrder());
    if(CGameManager::getInstance()->getIsGameOver())
    {
        removeFromParentAndCleanup(true);
        return;
    }
    
    //플레이어와 충돌검사
    auto player = CGameManager::getInstance()->getPlayerNode();
    bool bPlayerIsJump = player->getSprite()->getPositionY() > 10;
    Vec2 playerPos = CGameManager::getInstance()->getPlayerNode()->getPosition();
    float distP = getPosition().getDistance(playerPos);
    Size mapSize = CGameManager::getInstance()->getGameField()->getContentSize();
    bool outScreen = getPosition().x<0 || getPosition().y<0 || getPosition().x>mapSize.width || getPosition().y>mapSize.height;

    if(distP<20 && !bPlayerIsJump)
    {
        if(CGameManager::getInstance()->getPlayerNode()->addDamage(this))
        {
            removeFromParentAndCleanup(true);
        }
        return;
    }
    if(outScreen)
    {
        removeFromParentAndCleanup(true);
        return;
    }
    
}

