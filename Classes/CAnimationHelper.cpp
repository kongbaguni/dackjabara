//
//  CAnimationHelper.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CAnimationHelper.h"
void CAnimationHelper::addAnimation
(std::vector<std::string> frameNameList,
 std::string animationName,
 float fDelay,
 bool bLoop)
{
    if(frameNameList.size()==0 || animationName.size()==0)
    {
        return;
    }
    auto ani = AnimationCache::getInstance()->getAnimation(animationName);
    if(ani!=NULL)
    {
        return;
    }
    
    Vector<SpriteFrame*> frameList;
    for(std::vector<std::string>::iterator it = frameNameList.begin();
        it!=frameNameList.end();
        ++it)
    {
        std::string frameName = *it;
        CCLOG("frameName : %s",frameName.c_str());
        if(frameName.size()>0)
        {
            SpriteFrame* frame = Sprite::createWithSpriteFrameName(frameName)->getSpriteFrame();
            frameList.pushBack(frame);
        }
    }
    Animation* animation = Animation::createWithSpriteFrames(frameList);
    animation->setDelayPerUnit(fDelay);
    animation->setLoops(bLoop);
    AnimationCache::getInstance()->addAnimation(animation, animationName);
    
}

void CAnimationHelper::addAnimation
(std::string frameFormat,
 const int iStartFrame,
 const int iEndFrame,
 std::string animationName,
 float fDelay,
 bool bLoop
 )
{
    CCLOG("addAnimation : %s",frameFormat.c_str());
    auto ani = AnimationCache::getInstance()->getAnimation(animationName);
    if(ani!=NULL)
    {
        return;
    }


    std::vector<std::string> frameList;
    if(iStartFrame<iEndFrame)
    {
        for(int i=iStartFrame; i<=iEndFrame; i++)
        {
            auto string = String::createWithFormat(frameFormat.c_str(),i);
            std::string frameName;
            frameName.append(string->getCString());
            frameList.push_back(frameName);
        }

    }
    else if(iStartFrame>iEndFrame)
    {
        for(int i=iStartFrame; i>=iEndFrame; i--)
        {
            auto string = String::createWithFormat(frameFormat.c_str(),i);
            frameList.push_back(string->_string);
        }
    }
    
    addAnimation(frameList, animationName,fDelay,bLoop);
    
}


