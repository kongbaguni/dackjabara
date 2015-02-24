//
//  CUnitNode.cpp
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 8..
//
//

#include "CUnitNode.h"
#include "CUtil.h"
#include <vector>
CUnitNode::CUnitNode():
_pSprite(NULL),
_pTimer(NULL),
_pSpriteAttribute(NULL),
_pProgressTimer1(NULL),
_pProgressTimer2(NULL),
_iHPmax(30),
_iHP(30),
_iLevel(1),
_iExp(0),
_iAttack(1),
_vec2Movement(Vec2(0,0)),
_eAttribute(eAttribute::NONE),
_lLastDamagTime(0),
_pLabelLevel(NULL)
{
    _vDamageLabelList.clear();
    
}

CUnitNode::~CUnitNode()
{
    CC_SAFE_RELEASE_NULL(_pSprite);
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pSpriteAttribute);
    CC_SAFE_RELEASE_NULL(_pProgressTimer1);
    CC_SAFE_RELEASE_NULL(_pProgressTimer2);
    CC_SAFE_RELEASE_NULL(_pLabelLevel);

}

bool CUnitNode::init()
{
    if(!Node::init())
    {
        return false;
    }

    //기본 스프라이트 초기화
    {
        setSprite(Sprite::create());
        addChild(_pSprite);
    }
    
    //타이머 초기화
    {
        setTimer(CTimer::create());
    }

    //프로그레스바 초기화
    {
        auto progress = Sprite::createWithSpriteFrameName("unit/progressBarBG.png");
        getSprite()->addChild(progress);
        progress->setPosition(Vec2(58,0));
        
        setProgressTimer1(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar1.png")));
        setProgressTimer2(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar2.png")));
        
        ProgressTimer* progressList[2] =
        {
            _pProgressTimer1,_pProgressTimer2
        };
        
        for(int i=0; i<2; i++)
        {
            //progressList[i]->setPosition3D(Vec3(0,0,1));
            
            progressList[i]->setPercentage(0.0f);
            progressList[i]->runAction(ProgressTo::create(1.0f, 100));
            progressList[i]->setType(ProgressTimer::Type::BAR);
            progressList[i]->setMidpoint(Vec2(0.0f,0.0f));
            progressList[i]->setBarChangeRate(Vec2(1.0f,0.0f));
            progressList[i]->setAnchorPoint(Vec2(0.0f,0.0f));
            progress->addChild(progressList[i]);
        }
    }
    
    //속성 스프라이트 초기화
    {
        setSpriteAttribute(Sprite::createWithSpriteFrameName("unit/attribute.png"));
        getProgressTimer1()->getParent()->addChild(_pSpriteAttribute);
        _pSpriteAttribute->setPosition(Vec2(-15, 10));
        _pSpriteAttribute->runAction(RepeatForever::create(RotateBy::create(1.0f, 90.0f)));
    }
    //레벨표시 라벨 초기화
    {
        setLabelLevel(Label::createWithBMFont(CUtil::getFontName(CUtil::eFontList::OUTLINE_FONT_30), textUtil::addCommaText(_iLevel)));
        _pProgressTimer1->getParent()->addChild(_pLabelLevel);
        _pLabelLevel->setColor(Color3B::RED);
        _pLabelLevel->setPosition(Vec2(150,10));
        
    }
 
    setRotation3D(CUtil::getRotate3D());
    _iHP = _iHPmax;
    scheduleUpdate();

    return true;
}
void CUnitNode::update(float dt)
{
    Node::update(dt);
    setLocalZOrder(10000000-getPositionY());
}
void CUnitNode::setAttribute(CUnitNode::eAttribute attribute)
{
    _eAttribute = attribute;
    
    switch(_eAttribute)
    {
        case eAttribute::DARK:
            _color3bAttribute = Color3B(250, 0, 250);
            break;
        case eAttribute::LIGHT:
            _color3bAttribute = Color3B(255,255,0);
            break;
        case eAttribute::FIRE:
            _color3bAttribute = Color3B(255,0,0);
            break;
        case eAttribute::WATER:
            _color3bAttribute = Color3B(0,0,255);
            break;
        case eAttribute::WOOD:
            _color3bAttribute = Color3B(150,40,60);
            break;
        default:
            _color3bAttribute = Color3B(255,255,255);
            break;
    }
    _pSpriteAttribute->setColor(_color3bAttribute);
    
}

bool CUnitNode::addDamage(CUnitNode *unit)
{
    // 속성공격
    int iDamageSum = 1;
    eAttribute tAtt = unit->getAttribute();
    switch(_eAttribute)
    {
        case eAttribute::FIRE:
            if(tAtt== eAttribute::WATER)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::WATER:
            if(tAtt == eAttribute::WOOD)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::WOOD:
            if(tAtt == eAttribute::FIRE)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::DARK:
            if(tAtt == eAttribute::LIGHT)
            {
                iDamageSum = 2;
            }
            break;
        case eAttribute::LIGHT:
            if(tAtt == eAttribute::DARK)
            {
                iDamageSum = 2;
            }
            default:
            break;
    }
    
    int iDamage = unit->getAttack()*iDamageSum * (1.0+ unit->getLevel()*0.1f);
    if(addDamage(iDamage))
    {
        return true;
    }
    return false;
}

bool CUnitNode::addDamage(int iDamage)
{
    const long timeNow = timeUtil::millisecondNow();
    if(_lLastDamagTime>0 && timeNow-_lLastDamagTime<500)
    {
        return false;
    }
    _lLastDamagTime = timeNow;
    _iHP-=iDamage;
    if(_iHP<0)
    {
        _iHP = 0;
        return false;
    }
    _pSprite->setColor(Color3B(255, 0, 0));
    unschedule(schedule_selector(CUnitNode::setColorReset));
    scheduleOnce(schedule_selector(CUnitNode::setColorReset), 1.0f);
    
    std::string txt = textUtil::addCommaText(iDamage);
    txt+=" Point Damage";
    popupLabel(txt, Color3B(255,0,0));
    
    float p = (float)getHP()/(float)_iHPmax*100.0f;
    _pProgressTimer2->runAction(EaseExponentialInOut::create(ProgressTo::create(0.3f, p)));

    return true;
}

void CUnitNode::popupLabel(std::string text, cocos2d::Color3B color)
{
    if(_vDamageLabelList.size()>10)
    {
        auto first =_vDamageLabelList.front();
        removeChild(first);
        _vDamageLabelList.erase(_vDamageLabelList.begin());
    }
    
    auto labelDamage = Label::createWithBMFont(CUtil::getHDSDname("fonts/title2%s.fnt"), text);
    labelDamage->setColor(color);
    addChild(labelDamage);
    _vDamageLabelList.pushBack(labelDamage);
    labelDamage->runAction
    (Spawn::create
     (MoveBy::create(1.0f, Vec2(0, 100)),
      FadeOut::create(1.0f),
      NULL));
    
}
void CUnitNode::heal(int iHeal)
{
    if(_iHP<_iHPmax)
    {
        std::string txt = textUtil::addCommaText(iHeal);
        txt+=" Point Healing";
        popupLabel(txt,Color3B(50,250,150));
    }
    _iHP+=iHeal;
    if(_iHP>=_iHPmax)
    {
        _iHP = _iHPmax;
    }
}
void CUnitNode::setHPmax(int iHPMax)
{
    if(iHPMax>_iHPmax)
    {
        _iHP = iHPMax;
    }
    _iHPmax = iHPMax;
}


void CUnitNode::pause()
{
    Node::pause();
    _pSprite->pause();
    _pTimer->pause();
}

void CUnitNode::resume()
{
    Node::resume();
    _pSprite->resume();
    _pTimer->resume();
}

void CUnitNode::setColorReset(float dt)
{
    _pSprite->setColor(Color3B(255, 255, 255));
}


void CUnitNode::updateLabelLevel()
{
    std::string text = "LV ";
    text+=textUtil::addCommaText(_iLevel);
    _pLabelLevel->setString(text);
}

void CUnitNode::addExp(int exp)
{
    _iExp+=exp;
    updateLabelLevel();
    getLevel();
}

void CUnitNode::resetExp()
{
    _iExp=0;
    updateLabelLevel();
}


void CUnitNode::setLevel()
{
    const int MINEXP = 50;
    if(_iExp<MINEXP)
    {
        _iLevel = 1;
    }
    // x*e+x
    //exp -
    
    static int levelupTable[] =
    {
        50,
        100,
        150,
        200,
        250,
        300,
        350,
        400,
        450,
        500,
        550,
        600,
        650,
        700,
        750,
        800,
        850,
        900,
        950,
        1000,
        1500,
        2000,
        2500,
        3000,
        3500,
        4000,
        4500,
        5000,
        5500,
        6000,
        6500,
        7000,
        7500,
        8000,
        8500,
        9000,
        9500,
    };
    
    int tempExp = _iExp;
    int i = 0;
    while(tempExp>MINEXP && i<=sizeof(levelupTable)/sizeof(int64_t))
    {
        tempExp-=levelupTable[i];
        i++;
    }
    _iLevel = i;
}