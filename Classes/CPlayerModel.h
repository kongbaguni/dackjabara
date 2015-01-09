//
//  CPlayerModel.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 9..
//
//

#ifndef __dackjabara__CPlayerModel__
#define __dackjabara__CPlayerModel__

#include <stdio.h>
#include "CUtil.h"
#include "CTimer.h"

class CPlayerModel : public Ref
{
public:
    CPlayerModel();
    ~CPlayerModel();
    virtual bool init(){return true;};
    CREATE_FUNC(CPlayerModel);
    
    bool useCredit(int iCredit);
    void addCredit(int iCredit);
    
    bool useReal(int iReal);
    void addReal(int iReal);
    void addReal(int iReal,bool bUnLimit);
    int getReal();
    float getRealPercent();
    
private:
    //인앱결재로 충전하는 크레딧. 1코인=1달러.
    CC_SYNTHESIZE_READONLY(int,_iCredit,Credit);
    
    // 1코인 사용으로 충전.
    int _iRealUse;
    CC_SYNTHESIZE(int, _iRealMax, RealMax);
 
    //의욕충전용 타이머. 5분에 1의욕 충전.
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimerRealCharge, TimerRealCharge);
};

#endif /* defined(__dackjabara__CPlayerModel__) */
