//
//  CPlayerModel.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 9..
//
//

#include "CPlayerModel.h"
void CPlayerModel::CPlayerModel():
_iCredit(0),
_iRealUse(0),
_iRealMax(30)
{
    
}
void CPlayerModel::~CPlayerModel()
{
    
}

bool CPlayerModel::useCredit(int iCredit)
{
    if(_iCredit<iCredit)
    {
        return false;
    }
    
    iCredit-=iCredit;
    return true;
}

void CPlayerModel::addCredit(int iCredit)
{
    _iCredit+=iCredit;
}


bool CPlayerModel::useReal(int iReal)
{
    if(_iRealUse+iReal>_iRealMax)
    {
        return false;
    }
    _iRealUse+=iReal;
    return true;
}

void CPlayerModel::addReal(int iReal)
{
    addReal(iReal, false);
}
void CPlayerModel::addReal(int iReal, bool bUnLimit)
{
    _iRealUse-=iReal;
    
    if(_iRealUse<0 & !bUnLimit)
    {
        _iRealUse = 0;
    }
}

int CPlayerModel::getReal()
{
    if(!_pTimerRealCharge->isStart())
    {
        _pTimerRealCharge->start();
    }
   
    // 시간지났으면 의욕 충전
    {
        int times, time;
        _pTimerRealCharge->getTimes(times, time);
        if(times>0)
        {
            addReal(times);
        }
    }
    
    int result =_iRealMax-_iRealUse;
    return result;
}

float CPlayerModel::getRealPercent()
{
    int real = getReal();
    float result = (float)real/(float)_iRealMax;
    return result;
}

