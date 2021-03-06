//
//  CPlayerCharacterModel.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 9..
//
//

#include "CPlayerCharacterModel.h"
#include "CGameManager.h"
CPlayerCharacterModel::CPlayerCharacterModel():
_iEnergyMax(10000),
_iEnergyUse(0),
_eState(state::NORMAL)
{
    reset();
    
}
CPlayerCharacterModel::~CPlayerCharacterModel()
{
    
}
void CPlayerCharacterModel::reset()
{
    _mapScore.clear();
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

int CPlayerCharacterModel::getScoreWithChicken(CChikenNode *chicken)
{
    int score = 100;
    switch (chicken->getState())
    {
        case CChikenNode::state::EGG:
            score = 100;
            break;
        case CChikenNode::state::EGG_BROKEN:
            score = 300;
            break;
        case CChikenNode::state::CHICK:
            score = 110;
            break;
        case CChikenNode::state::CHICK_DEAD:
            score = 200;
            break;
        case CChikenNode::state::COCK:
            score = 5000;
            break;
        case CChikenNode::state::HEN:
            score = 10000;
            break;
        default:
            break;
    }
    int iLevelBonus = 1.0f+(chicken->getLevel()*0.1f);
    int iCombo = CGameManager::getInstance()->getNextTargetNode()->getCombo()+1;
    return score*iCombo*iLevelBonus;
}

void CPlayerCharacterModel::addScoreWithChicken(CChikenNode *chicken)
{
    _mapScore[chicken->getState()]+=getScoreWithChicken(chicken);
}

int CPlayerCharacterModel::getScore(CChikenNode::state state)
{
    return _mapScore[state];
}
int CPlayerCharacterModel::getTotalScore()
{
    int result = 0;
    for (std::map<CChikenNode::state,int>::iterator it = _mapScore.begin(); it != _mapScore.end(); ++it)
    {
        result+=(*it).second;
    }
    
         
    
    return result;
}
