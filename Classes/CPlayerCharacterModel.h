//
//  CPlayerCharacterModel.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 9..
//
//

#ifndef __dackjabara__CPlayerCharacterModel__
#define __dackjabara__CPlayerCharacterModel__

#include <stdio.h>
#include "cocos2d.h"
#include "CChikenNode.h"

class CPlayerCharacterModel : public Ref
{
public:
    CPlayerCharacterModel();
    ~CPlayerCharacterModel();
    void reset();
    
    bool useEnergy(int useValue);
    void chargeEnergy(int charge);
    float getEnergyPercent();
    enum class state
    {
        NORMAL,
        FEFER,
        DEAD
    };
  
    void addScoreWithChicken(CChikenNode* chicken);
    int getScore(CChikenNode::state state);
    int getTotalScore();
    virtual bool init(){return true;};
    CREATE_FUNC(CPlayerCharacterModel);
    
protected:
    CC_SYNTHESIZE(int, _iEnergyMax, EnergyMax);
    CC_SYNTHESIZE_READONLY(int, _iEnergyUse, EnergyUse);
    CC_SYNTHESIZE(state, _eState, State);
   
    
    std::map<CChikenNode::state, int> _mapScore;
};


#endif /* defined(__dackjabara__CPlayerCharacterModel__) */
