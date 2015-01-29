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
#include "CChikenNode.h"
CGameManager::CGameManager():
_pPlayerNode(NULL),
_pGameField(NULL),
_pDebugLogLabel(NULL),
_pMainTimerNode(NULL),
_pPauseLayer(NULL),
_pNextTargetNode(NULL)
{
      
    
}
CGameManager::~CGameManager()
{
    CC_SAFE_RELEASE_NULL(_pPlayerNode);
    CC_SAFE_RELEASE_NULL(_pGameField);
    CC_SAFE_RELEASE_NULL(_pDebugLogLabel);
    CC_SAFE_RELEASE_NULL(_pMainTimerNode);
    CC_SAFE_RELEASE_NULL(_pPauseLayer);
    CC_SAFE_RELEASE_NULL(_pNextTargetNode);
    
}

void CGameManager::gameOver()
{
    getParent()->removeChild(this);
    _pPlayerNode->getModel()->reset();
    CControllerLayer::getInstance()->setTouchMovement(Vec2::ZERO);
    _pPlayerNode->setMovement(Vec2::ZERO);
    getMainTimerNode()->getTimer()->stop();
    Director::getInstance()->pushScene(CSceneManager::getInstance()->getScene("title"));
    
}
bool CGameManager::init()
{
    if(!Node::init())
    {
        return false;
    }
    //Director::getInstance()->setDepthTest(true);
    
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


void CGameManager::onEnter()
{
    Node::onEnter();
    Size tileSize = _pGameField->getContentSize();
    _pMainTimerNode->setPosition3D
    (Vec3(tileSize.width/2,330,-tileSize.height+10));
    scheduleUpdate();

    if(_pNextTargetNode==NULL)
    {
        setNextTargetNode(CNextTargetPrintNode::create());
        addChild(_pNextTargetNode);
        _pNextTargetNode->setPosition3D(_pMainTimerNode->getPosition3D());
        _pNextTargetNode->setPosition(_pMainTimerNode->getPosition()+Vec2(0, -100));
        _pNextTargetNode->setRotation3D(Vec3(90,0,0));
    }
    
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

void CGameManager::update(float dt)
{
    insertEgg();

}
void CGameManager::insertEgg()
{
    int iCnt = 0;
    for(auto node:_pGameField->getChildren())
    {
        if(node->getTag()==(int)CUtil::unitTag::UNIT)
        {
            iCnt++;
        }
    }
    if(iCnt>10 || _pGameField==nullptr)
    {
        return;
    }

    for(int i=0; i<40; i++)
    {
        float tw = _pGameField->getContentSize().width;
        float th = _pGameField->getContentSize().height;
        int x = CRandom::getInstnace()->Random(tw-50)+25;
        int y = CRandom::getInstnace()->Random(th-50)+25;
        bool crash = CUtil::isCrashWithTMXTileMapSetting(_pGameField, "meta", "wall", Vec2(x,y),Vec2::ZERO)._bCrash;
        if(!crash)
        {
            auto chicken = CChikenNode::create();
            chicken->setPosition(x,y);
            _pGameField->addChild(chicken,(int)CUtil::unitTag::UNIT,(int)CUtil::unitTag::UNIT);
        }
        else
        {
            i--;
        }
    }
    
}

