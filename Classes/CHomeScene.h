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
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
class CHomeScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CHomeScene);
protected:
    enum class Tag
    {
        PLAYGAME,
        CARD_BBOBGI,
        EXITGAME,
        
        TAG_MAX
    };
    
    CHomeScene();
    ~CHomeScene();
    virtual void onEnter();
    CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, _pBox, Box);
    
    void callBack(Ref* pSender);
};
#endif /* defined(__dackjabara__CHomeScene__) */
