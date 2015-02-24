//
//  CNextTargetPrintNode.cpp
//  dackjabara
//
//  Created by kongbaguni on 2015. 1. 30..
//
//

#include "CNextTargetPrintNode.h"
#include "CGameManager.h"
#include "CRandom.h"
#include "CAnimationHelper.h"
CNextTargetPrintNode::CNextTargetPrintNode():
_pTargetChicken(NULL),
_pTimer(NULL),
_pProgressTimer(NULL),
_iCombo(0),
_pLabelCombo(NULL)
{
    _eNextTargetChickenState = CChikenNode::state::EGG;
    
}
CNextTargetPrintNode::~CNextTargetPrintNode()
{
    CC_SAFE_RELEASE_NULL(_pTargetChicken);
    CC_SAFE_RELEASE_NULL(_pTimer);
    CC_SAFE_RELEASE_NULL(_pProgressTimer);
    CC_SAFE_RELEASE_NULL(_pLabelCombo);
    
}
void CNextTargetPrintNode::reset()
{
    _iCombo = 0;
    _eNextTargetChickenState = CChikenNode::state::EGG;
    changePictureWithNextState();
    _pTimer->stop();
}
bool CNextTargetPrintNode::init()
{
    if(!Node::init())
    {
        return false;
    }
    
    CAnimationHelper::addAnimation("UI/nextTarget_%02d.png", 1, 3, "nextTargetBubble");

    auto bg = Sprite::createWithSpriteFrameName("UI/nextTarget_01.png");
    bg->runAction
    (RepeatForever::create(
     Animate::create(AnimationCache::getInstance()->getAnimation("nextTargetBubble"))));
    addChild(bg);
    bg->setScale(0.5f);
    bg->setPosition(Vec2(-20, 100));
    setTargetChicken(Sprite::createWithSpriteFrameName("unit/egg.png"));
    _pTargetChicken->setPosition(Vec2(100,100));
    bg->addChild(_pTargetChicken);
    _pTargetChicken->runAction
    (RepeatForever::create
     (Sequence::create
      (EaseExponentialInOut::create(RotateTo::create(1.0f, -10.0f)),
       EaseExponentialInOut::create(RotateTo::create(1.0f, 10.0f)),
       NULL)));
    
    auto pBg = Sprite::createWithSpriteFrameName("unit/progressBar2.png");
    pBg->setColor(Color3B(255, 0, 0));
    setProgressTimer(ProgressTimer::create(Sprite::createWithSpriteFrameName("unit/progressBar2.png")));
    
    _pProgressTimer->setPercentage(1.0f);
    _pProgressTimer->setType(ProgressTimer::Type::BAR);
    _pProgressTimer->setMidpoint(Vec2(0.0f,0.0f));
    _pProgressTimer->setBarChangeRate(Vec2(1.0f,0.0f));
    _pProgressTimer->setAnchorPoint(Vec2(0.0f,0.0f));
    pBg->addChild(_pProgressTimer);
    bg->addChild(pBg);
    pBg->setPosition(Vec2(100, 45));
    pBg->setScale(0.4f, 1.0f);
    pBg->setOpacity(100);
    
    setTimer(CTimer::create());
    _pTimer->setMaxTime(5000);
    
    setLabelCombo(Label::createWithBMFont(CUtil::getHDSDname("fonts/digital%s.fnt"), "0"));
    bg->addChild(_pLabelCombo);
    _pLabelCombo->setPosition(Vec2(80,130));
    _pLabelCombo->setScale(0.5f);
    

    scheduleUpdate();
    
    return true;
}

void CNextTargetPrintNode::onEnter()
{
    Node::onEnter();
    _pTimer->start();
    
}
void CNextTargetPrintNode::updateComboLabel()
{
    std::string txt = textUtil::addCommaText(_iCombo);
    txt+=" COMBO";
    _pLabelCombo->setString(txt);
}
void CNextTargetPrintNode::update(float dt)
{

    setVisible(!CGameManager::getInstance()->getIsGameOver());
    updateComboLabel();
    _pProgressTimer->setPercentage((float)_pTimer->getTime()/(float)_pTimer->getMaxTime()*100.0f);
    auto mainTimer = CGameManager::getInstance()->getMainTimerNode()->getTimer();
    if(mainTimer->isPause())
    {
        _pTimer->pause();
    }
    else
    {
        _pTimer->resume();
    }
    if(_pTimer->getTime()==0)
    {
        changeNextTarget();
        changePictureWithNextState();
        _pTimer->start();
        _iCombo*=0.5f;
    }
}
void CNextTargetPrintNode::pause()
{
    Node::pause();
    _pTimer->pause();
}
void CNextTargetPrintNode::resume()
{
    Node::resume();
    _pTimer->resume();
}

void CNextTargetPrintNode::changeNextTarget()
{
    Vector<Node*> vec = CGameManager::getInstance()->getGameField()->getChildren();
    for(auto unit : vec)
    {
        int a = CRandom::getInstnace()->Random(6);
        if(unit->getTag()==(int) CUtil::unitTag::UNIT_CHICKEN && unit!=CGameManager::getInstance()->getPlayerNode() && a == 0)
        {
            _eNextTargetChickenState = ((CChikenNode*)unit)->getState();
            break;
        }
    }
    
}

void CNextTargetPrintNode::catchChicken(CChikenNode *chicken)
{
    if(chicken->getState()==_eNextTargetChickenState)
    {
        changeNextTarget();
        _pTimer->start();
        _iCombo++;
        updateComboLabel();
        changePictureWithNextState();
    }
}
void CNextTargetPrintNode::changePictureWithNextState()
{
    std::string filename = "unit/";
    switch(_eNextTargetChickenState)
    {
        case CChikenNode::state::CHICK:
            filename+="chick";
            break;
        case CChikenNode::state::CHICK_DEAD:
            filename+="chickDead";
            break;
        case CChikenNode::state::COCK:
            filename+="cock";
            break;
        case CChikenNode::state::EGG:
            filename+="egg";
            break;
        case CChikenNode::state::EGG_BROKEN:
            filename+="eggBroken";
            break;
        case CChikenNode::state::HEN:
            filename+="hen";
            break;
        default:
            return;
    }
    filename+=".png";
    _pTargetChicken->setSpriteFrame(filename);
  //  _pTargetChicken->runAction(JumpBy::create(0.3f, Vec2::ZERO, 100, 1));
}
