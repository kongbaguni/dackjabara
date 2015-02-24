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
#include "CAvatarUnitNode.h"
class CChikenNode : public CAvatarUnitNode
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
        DDONG,
        STATE_MAX
    };
    enum class eAction
    {
        DEAD,
    };
    void setState(state eState);
    
protected:
    virtual void update(float dt);
    CChikenNode();
    ~CChikenNode();
    CC_SYNTHESIZE_READONLY(state, _eState, State);
    void resetTimer();
    
    void dead();
    virtual void onEnter();
    
    void shot(int shotLength);
    void ddongSSagi();
};

#endif /* defined(__dackjabara__CChikenNode__) */
