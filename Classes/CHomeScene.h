//
//  CHomeScene.h
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 4..
//
//

#ifndef __dackjabara__CHomeScene__
#define __dackjabara__CHomeScene__

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;
class CHomeScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CHomeScene);
protected:
    CHomeScene();
    ~CHomeScene();
};
#endif /* defined(__dackjabara__CHomeScene__) */
