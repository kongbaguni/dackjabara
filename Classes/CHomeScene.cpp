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
#include "CCardNode.h"

CHomeScene::CHomeScene():
_pBox(NULL),
_pMenu(NULL)
{

    
}
CHomeScene::~CHomeScene()
{
    CC_SAFE_RELEASE_NULL(_pBox);
    CC_SAFE_RELEASE_NULL(_pMenu);
}
bool CHomeScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->preloadEffect("effect/bowFire.mp3");
    
    Size winsize = Director::getInstance()->getWinSize();
    auto bg = LayerColor::create(Color4B(100, 200, 255, 255));
    addChild(bg);
    
    setBox(ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box02.png", Rect(20, 20, 10, 10)));
    addChild(_pBox);
    _pBox->setContentSize(Size(800, winsize.height*0.95f));
    _pBox->setPosition(Vec2(winsize.width/2, winsize.height/2));
    

    //메뉴로 바뀌는 메뉴판 내용 초기화
    {
        Node* m[] =
        {
            CTabHomeMenu::create(),
            CTabCardDeckMenu::create(),
            CTabCardBBobgiMenu::create(),
            CTabRankingMenu::create(),
            CTabGameSettingMenu::create(),
        };
        for(int i=0; i<sizeof(m)/sizeof(Node*); i++)
        {
            _pBox->addChild(m[i]);
            _vMenuNodes.pushBack(m[i]);
            m[i]->setVisible(false);
            m[i]->setPosition(_pBox->getContentSize()*0.5f);
        }
    }

 
    

    //토글메뉴 초기화
    {
        std::string fontName = CUtil::getFontName(CUtil::eFontList::TITLE);
        
        std::string text[] =
        {
            "Home",
            "Deck",
            "BBobgi",
            "Ranking",
            "Setting",
        };
        const int MENU_SIZE = sizeof(text)/sizeof(std::string);
        Node* boxList[MENU_SIZE][4];
        Vector<MenuItem*> menuItemList;
        menuItemList.clear();
        for(int i=0; i<MENU_SIZE ; i++)
        {
            for(int j=0; j<4; j++)
            {
                boxList[i][j] = ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box01.png", Rect(20,20,10,10));
                boxList[i][j]->setContentSize(Size(150, 80));
                auto label = Label::createWithBMFont(fontName, text[i]);
                label->setAnchorPoint(Vec2::ZERO);
                label->setPosition(Vec2(10,10));
                boxList[i][j]->addChild(label);
                label->setScale(0.5f);
                if(j==2)
                {
                    label->setColor(getFontColorByTag((Tag)i));
                }
            }
            boxList[i][1]->setColor(Color3B(255,255,0));
            boxList[i][2]->setColor(getColorByTag((Tag)i));
            
            boxList[i][3]->setColor(Color3B(255,255,0));
            
            const ccMenuCallback & callback = CC_CALLBACK_1(CHomeScene::callBack, this);
            auto menuitem1 =
            MenuItemSprite::create(boxList[i][0],boxList[i][1],callback);
            auto menuitem2 =
            MenuItemSprite::create(boxList[i][2],boxList[i][3],callback);
            
            auto toggleMenu = MenuItemToggle::createWithCallback(callback, menuitem1, menuitem2, NULL);
            toggleMenu->setTag(i);
            menuItemList.pushBack(toggleMenu);
        }
        
        auto firstMenuItem = (MenuItemToggle*)*menuItemList.begin();
        firstMenuItem->setSelectedIndex(1);
        
        setMenu(Menu::createWithArray(menuItemList));
        _pMenu->alignItemsVerticallyWithPadding(10);
        
        _pBox->addChild(_pMenu);
        _pMenu->setPositionX(winsize.width*0.5-450);
    }
    
    
    
    
    return true;
}
Color3B CHomeScene::getColorByTag(Tag tag)
{
    switch(tag)
    {
        case Tag::PLAYGAME:
            return Color3B(255, 0, 0);
        case Tag::CARD_DECK:
            return Color3B(255,120,120);
        case Tag::CARD_BBOBGI:
            return Color3B(0,255,0);
        case Tag::GAME_SETTING:
            return Color3B(0,125,255);
        case Tag::RANKING:
            return Color3B(255,130,220);
        default:
            break;
    }
    return Color3B::WHITE;
}
Color3B CHomeScene::getFontColorByTag(Tag tag)
{
    switch(tag)
    {
        case Tag::PLAYGAME:
            return Color3B::YELLOW;
        case Tag::CARD_DECK:
            return Color3B::GREEN;
        case Tag::CARD_BBOBGI:
            return Color3B::RED;
        case Tag::GAME_SETTING:
            return Color3B::YELLOW;
        case Tag::RANKING:
            return Color3B::GRAY;
        default:
            break;
    }
    return Color3B::WHITE;
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
    
    callBack(*_pMenu->getChildren().begin());
}


void CHomeScene::callBack(cocos2d::Ref *pSender)
{
    auto node = (Node*)pSender;
    int iTag = node->getTag();
    for(auto menu : _pMenu->getChildren())
    {
        MenuItemToggle* t = (MenuItemToggle*)menu;
        t->setSelectedIndex(0);
        t->stopAllActions();
        t->runAction
        (EaseExponentialInOut::create
         (MoveTo::create(1.0f, Vec2(0,t->getPositionY()))));
        t->setEnabled(true);
    }
    MenuItemToggle* t = (MenuItemToggle*)node;
    t->setSelectedIndex(1);
    t->stopAllActions();
    t->runAction(EaseExponentialInOut::create(MoveTo::create(2.0f, Vec2(-30,t->getPositionY()))));
    _pBox->setColor(getColorByTag((Tag)iTag));
    t->setEnabled(false);

    
    //메뉴판때기 보이거나 사라지게 하기.
    for(auto node : _vMenuNodes)
    {
        node->setVisible(false);
    }
    _vMenuNodes.at(iTag)->setVisible(true);
    
    
    switch((Tag)node->getTag())
    {
        case Tag::PLAYGAME:
            break;
        case Tag::CARD_BBOBGI:
            break;
        default:
            break;
    }
}


/**tab menu */
CTabMenu::CTabMenu():
_pLabelTitle(NULL)
{
    
}
CTabMenu::~CTabMenu()
{
    CC_SAFE_RELEASE_NULL(_pLabelTitle);
    
}
bool CTabMenu::init()
{
    if(!Node::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();

    auto box = ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box01.png", Rect(20,20,10,10));
    addChild(box);
    box->setContentSize(Size(750,winsize.height*0.9f));
    
    auto box2 = ui::Scale9Sprite::createWithSpriteFrameName("homeUI/box01.png", Rect(20,20,10,10));
    addChild(box2);
    box2->setContentSize(Size(250,70));
    box2->setPosition(Vec2(0,280));

    setLabelTitle(Label::createWithBMFont(CUtil::getFontName(CUtil::eFontList::TITLE2), "menuTitle"));
    addChild(_pLabelTitle);
    _pLabelTitle->setPosition(Vec2(0, 280));

    return true;
}

bool CTabHomeMenu::init()
{
    if(!CTabMenu::init())
    {
        return false;
    }
    getLabelTitle()->setString("HOME");
   
    const ccMenuCallback & callback = CC_CALLBACK_1(CTabHomeMenu::callBack, this);

    auto menuItem = MenuItemLabel::create(Label::createWithBMFont(CUtil::getFontName(CUtil::eFontList::TITLE2), "Start Game"),callback);
    auto menu = Menu::create(menuItem, NULL);
    addChild(menu);
    menu->alignItemsHorizontally();
    menu->setPosition(Vec2::ZERO);
    return true;
}
void CTabHomeMenu::callBack(cocos2d::Ref *pSender)
{
//    auto node = (Node*)pSender;
    CGameManager::getInstance()->newGameInit();
    Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("game"));
}

void CTabMenu::setVisible(bool visible)
{
    if(visible && !isVisible())
    {
        runAction
        (Sequence::create
         (EaseElasticInOut::create(ScaleTo::create(0.1f, 1.05f, 0.5f), 0.3f),
          EaseElasticInOut::create(ScaleTo::create(0.1f, 0.95f, 1.05f), 0.3f),
          EaseElasticInOut::create(ScaleTo::create(0.1f, 1.0f), 0.3f),
          NULL
          ));
        SimpleAudioEngine::getInstance()->playEffect("effect/bowFire.mp3");
    }
    Node::setVisible(visible);
}

bool CTabCardBBobgiMenu::init()
{
    if(!CTabMenu::init())
    {
        return false;
    }
    getLabelTitle()->setString("card bbobgi");
    return true;
}
bool CTabCardDeckMenu::init()
{
    if(!CTabMenu::init())
    {
        return false;
    }
    getLabelTitle()->setString("card deck");
    return true;
}
bool CTabGameSettingMenu::init()
{
    if(!CTabMenu::init())
    {
        return false;
    }
    getLabelTitle()->setString("gameSetting");
    return true;
}

bool CTabRankingMenu::init()
{
    if(!CTabMenu::init())
    {
        return false;
    }
    getLabelTitle()->setString("Ranking");
    return true;
}

