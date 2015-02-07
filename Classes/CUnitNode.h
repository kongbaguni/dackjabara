//
//  CUnitNode.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 8..
//
//

#ifndef __dackjabara__CUnitNode__
#define __dackjabara__CUnitNode__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "CTimer.h"


class CUnitNode : public Node
{
public:
    enum class eAttribute
    {
        NONE,
        FIRE,
        WATER,
        WOOD,
        DARK,
        LIGHT,
        MAX,
    };
    
    CUnitNode();
    virtual ~CUnitNode();
    virtual bool init();
    virtual void pause();
    virtual void resume();
    
    virtual bool addDamage(CUnitNode* unit);
    virtual void heal(int iHeal);
    virtual void setHPmax(int iHPMax);
    
    
protected:
    virtual bool addDamage(int iDamage);
    
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);

    Vector<Label*> _vDamageLabelList;

    CC_SYNTHESIZE_READONLY(int, _iHPmax, HPmax);
    CC_SYNTHESIZE_READONLY(int ,_iHP,HP);

    CC_SYNTHESIZE(int, _iAttack, Attack);
    CC_SYNTHESIZE(Vec2, _vec2Movement, Movement);
    CC_SYNTHESIZE(eAttribute, _eAttribute, Attribute);
    
    void setColorReset(float dt);
    
    void popupLabel(std::string text,Color3B color);
};



#endif /* defined(__dackjabara__CUnitNode__) */
