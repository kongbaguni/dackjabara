//
//  CPlayerCharacterModel.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 9..
//
//

#include "CPlayerCharacterModel.h"
CPlayerCharacterModel::CPlayerCharacterModel():
_iEnergyMax(2000),
_iEnergyUse(0)
{
    
}
CPlayerCharacterModel::~CPlayerCharacterModel()
{
    
}
void CPlayerCharacterModel::reset()
{
    _iEnergyUse = 0;
}

bool CPlayerCharacterModel::useEnergy(int useValue)
{
    if(useValue==0)
    {
        return false;
    }
    if(_iEnergyUse+useValue>_iEnergyMax)
    {
        return false;
    }
    _iEnergyUse+=useValue;
    
    return true;
}