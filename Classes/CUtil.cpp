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
    vec.y+=tileMap->getContentSize().height/2;
    Size size = tileMap->getContentSize();
    Size tileSzie = tileMap->getTileSize();
//    int iX = size.width/tileSzie.width;
    int iY = size.height/tileSzie.height;
    
    int iXx = vec.x / tileSzie.width;
    int iYy = vec.y / tileSzie.height;
    
    return Vec2(iXx,iY-iYy-1);
}

CUtil::movement8 CUtil::getMove8(cocos2d::Vec2 vec)
{
    float angle = vec.getAngle()*-57.3f+90.0f;
    if(vec.getLength()<10.0f)
    {
        return movement8::NOT_MOVE;
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
        return movement8::RIGHT;
    }
    else if(a[1]<= angle && angle < a[2])
    {
        return movement8::UP_RIGHT;
    }
    else if(a[2]<= angle && angle < a[3])
    {
        return movement8::UP;
    }
    else if(a[3]<= angle && angle < a[4])
    {
        return movement8::UP_LEFT;
    }
    else if(a[4]<= angle && angle < a[5])
    {
        return movement8::LEFT;
    }
    else if(a[5]<= angle && angle < a[6])
    {
        return movement8::DOWN_LEFT;
    }
    else if(a[6]<= angle && angle < a[7])
    {
        return movement8::DOWN;
    }
    else if(a[7]<= angle && angle < a[8])
    {
        return movement8::DOWN_RIGHT;
    }
    else if(a[8]<= angle && angle < a[9])
    {
        return movement8::RIGHT;
    }
    return movement8::NOT_MOVE;
}
