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
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;

bool CPauseScene::init()
{
    if(!Scene::init())
    {
        return false;
        
    }
    auto bg = LayerColor::create(Color4B(0,0,0,200));
    addChild(bg);
    
    Size winsize = Director::getInstance()->getWinSize();
    
    auto box = ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box02.png", Rect(20, 20, 10, 10));
    addChild(box);
    box->setContentSize(Size(800, winsize.height*0.95f));
    box->setPosition(Vec2(winsize.width/2, winsize.height/2));

    
    
    std::string title[] =
    {
        "resume",
        "exit game",
    };

    Vector<MenuItem*>menuList;
    menuList.clear();
    auto Titlelabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "Pause");
    menuList.pushBack(MenuItemLabel::create(Titlelabel));

    for(int i=0; i<sizeof(title)/sizeof(std::string); i++)
    {
        auto resumeLabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), title[i]);
        auto menuItem =
        MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(CPauseScene::menuCallback, this));
        menuItem->setTag(i);
        menuList.pushBack(menuItem);
    }
    
    auto menu = Menu::createWithArray(menuList);
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
    auto node = (Node*)sender;
    switch((eTag)node->getTag())
    {
        case eTag::RESUME:
            Director::getInstance()->pushScene
            (CSceneManager::getInstance()->getScene("game"));
            break;
        case eTag::EXIT_GAME:
            Director::getInstance()->pushScene
            (CSceneManager::getInstance()->getScene("gameResult"));
            break;
    }

    
}