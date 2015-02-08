//
//  CPlayerCharacterNode.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CPlayerCharacterNode__
#define __shootinggamePrototype__CPlayerCharacterNode__

#include <stdio.h>
#include "cocos2d.h"
#include "CAvatarUnitNode.h"
#include "CPlayerCharacterModel.h"
USING_NS_CC;


class CPlayerCharacterNode : public CAvatarUnitNode
{
public:
    enum class actionTag
    {
        STAND,
        JUMP,
        DASH,
        ACTION_MAX
    };
    
    virtual bool init();
    
    CREATE_FUNC(CPlayerCharacterNode);
    void standAction();
    void jumpAction();
    void jumpActionWithEnergyUse(int iEnergy);
    void dashAction();
    
    void reset();
protected:
    CPlayerCharacterNode(void);
    virtual ~CPlayerCharacterNode(void);
    virtual void update(float dt);
    
    
    void updateMovement(float dt);
    void chargeEnergy(float dt);
    
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticle, Particle);
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticleAfterJump, ParticleAfterJump);
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticlePitan, ParticlePitan);
    
    CC_SYNTHESIZE_READONLY(long,_lJumpStartTime,JumpStartTime);
    CC_SYNTHESIZE_READONLY(int, _iJumpCount, JumpCount);
    CC_SYNTHESIZE_READONLY(int, _iDashSpeed, DashSpeed);
    CC_SYNTHESIZE_RETAIN(CPlayerCharacterModel*, _pModel, Model);
    CC_SYNTHESIZE_READONLY(int, _iChargeSpeed, ChargeSpeed);
    CC_SYNTHESIZE_RETAIN(Camera*, _pCamera, Camera);
    virtual void pause();
    virtual void resume();
    virtual void onEnter();
    virtual void onExit();
    
    int _iMoveingSoundId;
    void dead();
    
    void jumpAfterParticle();
    virtual bool addDamage(CUnitNode* node);
 
};


#endif /* defined(__shootinggamePrototype__CPlayerCharacterNode__) */
