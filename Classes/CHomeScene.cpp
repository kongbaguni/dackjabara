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
#include "CGameManager.h"
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
    
    
    std::string fontName = CUtil::getFontName(CUtil::eFontList::TITLE);
    
    std::string text[2] =
    {
        "home",
        "BBobgi"
    };
    
    Node* boxList[2][2];
    Vector<MenuItem*> menuItemList;
    menuItemList.clear();
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            boxList[i][j] = ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box01.png", Rect(20,20,10,10));
            auto label = Label::createWithBMFont(fontName, text[i]);
            boxList[i][j]->addChild(label);
            label->setScale(0.5f);
        }
        boxList[i][1]->setColor(Color3B(255, 0, 0));
        auto menuitem =
        MenuItemSprite::create(boxList[i][0],boxList[i][1],CC_CALLBACK_1(CHomeScene::callBack, this));
        menuitem->setTag(i);
        menuItemList.pushBack(menuitem);
    }
    
    
    auto menu = Menu::createWithArray(menuItemList);
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
            CGameManager::getInstance()->newGameInit();
            Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("game"));
            break;
        case Tag::CARD_BBOBGI:
            break;
        default:
            break;
    }
}