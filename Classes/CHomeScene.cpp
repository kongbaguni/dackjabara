//
//  CHomeScene.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 4..
//
//

#include "CHomeScene.h"
#include "CUtil.h"
#include "CSceneManager.h"
#include "CCardBBobgiScene.h"
CHomeScene::CHomeScene():
_pBox(NULL)
{
    //    리소스 로딩
    std::string fileName = CUtil::getHDSDname("texturePacker/home%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);

    
}
CHomeScene::~CHomeScene()
{
    CC_SAFE_RELEASE_NULL(_pBox);
}
bool CHomeScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    Size winsize = Director::getInstance()->getWinSize();
    auto bg = LayerColor::create(Color4B(100, 200, 255, 255));
    addChild(bg);
    
    setBox(ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box01.png", Rect(20, 20, 10, 10)));
    addChild(_pBox);
    _pBox->setContentSize(winsize*0.95f);
    _pBox->setPosition(Vec2(winsize.width/2, winsize.height/2));
    
    
    std::string fontName = CUtil::getHDSDname("fonts/title2%s.fnt");
    auto menuitemPlayGame = MenuItemLabel::create(Label::createWithBMFont(fontName, "play Game"), CC_CALLBACK_1(CHomeScene::callBack, this));
    menuitemPlayGame->setTag((int)Tag::PLAYGAME);
    auto menuitemCardBBobgi = MenuItemLabel::create(Label::createWithBMFont(fontName, "Card BBobgi"), CC_CALLBACK_1(CHomeScene::callBack,this));
    menuitemCardBBobgi->setTag((int)Tag::CARD_BBOBGI);
    
    auto menu = Menu::create(menuitemPlayGame, menuitemCardBBobgi, NULL);
    menu->alignItemsHorizontally();
    
    _pBox->addChild(menu);
    
    
    
    return true;
}
void CHomeScene::onEnter()
{
    Scene::onEnter();
    Size winsize = Director::getInstance()->getWinSize();
    
    _pBox->setScale(0.1f);
    _pBox->setOpacity(0);
    _pBox->runAction
    (Sequence::create
     (DelayTime::create(0.3f),
      Spawn::create
      (FadeIn::create(1.0f),
       EaseExponentialInOut::create(JumpBy::create(1.0f, Vec2::ZERO, winsize.height*0.25f, 2)),
       EaseExponentialInOut::create(ScaleTo::create(1.0f, 1.0f)),
       NULL),
      NULL)
     );
    
}


void CHomeScene::callBack(cocos2d::Ref *pSender)
{
    auto node = (Node*)pSender;
    switch((Tag)node->getTag())
    {
        case Tag::PLAYGAME:
            Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("game"));
            break;
        case Tag::CARD_BBOBGI:
            Director::getInstance()->pushScene(CCArdBBobgiScene::create());
            break;
        default:
            break;
    }
}