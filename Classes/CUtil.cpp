//
//  CUtil.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CUtil.h"

bool CUtil::isHD()
{
    auto size = Director::getInstance()->getInstance()->getWinSize();
    int sizeTotal = size.width * size.height;
    
    return sizeTotal >= 614400;
}

std::string CUtil::getHDSD()
{
    if(!CUtil::isHD())
    {
        return "-sd";
    }
    
    return "-hd";
}


std::string CUtil::getHDSDname(std::string nameFormat)
{
    auto str = String::createWithFormat(nameFormat.c_str(),getHDSD().c_str());
    return str->_string;
}

Vec3 CUtil::getRotate3D()
{
    return Vec3(90.0f, 0.0f, 0.0f);
}


void CUtil::setTMXTileMapAntialias(cocos2d::TMXTiledMap *tileMap)
{
    for (const auto& child : tileMap->getChildren())
    {
        static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
    }
}

Vec2 CUtil::getCoordWithVec2(cocos2d::TMXTiledMap *tileMap, cocos2d::Vec2 vec)
{
    Size size = tileMap->getContentSize();
    Size tileSzie = tileMap->getTileSize();
    
    int iY = size.height/tileSzie.height;
    int iXx = vec.x / tileSzie.width;
    int iYy = (vec.y / tileSzie.height);
    
    
    return Vec2(iXx,iY-iYy);
}

CUtil::sTMXcrashTestValue CUtil::isCrashWithTMXTileMapSetting(cocos2d::TMXTiledMap *tileMap, std::string layerName, std::string key, CUnitNode* node)
{
    return CUtil::isCrashWithTMXTileMapSetting(tileMap, layerName, key, node->getPosition(), node->getMovement());
}


CUtil::sTMXcrashTestValue CUtil::isCrashWithTMXTileMapSetting(cocos2d::TMXTiledMap *tileMap, std::string layerName, std::string key, Vec2 pos, Vec2 movement)

{
    sTMXcrashTestValue result;
    auto fixPos = CUtil::getCoordWithVec2(tileMap, pos);
    auto tileSize = tileMap->getMapSize();
    
    if(fixPos.x<0 | fixPos.y<0 | fixPos.x >= tileSize.width | fixPos.y >= tileSize.height)
    {
        result._bCrash = true;
        result._eCrashDirction = eDirection8::NOT_MOVE;
        result._pCrashTile = NULL;
        return result;
    }
    TMXLayer* layer= tileMap->getLayer(layerName);
    uint32_t iGid = layer->getTileGIDAt(fixPos);
    result._pCrashTile = layer->getTileAt(fixPos);
    auto properties = tileMap->getPropertiesForGID(iGid);
    
    if(properties.getType()==Value::Type::MAP && !properties.asValueMap().empty())
    {
        auto collision = properties.asValueMap()[key].asString();
        if("true"==collision)
        {
            result._bCrash = true;
        }
        result._iValue = properties.asValueMap()[key].asInt();
    }
    else
    {
        result._bCrash = false;
        result._eCrashDirction = eDirection8::NOT_MOVE;
        result._iValue = 0;
        
    }
    return result;

}
void CUtil::set3DHeightPosition(cocos2d::TMXTiledMap *tileMap, std::string layerName)
{
    auto layer = tileMap->getLayer("height");
    auto targetLayer = tileMap->getLayer(layerName);
    auto mapSize = tileMap->getMapSize();
    auto tileSize = tileMap->getTileSize();
    int count = 0;
    for(int x=0; x<mapSize.width; x++)
    {
        for(int y=0; y<mapSize.height; y++)
        {
            const Vec2 pos = Vec2(x,y);
            auto tile = targetLayer->getTileAt(pos);
            uint32_t gid = layer->getTileGIDAt(pos);
            tile->setLocalZOrder(100000-tile->getPositionY());

            count++;
            auto properties = tileMap->getPropertiesForGID(gid);
            if(properties.getType() == Value::Type::MAP && !properties.asValueMap().empty())
            {
                
                auto collision = properties.asValueMap()["height"].asInt();
                if(collision>0)
                {
                    
                    tile->setPosition3D(tile->getPosition3D()+Vec3(0, 0,collision));
                }
            }
        }
    }
    CCLOG("height setting : %d",count);
}

CUtil::eDirection8 CUtil::getMove8(cocos2d::Vec2 vec)
{
    float angle = vec.getAngle()*-57.3f+90.0f;
    if(vec.getLength()<10.0f)
    {
        return eDirection8::NOT_MOVE;
    }
    float a[] =
    {
        -22.5f-45.0f*2,
        -22.5f-45.0f,
        -22.5f,
        -22.5f+45.0f,
        -22.5f+45.0f*2,
        -22.5f+45.0f*3,
        -22.5f+45.0f*4,
        -22.5f+45.0f*5,
        -22.5f+45.0f*6,
        -22.5f+45.0f*7
    };
    if(a[0]<= angle && angle < a[1])
    {
        return eDirection8::RIGHT;
    }
    else if(a[1]<= angle && angle < a[2])
    {
        return eDirection8::UP_RIGHT;
    }
    else if(a[2]<= angle && angle < a[3])
    {
        return eDirection8::UP;
    }
    else if(a[3]<= angle && angle < a[4])
    {
        return eDirection8::UP_LEFT;
    }
    else if(a[4]<= angle && angle < a[5])
    {
        return eDirection8::LEFT;
    }
    else if(a[5]<= angle && angle < a[6])
    {
        return eDirection8::DOWN_LEFT;
    }
    else if(a[6]<= angle && angle < a[7])
    {
        return eDirection8::DOWN;
    }
    else if(a[7]<= angle && angle < a[8])
    {
        return eDirection8::DOWN_RIGHT;
    }
    else if(a[8]<= angle && angle < a[9])
    {
        return eDirection8::RIGHT;
    }
    return eDirection8::NOT_MOVE;
}

float CUtil::getMove8Rotate(cocos2d::Vec2 vec)
{
    eDirection8 d = getMove8(vec);
    int i = (int)d;
    i*=-45.0f;
    i-=(180.0f+45.0f) ;
    return i;
    
}
