//
//  CGameScene.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CGameScene__
#define __shootinggamePrototype__CGameScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class CGameScene : public Scene
{
public:
    CGameScene();
    ~CGameScene();
    virtual bool init();
    CREATE_FUNC(CGameScene);
    virtual void onEnter();
    virtual void onExit();
protected:
    void makePlayer();
};

#endif /* defined(__shootinggamePrototype__CGameScene__) */
