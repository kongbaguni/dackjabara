//
//  CPauseScene.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 11..
//
//

#include "CPauseScene.h"
#include "CPauseLayer.h"
#include "CSceneManager.h"
bool CPauseScene::init()
{
    if(!Scene::init())
    {
        return false;
        
    }
    auto bg = LayerColor::create(Color4B(0,0,0,200));
    addChild(bg);
    
    auto Titlelabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "Pause");
    auto menuTitle = MenuItemLabel::create(Titlelabel);
    
    auto resumeLabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "resume");
    auto menuResume =
    MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(CPauseScene::menuCallback, this));
    
    
    auto menu = Menu::create(menuTitle,menuResume, nullptr);
    menu->alignItemsVertically();
    addChild(menu);
    menu->setRotation3D(Vec3(-10,0,0));
//    menu->runAction(RepeatForever::create(JumpTo::create(1.0f, Vec2(0,0), 100, 2)));;
//    
//    Titlelabel->runAction(EaseExponentialOut::create(MoveBy::create(0.4f, Vec2(-200,0))));
    
    return true;
}



void CPauseScene::menuCallback(cocos2d::Ref *sender)
{
    Director::getInstance()->pushScene
    (CSceneManager::getInstance()->getScene("game"));

    
}