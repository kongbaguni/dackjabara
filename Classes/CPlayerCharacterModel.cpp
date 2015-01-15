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
_iEnergyUse(0),
_eState(state::NORMAL)
{
    
}
CPlayerCharacterModel::~CPlayerCharacterModel()
{
    
}
void CPlayerCharacterModel::reset()
{
    _eState = state::NORMAL;
    _iEnergyUse = 0;
}

bool CPlayerCharacterModel::useEnergy(int useValue)
{
    if(useValue==0)
    {
        return true;
    }
    if(_iEnergyUse+useValue>_iEnergyMax)
    {
        return false;
    }
    _iEnergyUse+=useValue;
    
    return true;
}

void CPlayerCharacterModel::chargeEnergy(int charge)
{
    if(_iEnergyUse==0)
    {
        return;
    }
    _iEnergyUse-=charge;
    if(_iEnergyUse<0)
    {
        _iEnergyUse = 0;
    }
}

float CPlayerCharacterModel::getEnergyPercent()
{
    float result = (float)(_iEnergyMax-_iEnergyUse)/(float)_iEnergyMax;
    return result;
}
