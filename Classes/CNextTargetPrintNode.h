//
//  CNextTargetPrintNode.h
//  dackjabara
//
//  Created by kongbaguni on 2015. 1. 30..
//
//

#ifndef __dackjabara__CNextTargetPrintNode__
#define __dackjabara__CNextTargetPrintNode__

#include <stdio.h>
#include "cocos2d.h"
#include "CChikenNode.h"
#include "CTimer.h"
USING_NS_CC;
class CNextTargetPrintNode : public Node
{
public:
    virtual bool init();
    CREATE_FUNC(CNextTargetPrintNode);
    void catchChicken(CChikenNode* chicken);
    void reset();
protected:
    CNextTargetPrintNode();
    virtual ~CNextTargetPrintNode();
    CChikenNode::state _eNextTargetChickenState;
    CC_SYNTHESIZE_RETAIN(Sprite*, _pTargetChicken, TargetChicken);
    CC_SYNTHESIZE_READONLY(int, _iCombo, Combo);
    void changeNextTarget();
    void changePictureWithNextState();
    virtual void onEnter();
    virtual void update(float dt);
    virtual void pause();
    virtual void resume();
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer, ProgressTimer);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabelCombo, LabelCombo);

};

#endif /* defined(__dackjabara__CNextTargetPrintNode__) */
