//
//  CChikenSprite.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#ifndef __dackjabara__CChikenSprite__
#define __dackjabara__CChikenSprite__

#include <stdio.h>
#include "CUtil.h"
#include "CTimer.h"
#include "CUnitNode.h"
class CChikenSprite : public CUnitNode
{
public:
    virtual bool init();
    CREATE_FUNC(CChikenSprite);
    
    enum class state
    {
        EGG,
        EGG_BROKEN,
        CHICK,
        CHICK_DEAD,
        HEN,
        COCK,
    };
    enum class eAction
    {
        DEAD,
    };
    
protected:
    virtual void update(float dt);
    CChikenSprite();
    ~CChikenSprite();
    CC_SYNTHESIZE_READONLY(state, _eState, State);
    CC_SYNTHESIZE_READONLY(Vec2, _vec2Movement, Movement);
    void resetTimer();
    
    void dead();
    
};

#endif /* defined(__dackjabara__CChikenSprite__) */
