//
//  CTimer.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CTimer.h"
#include "CUtil.h"

CTimer::CTimer():
_lStartTime(0),
_lPauseTime(0),
_iMaxTime(0)
{
    
}
CTimer::~CTimer()
{
    
}
bool CTimer::init()
{
    return true;
}


void CTimer::start()
{
    _lStartTime = timeUtil::millisecondNow();
    
}

void CTimer::switchTimmer()
{
    if(isPause())
    {
        resume();
    }
    else
    {
        pause();
    }
}

void CTimer::pause()
{
    _lPauseTime = timeUtil::millisecondNow();
}

void CTimer::resume()
{
    long lTIme = _lPauseTime-_lStartTime;
    _lPauseTime = 0;
    _lStartTime+=lTIme;
}

bool CTimer::isPause()
{
    return _lPauseTime>0;
}
bool CTimer::isStart()
{
    return _lStartTime>0;
}

int CTimer::getTime()
{
    //타이머 시작 안했으면
    if (_lStartTime==0)
    {
        return _iMaxTime;
    }
    
    int time;
    //타이머 멈춰있으면 멈춘 시간 리턴
    if(_lPauseTime>0)
    {
        time = _lPauseTime-_lStartTime;
    }
    else
    {
        time = timeUtil::millisecondNow()-_lStartTime;
    }
    //maxTime설정되어있으면 남은시간 보여주기
    if(_iMaxTime>0)
    {
        int t =_iMaxTime-time;
        if(t<0)
        {
            t = 0;
        }
        return t;
    }
    //아니면 흘러간 시간 리턴.
    return time;
}


