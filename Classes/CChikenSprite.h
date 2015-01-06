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
class CChikenSprite : public Sprite
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
    
protected:
    virtual void update(float dt);
    CChikenSprite();
    ~CChikenSprite();
    CC_SYNTHESIZE_READONLY(state, _eState, State);
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    
    virtual void pause();
    virtual void resume();
    
    
};

#endif /* defined(__dackjabara__CChikenSprite__) */
