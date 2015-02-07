//
//  CCardBBobgiScene.cpp
//  darkjabara
//
//  Created by kongbaguni on 2015. 2. 6..
//
//

#include "CCardBBobgiScene.h"
#include "CCardNode.h"
#include "CUtil.h"
CCArdBBobgiScene::CCArdBBobgiScene()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CUtil::getHDSDname("texturePacker/card%s.plist"));
    
}
CCArdBBobgiScene::~CCArdBBobgiScene()
{
    
}

bool CCArdBBobgiScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();
  
    auto layer = LayerColor::create(Color4B(100, 155, 255,255), 1920, 1280);
    addChild(layer);
    
    
    
    auto card = CCardNode::create(0);
    card->setPosition(Vec2(winsize.width/2,winsize.height/2));
    addChild(card);
    
    
    return true;
}