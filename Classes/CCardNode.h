//
//  CCardNode.h
//  darkjabara
//
//  Created by kongbaguni on 2015. 2. 6..
//
//

#ifndef __darkjabara__CCardNode__
#define __darkjabara__CCardNode__

#include <stdio.h>
#include "CUnitNode.h"
class CCardNode : public CUnitNode
{
public:
    enum class skill
    {
        COMBO_RUSH,
        HEALING,
        CREATE_HEN,
        CREATE_COCK,        
    };
    enum class leaderSkill
    {
        HP_UP,
    };
    CCardNode(int iID, int iExp, int iSkillExp, int iRareRating);
    virtual ~CCardNode();
    virtual bool init();
    static CCardNode* create(int iID);
    static CCardNode* create(int iID, int iExp, int iSkillExp, int iRareRating);
    
    /** 카드의 레벨 구하기*/
    int getLevel();
    /** 카드 스킬레벨 구하기 */
    int getSkillLevel();
    /** 카드 합성하기 */
    bool syntheticCard(CCardNode* targetCard);
    /** 카드 여러개 합성하기*/
    bool syntheticCard(Vector<CCardNode*> cardList);
    /** 카드 진화 */
    bool evolutionCard(Vector<CCardNode*> cardList);
protected:
    CC_SYNTHESIZE_READONLY(int, _iID, ID);
    CC_SYNTHESIZE_READONLY(int, _iExp, Exp);
    CC_SYNTHESIZE_READONLY(int, _iSkillExp, SkillExp);
    CC_SYNTHESIZE_READONLY(int, _iSyntheticExp, SyntheticExp);
    CC_SYNTHESIZE(int, _iRareRating, RareRating)
    
    int getExpMax();
    int getSkillExpMax();
};

#endif /* defined(__darkjabara__CCardNode__) */
