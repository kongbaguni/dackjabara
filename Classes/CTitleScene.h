//
//  CTitleScene.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CTitleScene__
#define __shootinggamePrototype__CTitleScene__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class CTitleScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CTitleScene);
private:
    void changeScene(float dt);
};

#endif /* defined(__shootinggamePrototype__CTitleScene__) */
