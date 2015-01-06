//
//  CMainTimerNode.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#ifndef __dackjabara__CMainTimerNode__
#define __dackjabara__CMainTimerNode__

#include <stdio.h>
#include "CUtil.h"
#include "CTimer.h"
class CMainTimerNode : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(CMainTimerNode);
protected:
    CMainTimerNode();
    virtual ~CMainTimerNode();
    
    virtual void update(float dt);
    
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
};

#endif /* defined(__dackjabara__CMainTimerNode__) */
