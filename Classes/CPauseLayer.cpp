//
//  CPauseLayer.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 6..
//
//

#include "CPauseLayer.h"
#include "CGameManager.h"
CPauseLayer::CPauseLayer()
{
    
}
CPauseLayer::~CPauseLayer()
{
    
}
bool CPauseLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    auto bg = LayerColor::create(Color4B(0,0,0,200));
    addChild(bg);
    
    auto Titlelabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "Pause");
    auto menuTitle = MenuItemLabel::create(Titlelabel);
    
    auto resumeLabel = Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "resume");
    auto menuResume =
    MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(CPauseLayer::menuCallback, this));
    menuResume->setTag((int)menuType::RESUME);

    
    auto menu = Menu::create(menuTitle,menuResume, nullptr);
    menu->alignItemsVertically();
    addChild(menu);
    menu->setRotation3D(Vec3(-10,0,0));
    menu->runAction(RepeatForever::create(JumpTo::create(1.0f, Vec2(0,0), 100, 2)));;

    Titlelabel->runAction(EaseExponentialOut::create(MoveBy::create(0.4f, Vec2(-200,0))));
    
    
    
    return true;
}
void CPauseLayer::onEnter()
{
    CGameManager::getInstance()->getMainTimerNode()->getTimer()->pause();
    if(CGameManager::getInstance()->getGameField())
    {
        Vector<Node*> childList =
        CGameManager::getInstance()->getGameField()->getChildren();
        for(Vector<Node *>::iterator it = childList.begin(); it!=childList.end(); ++it)
        {
            Node* node = *it;
            node->pause();
        }
    }
    
}
void CPauseLayer::onExit()
{

    CGameManager::getInstance()->getMainTimerNode()->getTimer()->resume();
    
    if(CGameManager::getInstance()->getGameField())
    {
        Vector<Node*> childList =
        CGameManager::getInstance()->getGameField()->getChildren();
        for(Vector<Node *>::iterator it = childList.begin(); it!=childList.end(); ++it)
        {
            Node* node = *it;
            node->resume();
        }
    }
    
    
}


void CPauseLayer::menuCallback(cocos2d::Ref *sender)
{
    Node* node = (Node*)sender;
    switch ((menuType)node->getTag())
    {
        case menuType::RESUME:
            removeFromParent();
            break;
        default:
            break;
    }
    
}