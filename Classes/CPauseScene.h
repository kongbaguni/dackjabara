//
//  CPauseScene.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 11..
//
//

#ifndef __dackjabara__CPauseScene__
#define __dackjabara__CPauseScene__

#include <stdio.h>
#include "CUtil.h"
class CPauseScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CPauseScene);
protected:
    void menuCallback(Ref* sender);
};
#endif /* defined(__dackjabara__CPauseScene__) */
