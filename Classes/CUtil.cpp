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
