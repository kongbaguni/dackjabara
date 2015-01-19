//
//  CControllerLayer.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 14..
//
//

#ifndef __dackjabara__CControllerLayer__
#define __dackjabara__CControllerLayer__

#include <stdio.h>
#include "CUtil.h"
class CControllerLayer : public Layer
{
public:
    static CControllerLayer* getInstance();
    CControllerLayer();
    ~CControllerLayer();

    //keyboard event
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    //touch event
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
protected:

    
    virtual void onAcceleration(Acceleration* acc, Event* unused_event);
    
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchStartPointLeft,TouchStartPointLeft);
    CC_SYNTHESIZE_READONLY(Vec2, _vec2TouchStartPointRight, TouchStartPointRight)
    CC_SYNTHESIZE(Vec2, _vec2TouchMovement, TouchMovement);
    CC_SYNTHESIZE_READONLY(float, _fPlayerSpeed, PlayerSpeed);

    Touch* getNearTouch(const std::vector<Touch *> &touches, Vec2 pos, float dist);
    Touch* getLeftTouch(const std::vector<Touch *> &touches);
    Touch* getRightTouch(const std::vector<Touch *> &touches);
    
    void scheduleStopMovement(float dt);


    bool _baArrowPress[4];
   
    CC_SYNTHESIZE_RETAIN(Sprite*, _pControllerLeftBg, ControllerLeftBg);
    CC_SYNTHESIZE_RETAIN(Sprite*, _pControllerLeftSelect, ControllerLeftSelect);
    
    CC_SYNTHESIZE_RETAIN(Sprite*, _pControllerRightBg, ControllerRightBg);
    CC_SYNTHESIZE_RETAIN(Sprite*, _pControllerRightSelect, ControllerRightSelect);
    

};
#endif /* defined(__dackjabara__CControllerLayer__) */
