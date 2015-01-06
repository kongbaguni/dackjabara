//
//  CTimer.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#ifndef __dackjabara__CTimer__
#define __dackjabara__CTimer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class CTimer : public Ref
{

public:
    CTimer();
    ~CTimer();
    virtual bool init();
    CREATE_FUNC(CTimer);
    
    void start();
    void pause();
    void resume();
    bool isPause();
    bool isStart();
    int getTime();
    void switchTimmer();
    
    std::string getTimeString();
    
protected:
    CC_SYNTHESIZE(int, _iMaxTime, MaxTime);
    long _lStartTime;
    long _lPauseTime;
};
#endif /* defined(__dackjabara__CTimer__) */
