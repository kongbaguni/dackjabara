//
//  CGameManager.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 3..
//
//

#include "CGameManager.h"
#include "CUtil.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CTitleScene.h"
CGameManager::CGameManager():
_pTileMap(NULL),
_pPlayerNode(NULL),
_pGameField(NULL),
_pDebugLogLabel(NULL),
_pMainTimerNode(NULL),
_pPauseLayer(NULL)
{
      
    
}
CGameManager::~CGameManager()
{
    CC_SAFE_RELEASE_NULL(_pPlayerNode);
    CC_SAFE_RELEASE_NULL(_pTileMap);
    CC_SAFE_RELEASE_NULL(_pGameField);
    CC_SAFE_RELEASE_NULL(_pDebugLogLabel);
    CC_SAFE_RELEASE_NULL(_pMainTimerNode);
    CC_SAFE_RELEASE_NULL(_pPauseLayer);
    
}

void CGameManager::gameOver()
{
    getParent()->removeChild(this);
    _pPlayerNode->getModel().reset();
    _pPlayerNode->init();
   // CSceneManager::getInstance()->addScene(CGameScene::create(), "game");
    Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("title"));
}
bool CGameManager::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    Size winsize = Director::getInstance()->getWinSize();
    setDebugLogLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), ""));
    _pDebugLogLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    _pDebugLogLabel->setPosition(Vec2(winsize.width-10.0f,0));
    
    addChild(_pDebugLogLabel);
    
    setMainTimerNode(CMainTimerNode::create());
    addChild(_pMainTimerNode,100);

    
    setPauseLayer(CPauseLayer::create());
    
    return true;
}

void CGameManager::reorderUnitZindex(float dt)
{
    Vector<Node*> childList = _pGameField->getChildren();
    for(Vector<Node*>::iterator it = childList.begin();
        it != childList.end();
        ++it)
    {
        Node* child = *it;
        int zorder = child->getPositionY()+_pTileMap->getContentSize().height;
        zorder = _pTileMap->getContentSize().height*2-zorder + 1000;
        child->setLocalZOrder(zorder);
    }
}
void CGameManager::onEnter()
{
    Node::onEnter();
    Size tileSize = _pTileMap->getContentSize();
    _pMainTimerNode->setPosition3D
    (Vec3(tileSize.width/2,tileSize.height-50,-tileSize.height/2+1));
    schedule(schedule_selector(CGameManager::reorderUnitZindex));

    
}

CGameManager* CGameManager::getInstance()
{
    static CGameManager* instance = NULL;
    if(instance==NULL)
    {
        instance = new CGameManager();
        instance->init();
    }
    return instance;
}

