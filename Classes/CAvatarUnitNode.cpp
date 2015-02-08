//
//  CAvatarUnitNode.cpp
//  darkjabara
//
//  Created by kongbaguni on 2015. 2. 6..
//
//

#include "CAvatarUnitNode.h"
#include "CUtil.h"

CAvatarUnitNode::CAvatarUnitNode():
_pLabel(NULL)
{
    
}

CAvatarUnitNode::~CAvatarUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pLabel);
    
}

bool CAvatarUnitNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    
    setLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), ""));
    addChild(_pLabel);
    _pLabel->setScale(0.5f);
    _pLabel->setVisible(false);

    
    return true;
}

