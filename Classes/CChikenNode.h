//
//  CChikenNode.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#ifndef __dackjabara__CChikenNode__
#define __dackjabara__CChikenNode__

#include <stdio.h>
#include "CUtil.h"
#include "CTimer.h"
#include "CUnitNode.h"
class CChikenNode : public CUnitNode
{
public:
    virtual bool init();
    CREATE_FUNC(CChikenNode);
    
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
    CChikenNode();
    ~CChikenNode();
    CC_SYNTHESIZE_READONLY(state, _eState, State);
    CC_SYNTHESIZE_READONLY(Vec2, _vec2Movement, Movement);
    void resetTimer();
    
    void dead();
    
};

#endif /* defined(__dackjabara__CChikenNode__) */