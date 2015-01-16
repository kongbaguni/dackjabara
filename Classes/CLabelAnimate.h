//
//  CLabelAnimate.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 16..
//
//

#ifndef __dackjabara__CLabelAnimate__
#define __dackjabara__CLabelAnimate__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class CLabelAnimate : public Label
{
public:
    static CLabelAnimate* createWithBMFont(const std::string& bmfontFilePath,
                                                       const int iStartNumber,
                                           const int iEndNumber,
                                           const TextHAlignment& alignment = TextHAlignment::LEFT, int maxLineWidth = 0,
                                           const Vec2& imageOffset = Vec2::ZERO);
    
    virtual void update(float dt);
protected:
    virtual void onEnter();
    virtual void onExit();
    CC_SYNTHESIZE(int, _iNumber, Number);
    CC_SYNTHESIZE(int, _iTargetNumber, TargetNumber);

};

#endif /* defined(__dackjabara__CLabelAnimate__) */
