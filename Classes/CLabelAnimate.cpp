//
//  CLabelAnimate.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 16..
//
//

#include "CLabelAnimate.h"
#include "CUtil.h"
CLabelAnimate* CLabelAnimate::createWithBMFont
(const std::string& bmfontFilePath,
 const int iStartNumber,
 const int iEndNumber,
 const TextHAlignment& alignment,
 int maxLineWidth,
 const Vec2& imageOffset)

{
    auto ret = new (std::nothrow) CLabelAnimate();
    
    
    if (ret && ret->setBMFontFilePath(bmfontFilePath,imageOffset))
    {
        ret->setMaxLineWidth(maxLineWidth);
        ret->autorelease();
        ret->setNumber(iStartNumber);
        ret->setTargetNumber(iEndNumber);
        ret->setString(textUtil::addCommaText(iStartNumber));
        ret->setChangeSpeed(0.1f);

        return ret;
    }
    
    delete ret;
    return nullptr;
    
}

void CLabelAnimate::onEnter()
{
    update(0);
    schedule(schedule_selector(CLabelAnimate::update));
}

void CLabelAnimate::onExit()
{
    unschedule(schedule_selector(CLabelAnimate::update));
}

void CLabelAnimate::update(float dt)
{
    if(_iNumber==_iTargetNumber)
    {
        return ;
    }
    int i = ceilf(((float)(_iTargetNumber - _iNumber) *_fChangeSpeed));
    _iNumber+=i;
    
    setString(textUtil::addCommaText(_iNumber));
}