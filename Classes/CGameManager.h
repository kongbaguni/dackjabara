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
#include "CControllerLayer.h"
#include "CNextTargetPrintNode.h"

#include <map>
USING_NS_CC;
class CGameManager : public Node
{
public:
    virtual bool init();
    static CGameManager* getInstance();

    void gameOver();
    void gameOver_finish();
    
    void pauseGame();

private:
    CGameManager();
    virtual ~CGameManager();
    

    CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _pGameField, GameField);
    CC_SYNTHESIZE_RETAIN(CPlayerCharacterNode*, _pPlayerNode, PlayerNode);
    CC_SYNTHESIZE_RETAIN(Label*, _pDebugLogLabel, DebugLogLabel);
    CC_SYNTHESIZE_RETAIN(CMainTimerNode*, _pMainTimerNode, MainTimerNode);
    CC_SYNTHESIZE_RETAIN(CNextTargetPrintNode*, _pNextTargetNode, NextTargetNode);
    
    CC_SYNTHESIZE_RETAIN(CPauseLayer*, _pPauseLayer, PauseLayer);
    CC_SYNTHESIZE_RETAIN(CControllerLayer*, _pControllerLayer, ControllerLayer);
    CC_SYNTHESIZE_RETAIN(Label*, _pTitleLabel, TitleLabel);

    
    
    virtual void onEnter();
    virtual void update(float dt);
    
    void insertEgg();
    
};

#endif /* defined(__shootinggamePrototype__CGameManager__) */
