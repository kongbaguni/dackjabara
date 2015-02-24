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
    virtual void update(float dt);
    
    virtual bool addDamage(CUnitNode* unit);
    virtual void heal(int iHeal);
    virtual void setHPmax(int iHPMax);
    
    /**속성 설정하기 */
    void setAttribute(eAttribute attribute);
    
    virtual void addExp(int exp);
    void resetExp();
    
protected:
    void setLevel();
    virtual bool addDamage(int iDamage);
    
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSprite, Sprite);
    CC_SYNTHESIZE_RETAIN(Sprite*, _pSpriteAttribute, SpriteAttribute);
    CC_SYNTHESIZE_RETAIN(CTimer*, _pTimer, Timer);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer1, ProgressTimer1);
    CC_SYNTHESIZE_RETAIN(ProgressTimer*, _pProgressTimer2, ProgressTimer2);
    CC_SYNTHESIZE_RETAIN(Label*, _pLabelLevel, LabelLevel);
    
    
    Vector<Label*> _vDamageLabelList;

    CC_SYNTHESIZE_READONLY(int, _iHPmax, HPmax);
    CC_SYNTHESIZE_READONLY(int ,_iHP,HP);

    CC_SYNTHESIZE(int, _iAttack, Attack);
    CC_SYNTHESIZE(Vec2, _vec2Movement, Movement);
    
    CC_SYNTHESIZE_READONLY(eAttribute, _eAttribute, Attribute);
    CC_SYNTHESIZE_READONLY(Color3B, _color3bAttribute, AttributeColor);

    
    CC_SYNTHESIZE_READONLY(int ,_iExp,Exp);
    CC_SYNTHESIZE_READONLY(int, _iLevel, Level);
    void setColorReset(float dt);
    
    void popupLabel(std::string text,Color3B color);
    long _lLastDamagTime;
    
    void updateLabelLevel();
};



#endif /* defined(__dackjabara__CUnitNode__) */
