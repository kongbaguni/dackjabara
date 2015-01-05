//
//  CGameManager.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 3..
//
//

#include "CGameManager.h"
#include "CUtil.h"
CGameManager::CGameManager():
_vec2TouchStartPoint(Vec2(0.0f,0.0f)),
_vec2TouchMovement(Vec2(0.0f,0.0f)),
_pTileMap(NULL),
_pPlayerSprite(NULL),
_pGameField(NULL),
_pDebugLogLabel(NULL),
_fPlayerSpeed(10)
{
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    //터치 리스너 등록
    {
        auto touchListner = EventListenerTouchAllAtOnce::create();
        touchListner->setEnabled(true);
        
        touchListner->onTouchesBegan = CC_CALLBACK_2(CGameManager::onTouchesBegan, this);
        touchListner->onTouchesMoved = CC_CALLBACK_2(CGameManager::onTouchesMoved, this);
        touchListner->onTouchesEnded = CC_CALLBACK_2(CGameManager::onTouchesEnded, this);
        touchListner->onTouchesCancelled = CC_CALLBACK_2(CGameManager::onTouchesCancelled, this);
        dispatcher->addEventListenerWithSceneGraphPriority(touchListner, this);
    }
    //키보드 리스너 등록
    {
        auto keyboardListener = EventListenerKeyboard::create();
        keyboardListener->setEnabled(true);
        keyboardListener->onKeyPressed = CC_CALLBACK_2(CGameManager::onKeyPressed, this);
        keyboardListener->onKeyReleased = CC_CALLBACK_2(CGameManager::onKeyReleased, this);
        dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    }
 
    
    
    
    memset(_baArrowPress, false, sizeof(_baArrowPress));
    
    
}
CGameManager::~CGameManager()
{
    CC_SAFE_RELEASE_NULL(_pPlayerSprite);
    CC_SAFE_RELEASE_NULL(_pTileMap);
    CC_SAFE_RELEASE_NULL(_pGameField);
    CC_SAFE_RELEASE_NULL(_pDebugLogLabel);
    
}

bool CGameManager::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    
    Size winsize = Director::getInstance()->getWinSize();
    setDebugLogLabel(Label::createWithBMFont(CUtil::getHDSDname("fonts/title%s.fnt"), "0"));
    _pDebugLogLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
    _pDebugLogLabel->setPosition(Vec2(winsize.width-10.0f,0));
    
    addChild(_pDebugLogLabel);
    return true;
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

void CGameManager::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    _vec2TouchStartPoint = touches[0]->getLocation();
}

void CGameManager::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    const float fs = _fPlayerSpeed;
    Vec2 touchPoint = touches[0]->getLocation();
    Vec2 tmp =  touchPoint - _vec2TouchStartPoint;
    CUtil::movement8 movement = CUtil::getMove8(tmp);
    switch (movement)
    {
        case CUtil::movement8::UP:
            _vec2TouchMovement = Vec2(0,fs);
            break;
        case CUtil::movement8::UP_LEFT:
            _vec2TouchMovement = Vec2(fs,fs);
            break;
        case CUtil::movement8::LEFT:
            _vec2TouchMovement = Vec2(fs,0);
            break;
        case CUtil::movement8::DOWN_LEFT:
            _vec2TouchMovement = Vec2(fs,-fs);
            break;
        case CUtil::movement8::DOWN:
            _vec2TouchMovement = Vec2(0, -fs);
            break;
        case CUtil::movement8::DOWN_RIGHT:
            _vec2TouchMovement = Vec2(-fs, -fs);
            break;
        case CUtil::movement8::RIGHT:
            _vec2TouchMovement = Vec2(-fs, 0);
            break;
        case CUtil::movement8::UP_RIGHT:
            _vec2TouchMovement = Vec2(-fs, fs);
            break;
        default:
            _vec2TouchMovement = Vec2(0,0);
            break;
    }

}

void CGameManager::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    onTouchesMoved(touches, unused_event);
    _vec2TouchMovement = Vec2(0.0f, 0.0f);
    _vec2TouchStartPoint = touches[0]->getLocation();
    if(touches.size()==2)
    {
        _pPlayerSprite->jumpAction();
    }
    
}
void CGameManager::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    onTouchesEnded(touches, unused_event);
}

void CGameManager::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    float fPlayerSpeed = 5;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _vec2TouchMovement.y = fPlayerSpeed;
            _baArrowPress[0] = true;
            unschedule(schedule_selector(CGameManager::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _vec2TouchMovement.y = -fPlayerSpeed;
            _baArrowPress[1] = true;
            unschedule(schedule_selector(CGameManager::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _vec2TouchMovement.x = -fPlayerSpeed;
            _baArrowPress[2] = true;
            unschedule(schedule_selector(CGameManager::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _vec2TouchMovement.x = fPlayerSpeed;
            _baArrowPress[3] = true;
            unschedule(schedule_selector(CGameManager::scheduleStopMovement));
            break;
        default:
            break;
    }
    CCLOG("keyDown");
    
}
void CGameManager::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    //방향키검사
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _baArrowPress[0] = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _baArrowPress[1] = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _baArrowPress[2] = false;
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _baArrowPress[3] = false;
            break;
        default:
            break;
    }
    int iKeyTest = 0;
    for (int i=0; i<4; i++)
    {
        iKeyTest+=(int)_baArrowPress[i];
    }
    if(iKeyTest==0)
    {
        schedule(schedule_selector(CGameManager::scheduleStopMovement));
    }

    //점프 
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            _pPlayerSprite->jumpAction();
            break;
        default:
            break;
    }
}

void CGameManager::scheduleStopMovement(float dt)
{
    _vec2TouchMovement.x*=0.9f;
    _vec2TouchMovement.y*=0.9f;
    float fMovementSize = fabsf(_vec2TouchMovement.x)+fabsf(_vec2TouchMovement.y);
    if(fMovementSize<=0.1f)
    {
        _vec2TouchMovement = Vec2(0.0f,0.0f);
        unschedule(schedule_selector(CGameManager::scheduleStopMovement));
    }
}
