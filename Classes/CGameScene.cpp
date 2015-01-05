//
//  CGameScene.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CGameScene.h"
#include "CPlayerSprite.h"
#include "CUtil.h"
#include "CGameManager.h"

bool CGameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }
    Size winsize = Director::getInstance()->getWinSize();
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/01 A Night Of Dizzy Spells.mp3",true);
    
//    배경 레이어 초기화
    auto bg = Layer::create();
    Vec3 r = CUtil::getRotate3D();
    bg->setRotation3D(Vec3(-r.x, 0, 0));
    bg->setPosition(Vec2(0.0f, 200.0f));
    addChild(bg);
    
//    타일맵 초기화
    auto tileMap = TMXTiledMap::create("tilemap/map.tmx");
    CGameManager::getInstance()->setTileMap(tileMap);
    
    tileMap->setPosition(Vec2(0,-winsize.height/2));
    tileMap->setPosition3D(Vec3(0.0f, -tileMap->getContentSize().height/2, 0.0f));
    CUtil::setTMXTileMapAntialias(tileMap);
    bg->addChild(tileMap);
    
  
    auto bgBack =TMXTiledMap::create("tilemap/map2.tmx");
    bgBack->setPosition3D(Vec3(0, tileMap->getContentSize().height,0));
    bgBack->setRotation3D(Vec3(90,0,0));
    tileMap->addChild(bgBack);
    
    auto bgLeft =TMXTiledMap::create("tilemap/map2.tmx");
    bgLeft->setPosition3D(Vec3(0,0,bgLeft->getContentSize().width));
    bgLeft->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgLeft);
    tileMap->addChild(bgLeft);
    
    auto bgRight =TMXTiledMap::create("tilemap/map2.tmx");
    bgRight->setPosition3D(Vec3(tileMap->getContentSize().width,0,bgRight->getContentSize().width));
    bgRight->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgRight);
    tileMap->addChild(bgRight);
  
    auto bgTop = TMXTiledMap::create("tilemap/map2.tmx");
    bgTop->setPosition3D(Vec3(0, 0, winsize.height/2));
    tileMap->addChild(bgTop);
    CUtil::setTMXTileMapAntialias(bgTop);
    
    
//    게임매니져 붙이기
    addChild(CGameManager::getInstance());
    
//    리소스 로딩
    std::string fileName = CUtil::getHDSDname("texturePacker/unit%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);

//    플레이어 초기화
    auto player = CPlayerSprite::create();
    player->setPosition(winsize.width/2,10);
    bg->addChild(player);
    CGameManager::getInstance()->setPlayerSprite(player);
    
    
    return true;
}