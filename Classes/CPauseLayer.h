//
//  CPauseLayer.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#ifndef __dackjabara__CPauseLayer__
#define __dackjabara__CPauseLayer__

#include <stdio.h>
#include "CUtil.h"

class CPauseLayer : public Layer
{
public:
    CREATE_FUNC(CPauseLayer);
    virtual bool init();
    
protected:
    enum class menuType
    {
        RESUME,
        EXIT
    };
    virtual void onEnter();
    virtual void onExit();
    CPauseLayer();
    virtual ~CPauseLayer();
    virtual void menuCallback(Ref* sender);
    
};

#endif /* defined(__dackjabara__CPauseLayer__) */
