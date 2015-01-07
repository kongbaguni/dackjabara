//
//  CPlayerNode.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CPlayerNode__
#define __shootinggamePrototype__CPlayerNode__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class CPlayerModel
{
public:
    CPlayerModel();
    ~CPlayerModel();
    void reset();
    
    bool useEnergy(int useValue);
    void chargeEnergy(int charge);
    float getEnergyPercent();
    
protected:
    CC_SYNTHESIZE(int, _iEnergyMax, EnergyMax);
    CC_SYNTHESIZE_READONLY(int, _iEnergyUse, EnergyUse);

};

class CPlayerNode : public Sprite
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
    
    CREATE_FUNC(CPlayerNode);
    void standAction();
    void jumpAction();
    void dashAction();
protected:
    CPlayerNode(void);
    virtual ~CPlayerNode(void);
    virtual void update(float dt);
    
    void updateMovement(float dt);
    void chargeEnergy(float dt);
    
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticle, Particle);
    CC_SYNTHESIZE_READONLY(int, _iJumpCount, JumpCount);
    CC_SYNTHESIZE_READONLY(int, _iDashSpeed, DashSpeed);
    CC_SYNTHESIZE(CPlayerModel, _cModel, Model);
    CC_SYNTHESIZE_READONLY(int, _iChargeSpeed, ChargeSpeed);
    CC_SYNTHESIZE_RETAIN(Camera*, _pCamera, Camera);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer, ProgressTImer);
    
    virtual void pause();
    virtual void resume();
 
};


#endif /* defined(__shootinggamePrototype__CPlayerNode__) */
