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
_pLabel(NULL),
_pProgressTimer1(NULL),
_pProgressTimer2(NULL)
{
    
}

CAvatarUnitNode::~CAvatarUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pLabel);
    CC_SAFE_RELEASE_NULL(_pProgressTimer1);
    CC_SAFE_RELEASE_NULL(_pProgressTimer2);
    
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

    auto progress = Sprite::createWithSpriteFrameName("unit/progressBarBG.png");
    getSprite()->addChild(progress);
    progress->setPosition(Vec2(58,0));
    
    setProgressTimer1(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar1.png")));
    setProgressTimer2(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar2.png")));
    
    ProgressTimer* progressList[2] =
    {
        _pProgressTimer1,_pProgressTimer2
    };
    
    for(int i=0; i<2; i++)
    {
        //progressList[i]->setPosition3D(Vec3(0,0,1));
        
        progressList[i]->setPercentage(0.0f);
        progressList[i]->runAction(ProgressTo::create(1.0f, 100));
        progressList[i]->setType(ProgressTimer::Type::BAR);
        progressList[i]->setMidpoint(Vec2(0.0f,0.0f));
        progressList[i]->setBarChangeRate(Vec2(1.0f,0.0f));
        progressList[i]->setAnchorPoint(Vec2(0.0f,0.0f));
        progress->addChild(progressList[i]);
    }
    scheduleUpdate();
    
    return true;
}

void CAvatarUnitNode::update(float dt)
{
    setLocalZOrder(10000000-getPositionY());
    float p = (float)getHP()/(float)_iHPmax*100.0f;
    _pProgressTimer2->setPercentage(p);

}