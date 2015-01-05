//
//  CUtil.h
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#ifndef __shootinggamePrototype__CUtil__
#define __shootinggamePrototype__CUtil__

#include <stdio.h>
#include "cocos2d.h"
#include <SimpleAudioEngine.h>
USING_NS_CC;
using namespace CocosDenshion;
class CUtil
{
public:
    
    static bool isHD();
    static std::string getHDSD();
    static std::string getHDSDname(std::string nameFormat);
    static Vec3 getRotate3D();
    
    static void setTMXTileMapAntialias(TMXTiledMap* tileMap);
    static Vec2 getCoordWithVec2(TMXTiledMap* tileMap, Vec2 vec);
};






#endif /* defined(__shootinggamePrototype__CUtil__) */
