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
protected:
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer, ProgressTImer);


    
};

#endif /* defined(__dackjabara__CUnitNode__) */
