//
//  CPlayerSprite.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CPlayerSprite__
#define __shootinggamePrototype__CPlayerSprite__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class CPlayerSprite : public Node
{
public:
    enum class actionTag
    {
        STAND,
        JUMP,
        ACTION_MAX
    };
    
    virtual bool init();
    
    CREATE_FUNC(CPlayerSprite);
    void standAction();
    void jumpAction();
protected:
    CPlayerSprite(void);
    virtual ~CPlayerSprite(void);
    virtual void update(float dt);
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
    CC_SYNTHESIZE_RETAIN(ParticleSystemQuad*, _pParticle, Particle);
    CC_SYNTHESIZE_READONLY(int, _iJumpCount, JumpCount);
};


#endif /* defined(__shootinggamePrototype__CPlayerSprite__) */
