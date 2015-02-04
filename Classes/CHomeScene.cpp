//
//  CHomeScene.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 4..
//
//

#include "CHomeScene.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
CHomeScene::CHomeScene()
{
    
}
CHomeScene::~CHomeScene()
{
    
}
bool CHomeScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    
    auto bg = Scale9Sprite::createWithSpriteFrameName("UI/box01.png", Rect(50, 50, 450, 450));
    
    
    return true;
}