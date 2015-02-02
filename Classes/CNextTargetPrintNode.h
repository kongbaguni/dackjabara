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
    void changePictureWithNextState();
    virtual void onEnter();
};

#endif /* defined(__dackjabara__CNextTargetPrintNode__) */
