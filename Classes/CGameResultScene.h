//
//  CGameResultScene.h
//  dackjabara
//
//  Created by kongbaguni on 2015. 1. 30..
//
//

#ifndef __dackjabara__CGameResultScene__
#define __dackjabara__CGameResultScene__

#include <stdio.h>
#include "cocos2d.h"
#include "CLabelAnimate.h"

USING_NS_CC;
class CGameResultScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CGameResultScene);
protected:
    CC_SYNTHESIZE_RETAIN(Label*, _pLabelTotalScore, LabelTotalScore);
    CGameResultScene();
    virtual ~CGameResultScene();
    virtual void onEnter();
    void returnToTitle(float dt);
};

#endif /* defined(__dackjabara__CGameResultScene__) */
