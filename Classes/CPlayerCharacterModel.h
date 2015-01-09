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
class CPlayerCharacterModel
{
public:
    CPlayerCharacterModel();
    ~CPlayerCharacterModel();
    void reset();
    
    bool useEnergy(int useValue);
    void chargeEnergy(int charge);
    float getEnergyPercent();
    
protected:
    CC_SYNTHESIZE(int, _iEnergyMax, EnergyMax);
    CC_SYNTHESIZE_READONLY(int, _iEnergyUse, EnergyUse);
    
};


#endif /* defined(__dackjabara__CPlayerCharacterModel__) */
