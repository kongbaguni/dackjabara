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
#include "CInlineFunctions.h"
#include "CRandom.h"

USING_NS_CC;
using namespace CocosDenshion;
class CUtil
{
public:
    enum class eDirection8
    {
        NOT_MOVE,
        LEFT,
        UP_LEFT,
        UP,
        UP_RIGHT,
        RIGHT,
        DOWN_RIGHT,
        DOWN,
        DOWN_LEFT,
    };
    static eDirection8 getMove8(Vec2 vec);
    
    enum class zorderList
    {
        BACKGROUND,
        GAME_FEALD,
        GAME_UI,
    };
    
    struct sTMXcrashTestValue
    {
        bool _bCrash;
        eDirection8 _eCrashDirction;
        
    };

    
    static bool isHD();
    static std::string getHDSD();
    static std::string getHDSDname(std::string nameFormat);
    static Vec3 getRotate3D();
    
    static void setTMXTileMapAntialias(TMXTiledMap* tileMap);
    static Vec2 getCoordWithVec2(TMXTiledMap* tileMap, Vec2 vec);
    static sTMXcrashTestValue isCrashWithTMXTileMapSetting(TMXTiledMap* tileMap,std::string layerName, std::string key, Node* node);
    
};






#endif /* defined(__shootinggamePrototype__CUtil__) */
