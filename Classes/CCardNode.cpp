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
CCardNode::CCardNode():
_iID(0),
_iExp(0),
_iSkillExp(0),
_iRareRating(1)
{
    
}


CCardNode::~CCardNode()
{
    
}

bool CCardNode::init()
{
    if(!CUnitNode::init())
    {
        return false;
    }
    
    

    
    return true;
}

void CCardNode::setId(int iId)
{
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
    
}
bool CCardNode::addExp(int iExp)
{
    _iExp+=iExp;
    return true;
}
bool CCardNode::addSkilExp(int iExp)
{
    _iSkillExp+=iExp;
    return  true;
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

