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
#include "CPlayerCharacterNode.h"
#include "CMainTimerNode.h"
#include "CPauseLayer.h"

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
    
    //touch event
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
    //keyboard event
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);


    
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchStartPointLeft,TouchStartPointLeft);
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchStartPointRight, TouchStartPointRight)
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchMovement, TouchMovement);
    CC_SYNTHESIZE_READONLY(float, _fPlayerSpeed, PlayerSpeed);

    CC_SYNTHESIZE_RETAIN(Node*, _pGameField, GameField);
    CC_SYNTHESIZE_RETAIN(CPlayerCharacterNode*, _pPlayerNode, PlayerNode);
    CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _pTileMap, TileMap);
    CC_SYNTHESIZE_RETAIN(Label*, _pDebugLogLabel, DebugLogLabel);
    CC_SYNTHESIZE_RETAIN(CMainTimerNode*, _pMainTimerNode, MainTimerNode);
    
    CC_SYNTHESIZE_RETAIN(CPauseLayer*, _pPauseLayer, PauseLayer);

    bool _baArrowPress[4];
    
    void scheduleStopMovement(float dt);
    
    Touch* getNearTouch(const std::vector<Touch *> &touches, Vec2 pos, float dist);    
    Touch* getLeftTouch(const std::vector<Touch *> &touches);
    Touch* getRightTouch(const std::vector<Touch *> &touches);
    
    virtual void onEnter();
    
    void reorderUnitZindex(float dt);
    
};

#endif /* defined(__shootinggamePrototype__CGameManager__) */
