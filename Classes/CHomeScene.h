//
//  CHomeScene.h
//  dackjabara
//
//  Created by kongbaguni on 2015. 2. 4..
//
//

#ifndef __dackjabara__CHomeScene__
#define __dackjabara__CHomeScene__

#include <stdio.h>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class CHomeScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(CHomeScene);
protected:
    enum class Tag
    {
        PLAYGAME,
        CARD_DECK,
        CARD_BBOBGI,
        GAME_SETTING,
        EXITGAME,
        
        TAG_MAX
    };
    
    CHomeScene();
    ~CHomeScene();
    virtual void onEnter();
    CC_SYNTHESIZE_RETAIN(ui::Scale9Sprite*, _pBox, Box);
    CC_SYNTHESIZE_RETAIN(Menu*, _pMenu, Menu);
    Vector<Node*> _vMenuNodes;
    void callBack(Ref* pSender);
    Color3B getColorByTag(Tag tag);
    Color3B getFontColorByTag(Tag tag);
};

/**tab menu */
class CTabMenu : public Node
{
public:
    CTabMenu();
    virtual ~CTabMenu();
    virtual bool init();
    CREATE_FUNC(CTabMenu);
protected:
    CC_SYNTHESIZE_RETAIN(Label*, _pLabelTitle, LabelTitle);
    virtual void setVisible(bool visible);
};

class CTabHomeMenu : public CTabMenu
{
public:
    virtual bool init();
    CREATE_FUNC(CTabHomeMenu);
};

class CTabCardDeckMenu : public CTabMenu
{
public:
    virtual bool init();
    CREATE_FUNC(CTabCardDeckMenu);
};

class CTabCardBBobgiMenu : public CTabMenu
{
public:
    virtual bool init();
    CREATE_FUNC(CTabCardBBobgiMenu);
};

class CTabGameSettingMenu : public CTabMenu
{
public:
    virtual bool init();
    CREATE_FUNC(CTabGameSettingMenu);
};


#endif /* defined(__dackjabara__CHomeScene__) */
