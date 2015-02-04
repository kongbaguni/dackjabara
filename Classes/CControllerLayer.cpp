//
//  CControllerLayer.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 14..
//
//

#include "CControllerLayer.h"
#include "CGameManager.h"
#include "CSceneManager.h"
CControllerLayer::CControllerLayer():
_vec2TouchStartPointLeft(Vec2(0.0f,0.0f)),
_vec2TouchStartPointRight(Vec2(0.0f,0.0f)),
_vec2TouchMovement(Vec2(0.0f,0.0f)),
_pControllerLeftSelect(NULL),
_pControllerLeftBg(NULL),
_pControllerRightSelect(NULL),
_pControllerRightBg(NULL),
_fPlayerSpeed(5.0f)
{
    std::string fileName = CUtil::getHDSDname("texturePacker/game%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);

    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    //터치 리스너 등록
    {
        auto touchListner = EventListenerTouchAllAtOnce::create();
        touchListner->setEnabled(true);
        
        touchListner->onTouchesBegan = CC_CALLBACK_2(CControllerLayer::onTouchesBegan, this);
        touchListner->onTouchesMoved = CC_CALLBACK_2(CControllerLayer::onTouchesMoved, this);
        touchListner->onTouchesEnded = CC_CALLBACK_2(CControllerLayer::onTouchesEnded, this);
        touchListner->onTouchesCancelled = CC_CALLBACK_2(CControllerLayer::onTouchesCancelled, this);
        dispatcher->addEventListenerWithSceneGraphPriority(touchListner, this);
    }
    //키보드 리스너 등록
    {
        auto keyboardListener = EventListenerKeyboard::create();
        keyboardListener->setEnabled(true);
        keyboardListener->onKeyPressed = CC_CALLBACK_2(CControllerLayer::onKeyPressed, this);
        keyboardListener->onKeyReleased = CC_CALLBACK_2(CControllerLayer::onKeyReleased, this);
        dispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    }
    
    {
        auto acc = EventListenerAcceleration::create(CC_CALLBACK_2(CControllerLayer::onAcceleration, this));
        acc->setEnabled(true);
        dispatcher->addEventListenerWithSceneGraphPriority(acc, this);
    }
    
    

    memset(_baArrowPress, false, sizeof(_baArrowPress));
    //컨트롤러 그림 초기화
    {
        setControllerLeftBg(Sprite::createWithSpriteFrameName("UI/control_left_bg.png"));
        addChild(_pControllerLeftBg);
        
        setControllerLeftSelect(Sprite::createWithSpriteFrameName("UI/control_left_select.png"));
        _pControllerLeftBg->addChild(_pControllerLeftSelect);
        _pControllerLeftBg->setOpacity(100);
        Size s = _pControllerLeftBg->getContentSize();
        _pControllerLeftSelect->setPosition(Vec2(s.width/2,s.height/2));
        _pControllerLeftSelect->setOpacity(0);
        
        
        setControllerRightBg(Sprite::createWithSpriteFrameName("UI/control_right_bg.png"));
        addChild(_pControllerRightBg);
        
        setControllerRightSelect(Sprite::createWithSpriteFrameName("UI/control_right_select.png"));
        _pControllerRightBg->addChild(_pControllerRightSelect);
        
        
        _pControllerLeftBg->setVisible(false);
        _pControllerRightBg->setVisible(false);
        _pControllerRightSelect->setPosition(s.width/2, s.height/2);
        _pControllerRightSelect->setOpacity(0);
        _pControllerRightBg->setOpacity(100);
    }
    
}

CControllerLayer::~CControllerLayer()
{
    CC_SAFE_RELEASE_NULL(_pControllerLeftBg);
    CC_SAFE_RELEASE_NULL(_pControllerLeftSelect);
    CC_SAFE_RELEASE_NULL(_pControllerRightBg);
    CC_SAFE_RELEASE_NULL(_pControllerRightSelect);
    
}

CControllerLayer* CControllerLayer::getInstance()
{
    static CControllerLayer* instance = nullptr;
    if(instance==nullptr)
    {
        instance = new CControllerLayer();
    }
    return instance;
}


void CControllerLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    auto leftTouch = getLeftTouch(touches);
    if(leftTouch)
    {
        _vec2TouchStartPointLeft = leftTouch->getLocation();
        _pControllerLeftBg->setVisible(true);
        _pControllerLeftBg->setPosition(leftTouch->getLocation());
    }
    
    auto rightTouch = getRightTouch(touches);
    if(rightTouch)
    {
        _vec2TouchStartPointRight = rightTouch->getLocation();
        _pControllerRightBg->setVisible(true);
        _pControllerRightBg->setPosition(rightTouch->getLocation());
    }
    
}

void CControllerLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    auto leftMoveTouch = getLeftTouch(touches);
    if(leftMoveTouch)
    {
        const float fs = _fPlayerSpeed;
        Vec2 touchPoint = leftMoveTouch->getLocation();
        
        Vec2 tmp =  touchPoint - _vec2TouchStartPointLeft;
        CUtil::eDirection8 movement = CUtil::getMove8(tmp);
        switch (movement)
        {
            case CUtil::eDirection8::UP:
                _vec2TouchMovement = Vec2(0,fs);
                break;
            case CUtil::eDirection8::UP_LEFT:
                _vec2TouchMovement = Vec2(fs,fs);
                break;
            case CUtil::eDirection8::LEFT:
                _vec2TouchMovement = Vec2(fs,0);
                break;
            case CUtil::eDirection8::DOWN_LEFT:
                _vec2TouchMovement = Vec2(fs,-fs);
                break;
            case CUtil::eDirection8::DOWN:
                _vec2TouchMovement = Vec2(0, -fs);
                break;
            case CUtil::eDirection8::DOWN_RIGHT:
                _vec2TouchMovement = Vec2(-fs, -fs);
                break;
            case CUtil::eDirection8::RIGHT:
                _vec2TouchMovement = Vec2(-fs, 0);
                break;
            case CUtil::eDirection8::UP_RIGHT:
                _vec2TouchMovement = Vec2(-fs, fs);
                break;
            default:
                _vec2TouchMovement = Vec2(0,0);
                break;
        }
        
        
        switch (movement) {
            case CUtil::eDirection8::NOT_MOVE:
            {
                _pControllerLeftSelect->setOpacity(0);
            }
                break;
            default:
            {
                _pControllerLeftSelect->setOpacity(100);
                _pControllerLeftSelect->setRotation(_vec2TouchMovement.getAngle()*-57.3f+90.0f);
            }
                break;
        }
        
    }
    auto rightMoveTouch = getRightTouch(touches);
    if(rightMoveTouch)
    {
        Vec2 rt = rightMoveTouch->getLocation();
        Vec2 movement = rt-_vec2TouchStartPointRight;
        CUtil::eDirection8 m = CUtil::getMove8(movement);
        if(movement.getLength()<10.0f)
        {
            m = CUtil::eDirection8::NOT_MOVE;
        }
        switch(m)
        {
            case CUtil::eDirection8::NOT_MOVE:
                _pControllerRightSelect->setOpacity(0);
                break;
            default:
                _pControllerRightSelect->setOpacity(100);
                _pControllerRightSelect->setRotation(CUtil::getMove8Rotate(movement));
                break;
                
        }
        
    }
    
}

void CControllerLayer::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    _pControllerRightSelect->setOpacity(0);
    _pControllerLeftSelect->setOpacity(0);
    auto leftTouch = getLeftTouch(touches);
    if(leftTouch)
    {
        onTouchesMoved(touches, unused_event);
        _vec2TouchMovement = Vec2(0.0f, 0.0f);
        _vec2TouchStartPointLeft = leftTouch->getLocation();
        _pControllerLeftBg->setVisible(false);
    }
    
    auto rightTouch =getRightTouch(touches);
    if(rightTouch)
    {
        Vec2 rt = rightTouch->getLocation();
        Vec2 movement = rt-_vec2TouchStartPointRight;
        CUtil::eDirection8 m = CUtil::getMove8(movement);
        switch(m)
        {
            case CUtil::eDirection8::UP:
            case CUtil::eDirection8::UP_LEFT:
            case CUtil::eDirection8::UP_RIGHT:
                CGameManager::getInstance()->getPlayerNode()->jumpAction();
                break;
            case CUtil::eDirection8::LEFT:
            case CUtil::eDirection8::RIGHT:
            case CUtil::eDirection8::DOWN_LEFT:
            case CUtil::eDirection8::DOWN_RIGHT:
                CGameManager::getInstance()->getPlayerNode()->dashAction();
                break;
            case CUtil::eDirection8::DOWN:
                onKeyReleased(EventKeyboard::KeyCode::KEY_ESCAPE, unused_event);
                break;
            default:
                break;
        }
        _pControllerRightBg->setVisible(false);
    }
    
}
void CControllerLayer::onTouchesCancelled(const std::vector<Touch *> &touches, cocos2d::Event *unused_event)
{
    onTouchesEnded(touches, unused_event);
}

void CControllerLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    float fPlayerSpeed = _fPlayerSpeed;
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
            _vec2TouchMovement.y = fPlayerSpeed;
            _baArrowPress[0] = true;
            unschedule(schedule_selector(CControllerLayer::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            _vec2TouchMovement.y = -fPlayerSpeed;
            _baArrowPress[1] = true;
            unschedule(schedule_selector(CControllerLayer::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            _vec2TouchMovement.x = -fPlayerSpeed;
            _baArrowPress[2] = true;
            unschedule(schedule_selector(CControllerLayer::scheduleStopMovement));
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            _vec2TouchMovement.x = fPlayerSpeed;
            _baArrowPress[3] = true;
            unschedule(schedule_selector(CControllerLayer::scheduleStopMovement));
            break;
        default:
            break;
    }
    CCLOG("keyDown");
    
}
void CControllerLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
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
        schedule(schedule_selector(CControllerLayer::scheduleStopMovement));
    }
    
    //점프
    switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            CGameManager::getInstance()->getPlayerNode()->jumpAction();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
            CGameManager::getInstance()->getPlayerNode()->dashAction();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        {
            CGameManager::getInstance()->pauseGame();
        }
            
            break;
        default:
            break;
    }
}

void CControllerLayer::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *unused_event)
{
    CCLOG("acc %f %f %f",acc->x,acc->y,acc->z);
    
}
void CControllerLayer::scheduleStopMovement(float dt)
{
    _vec2TouchMovement.x*=0.9f;
    _vec2TouchMovement.y*=0.9f;
    float fMovementSize = fabsf(_vec2TouchMovement.x)+fabsf(_vec2TouchMovement.y);
    if(fMovementSize<=0.1f)
    {
        _vec2TouchMovement = Vec2(0.0f,0.0f);
        unschedule(schedule_selector(CControllerLayer::scheduleStopMovement));
    }
}

Touch* CControllerLayer::getNearTouch(const std::vector<Touch *> &touches, cocos2d::Vec2 pos, float dist)
{
    for(int i=0; i<touches.size(); i++)
    {
        Vec2 touchLocation = touches[i]->getLocation();
        float fD = touchLocation.getDistance(pos);
        if(fD<=dist)
        {
            return touches[i];
        }
    }
    return NULL;
}

Touch* CControllerLayer::getLeftTouch(const std::vector<Touch *> &touches)
{
    Size winsize = Director::getInstance()->getWinSize();
    Vec2 pos = Vec2(0,winsize.height/2);
    return getNearTouch(touches, pos, winsize.width/2);
}
Touch* CControllerLayer::getRightTouch(const std::vector<Touch *> &touches)
{
    Size winsize = Director::getInstance()->getWinSize();
    Vec2 pos = Vec2(winsize.width,winsize.height/2);
    return getNearTouch(touches, pos, winsize.width/2);
}