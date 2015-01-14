//
//  CUnitNode.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 8..
//
//

#ifndef __dackjabara__CUnitNode__
#define __dackjabara__CUnitNode__

#include <stdio.h>
#include "CUtil.h"
#include "CTimer.h"

class CUnitNode : public Node
{
public:
    CUnitNode();
    virtual ~CUnitNode();
    virtual bool init();
    virtual void pause();
    virtual void resume();
    
    void addDamage(int iDamage);
    int getHP();
    
protected:
    virtual void update(float dt);
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer1, ProgressTimer1);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer2, ProgressTimer2);

    CC_SYNTHESIZE(int, _iHPmax, HPmax);
    int _iDamage;
    
    CC_SYNTHESIZE(int, _iAttack, Attack);
    
};

#endif /* defined(__dackjabara__CUnitNode__) */
