//
//  CBulletNode.h
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 2..
//
//

#ifndef __dackjabara__CBulletNode__
#define __dackjabara__CBulletNode__

#include <stdio.h>
#include "cocos2d.h"
#include "CUnitNode.h"
USING_NS_CC;

class CBulletNode : public CUnitNode
{
public:
    CBulletNode();
    ~CBulletNode();
    virtual bool init();
    CREATE_FUNC(CBulletNode);
protected:
    virtual void onEnter();
    virtual void update(float dt);
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticle, Particle);
    
    CC_SYNTHESIZE(float, _fSpeedAcc, SpeedAcc);
};

#endif /* defined(__dackjabara__CBulletNode__) */
