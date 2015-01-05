//
//  CGameManager.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 3..
//
//

#ifndef __shootinggamePrototype__CGameManager__
#define __shootinggamePrototype__CGameManager__

#include <stdio.h>
#include "cocos2d.h"
#include "CPlayerSprite.h"
#include <map>
USING_NS_CC;
class CGameManager : public Layer
{
public:
    virtual bool init();
    static CGameManager* getInstance();
private:
    CGameManager();
    virtual ~CGameManager();
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchStartPoint,TouchStartPoint);
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchMovement, TouchMovement);
    
    CC_SYNTHESIZE_RETAIN(CPlayerSprite*, _pPlayerSprite, PlayerSprite);
    CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _pTileMap, TileMap);

    bool _baArrowPress[4];
    
    void scheduleStopMovement(float dt);
    
    
};

#endif /* defined(__shootinggamePrototype__CGameManager__) */
