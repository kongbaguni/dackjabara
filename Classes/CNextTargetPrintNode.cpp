//
//  CNextTargetPrintNode.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 1. 30..
//
//

#include "CNextTargetPrintNode.h"
#include "CGameManager.h"
#include "CRandom.h"
CNextTargetPrintNode::CNextTargetPrintNode():
_pTargetChicken(NULL),
_iCombo(0)
{
    _eNextTargetChickenState = CChikenNode::state::EGG;
    
}
CNextTargetPrintNode::~CNextTargetPrintNode()
{
    CC_SAFE_RELEASE_NULL(_pTargetChicken);
    
}
bool CNextTargetPrintNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    setTargetChicken(Sprite::createWithSpriteFrameName("unit/egg.png"));
    _pTargetChicken->setRotation3D(Vec3(-90, 0, 0));
    addChild(_pTargetChicken);
    
    return true;
}

void CNextTargetPrintNode::catchChicken(CChikenNode *chicken)
{
    if(chicken->getState()==_eNextTargetChickenState)
    {
        Vector<Node*> vec = CGameManager::getInstance()->getGameField()->getChildren();
        for(auto unit : vec)
        {
            int a = CRandom::getInstnace()->Random(6);
            if(unit->getTag()==(int) CUtil::unitTag::UNIT && unit!=CGameManager::getInstance()->getPlayerNode() && a == 0)
            {
                _eNextTargetChickenState = ((CChikenNode*)unit)->getState();
                break;
            }
        }
        
        changePictureWithNextState();
        
        
        _iCombo++;
    }
}
void CNextTargetPrintNode::changePictureWithNextState()
{
    std::string filename = "unit/";
    switch(_eNextTargetChickenState)
    {
        case CChikenNode::state::CHICK:
            filename+="chick";
            break;
        case CChikenNode::state::CHICK_DEAD:
            filename+="chickDead";
            break;
        case CChikenNode::state::COCK:
            filename+="cock";
            break;
        case CChikenNode::state::EGG:
            filename+="egg";
            break;
        case CChikenNode::state::EGG_BROKEN:
            filename+="eggBroken";
            break;
        case CChikenNode::state::HEN:
            filename+="hen";
        default:
            break;
    }
    filename+=".png";
    _pTargetChicken->setSpriteFrame(filename);
}
