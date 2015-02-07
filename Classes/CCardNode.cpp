//
//  CCardNode.cpp
//  darkjabara
//
//  Created by kongbaguni on 2015. 2. 6..
//
//

#include "CCardNode.h"
#include <json/document.h>

USING_NS_CC_MATH;

CCardNode::CCardNode(int iID, int iExp, int iSkillExp, int iRareRating)
{
    _iID = iID;
    _iExp = iExp;
    _iSkillExp = iSkillExp;
    _iRareRating = iRareRating;
}

CCardNode::~CCardNode()
{
    
}
CCardNode* CCardNode::create(int iID, int iExp, int iSkillExp, int iRareRating)
{
    CCardNode* card = new (std::nothrow) CCardNode(iID,iExp,iSkillExp,iRareRating);
    if(card && card->init())
    {
        card->autorelease();
        return card;
    }
    CC_SAFE_RELEASE_NULL(card);
    return nullptr;
    
}
CCardNode* CCardNode::create(int iID)
{
    return CCardNode::create(iID, 0, 0, 0);
}

bool CCardNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }

    std::string name;
    std::string imageFrameName;
    {//cardList.json 에서 설정 읽어오기
        static rapidjson::Document doc;
        if(!doc.IsArray())
        {
            std::string jsonpath = FileUtils::getInstance()->fullPathForFilename("cardList.json");
            std::string contentStr = FileUtils::getInstance()->getStringFromFile(jsonpath);
            doc.Parse<0>(contentStr.c_str());
        }
        
        if(doc.IsArray())
        {
            if(doc[_iID]["name"].IsString());
            {
                name = doc[_iID]["name"].GetString();
            }
            if(doc[_iID]["imageFrameName"].IsString())
            {
                imageFrameName = doc[_iID]["imageFrameName"].GetString();
            }
            if(doc[_iID]["atteck"].IsInt())
            {
                setAttack(doc[_iID]["atteck"].GetInt());
            }
            if(doc[_iID]["hp"].IsInt())
            {
                setHPmax(doc[_iID]["hp"].GetInt());
            }
        }
    }
    
    getSprite()->setSpriteFrame(imageFrameName);
    

    
    return true;
}

int CCardNode::getLevel()
{
    return 1;
}

int CCardNode::getSkillLevel()
{
    return 1;
}

int CCardNode::getExpMax()
{
 
    return 100;
}

int CCardNode::getSkillExpMax()
{
    return 100;
}

bool CCardNode::syntheticCard(CCardNode *targetCard)
{
    int iExpMax = getExpMax();
    int iSkillExpMax = getSkillExpMax();
    if(targetCard==NULL)
    {
        return false;
    }
    
    int tRareRating = targetCard->getRareRating()^2;
    bool bExpUp = false;
    bool bSkillExpUp = false;
    if(_iExp<iExpMax)
    {
        _iExp+=targetCard->getSyntheticExp()*tRareRating;
        bExpUp = true;
    }
    else
    {
        _iExp = iExpMax;
    }
    
    if(_iID==targetCard->getID() && _iSkillExp < iSkillExpMax)
    {
        _iSkillExp+=(10*tRareRating);
        bSkillExpUp = true;
    }
    else
    {
        _iSkillExp = iSkillExpMax;
    }
    
    return bExpUp || bSkillExpUp;
}

bool CCardNode::syntheticCard(Vector<CCardNode *> cardList)
{
    for(auto card:cardList)
    {
        if(card==NULL)
        {
            return false;
        }
        syntheticCard(card);
    }
    
    return true;
}


bool CCardNode::evolutionCard(Vector<CCardNode *> cardList)
{
    for(auto card:cardList)
    {
        if(card==NULL)
        {
            return false;
        }
    }
    
    return true;
}

