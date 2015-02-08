//
//  CAvatarUnitNode.h
//  darkjabara
//
//  Created by kongbaguni on 2015. 2. 6..
//
//

#ifndef __darkjabara__CAvatarUnitNode__
#define __darkjabara__CAvatarUnitNode__

#include <stdio.h>
#include "CUnitNode.h"
class CAvatarUnitNode : public CUnitNode
{
public:
    CAvatarUnitNode();
    virtual ~CAvatarUnitNode();
    CREATE_FUNC(CAvatarUnitNode);
    virtual bool init();
  
protected:
    CC_SYNTHESIZE_RETAIN(Label*, _pLabel, Label);
    
    
};

#endif /* defined(__darkjabara__CAvatarUnitNode__) */
