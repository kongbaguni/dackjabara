//
//  CGameScene.cpp
//  shootinggamePrototype
//
//  Created by SeoChangyul on 2015. 1. 2..
//
//

#include "CGameScene.h"
#include "CPlayerCharacterNode.h"
#include "CUtil.h"
#include "CGameManager.h"
#include "CChikenNode.h"

bool CGameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }

    Size winsize = Director::getInstance()->getWinSize();
    
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/01 A Night Of Dizzy Spells.mp3",true);
    auto colorBg1 = LayerGradient::create(Color4B(30, 70, 200, 255), Color4B(255,255,255,255));
    float h = colorBg1->getContentSize().height;
    colorBg1->setVector(Vec2(0,-h/4));
    addChild(colorBg1);
    colorBg1->setRotation3D(Vec3(0,0,0));
    colorBg1->setPosition3D(Vec3(-winsize.width*5,0,-50));
    colorBg1->setContentSize(Size(winsize.width*1000, winsize.height));
    
    auto colorBg = LayerColor::create(Color4B(255, 255, 255, 255));
    addChild(colorBg);
    colorBg->setRotation3D(Vec3(-90,0,0));
    colorBg->setPosition3D(Vec3(-winsize.width*5,-50,-50));
    colorBg->setContentSize(winsize*1000);
    
//    배경 레이어 초기화
    auto gameFeald = Layer::create();
    Vec3 r = CUtil::getRotate3D();
    gameFeald->setRotation3D(Vec3(-r.x, 0, 0));
    gameFeald->setPosition(Vec2(0.0f, 200.0f));
    addChild(gameFeald,(int)CUtil::zorderList::GAME_FEALD);
    
//    타일맵 초기화
    auto tileMap = TMXTiledMap::create("tilemap/map.tmx");
    CGameManager::getInstance()->setTileMap(tileMap);
    
    tileMap->setPosition(Vec2(0,-winsize.height/2));
    tileMap->setPosition3D(Vec3(0.0f, tileMap->getContentSize().height/3, winsize.height/2));
    tileMap->setRotation3D(Vec3(-90, 0, 0));
   CUtil::setTMXTileMapAntialias(tileMap);
    addChild(tileMap,(int)CUtil::zorderList::BACKGROUND);
    
    
  
    auto bgBack =TMXTiledMap::create("tilemap/map4.tmx");
    bgBack->setPosition3D(Vec3(0, tileMap->getContentSize().height,0));
    bgBack->setRotation3D(Vec3(90,0,0));
    tileMap->addChild(bgBack);
    
    auto bgLeft =TMXTiledMap::create("tilemap/map3.tmx");
    bgLeft->setPosition3D(Vec3(0,0,bgLeft->getContentSize().width));
    bgLeft->setRotation3D(Vec3(0, 90, 0));
   // CUtil::setTMXTileMapAntialias(bgLeft);
    tileMap->addChild(bgLeft);
    
    auto bgRight =TMXTiledMap::create("tilemap/map3.tmx");
    bgRight->setPosition3D(Vec3(tileMap->getContentSize().width,0,bgRight->getContentSize().width));
    bgRight->setRotation3D(Vec3(0, 90, 0));
//    CUtil::setTMXTileMapAntialias(bgRight);
    tileMap->addChild(bgRight);
  
    auto bgTop = TMXTiledMap::create("tilemap/map2.tmx");
    bgTop->setPosition3D(Vec3(0, 0, winsize.height/2));
    tileMap->addChild(bgTop);
   CUtil::setTMXTileMapAntialias(bgTop);
    
    
    
//    리소스 로딩
    std::string fileName = CUtil::getHDSDname("texturePacker/unit%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);


    //닭 집어넣기
    for(int i=0; i<10; i++)
    {
        float tw = tileMap->getContentSize().width/2;
        float th = tileMap->getContentSize().height/2;
        int x = CRandom::getInstnace()->Random(tw-50)+25;
        int y = CRandom::getInstnace()->Random(th) - th/2;
        
        auto chicken = CChikenNode::create();
        chicken->setPosition(x,y);
        gameFeald->addChild(chicken,(int)CUtil::zorderList::BACKGROUND);
        //        chicken->setScale(1.0f);
    }

    
    //    플레이어 초기화
    
    auto player = CPlayerCharacterNode::create();
    if(player)
    {
        player->setPosition(winsize.width/2,10);
        player->getSprite()->setScale(0.5f);
        gameFeald->addChild(player);
        CGameManager::getInstance()->setPlayerNode(player);
    }
    
    
//    게임매니져 붙이기
    addChild(CGameManager::getInstance(),(int)CUtil::zorderList::GAME_UI,(int)CUtil::zorderList::GAME_UI);
    CGameManager::getInstance()->setGameField(gameFeald);
    
    
    
    
    
    return true;
}