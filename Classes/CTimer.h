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
    
    /** 타이머 시작*/
    void start();
    /** 타이머 잠시 멈춤*/
    void pause();
    /** 타이머 완전 멈춤*/
    void stop();
    
    /** 타이머 다시 시작*/
    void resume();
    /** 타이머 멈췄냐?*/
    bool isPause();
    /** 타이머 작동중이냐?*/
    bool isStart();
    /** 흘러간 시간 구하기. MaxTime설정되어있으면 discount */
    int getTime();
    
    /** 타이머가 가는중이면 멈추고 멈춰있으면 시작하고...*/
    void switchTimmer();
    
    /** MaxTime설정되어있을 경우 MaxTime이 몇번 소모된만큼 시간이 흘렀는지 측정 MaxTime이 설정되어있지 않으면 0.*/
    void getTimes(int& times, int& time);
    
    std::string getTimeString();
    
protected:
    CC_SYNTHESIZE(int, _iMaxTime, MaxTime);
    /**타이머 시작한 시각*/
    long _lStartTime;
    /**타이머 멈춘 시각*/
    long _lPauseTime;
    
};


#endif /* defined(__dackjabara__CTimer__) */
