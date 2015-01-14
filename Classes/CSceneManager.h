//
//  CSceneManager.h
//  dackjabara
//
//  Created by SeoChangyul on 2015. 1. 11..
//
//

#ifndef __dackjabara__CSceneManager__
#define __dackjabara__CSceneManager__

#include <stdio.h>
#include "CUtil.h"
#include <map>
class CSceneManager
{
public:
    static CSceneManager* getInstance();
    CSceneManager();
    ~CSceneManager();
    
    void addScene(Scene* scene, std::string key);
    Scene* getScene (std::string key);
    
protected:
    std::map<std::string,Scene*> _mapScene;
};

#endif /* defined(__dackjabara__CSceneManager__) */
