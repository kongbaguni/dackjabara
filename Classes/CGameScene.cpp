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
    
    
    auto colorBg1 = LayerGradient::create(Color4B(30, 70, 200, 255), Color4B(255,255,255,255));
    float h = colorBg1->getContentSize().height;
    colorBg1->setVector(Vec2(0,-h/4));
    addChild(colorBg1);
    colorBg1->setRotation3D(Vec3(0,0,0));
    colorBg1->setPosition3D(Vec3(-winsize.width*5,-120,-1550));
    colorBg1->setContentSize(Size(winsize.width*1000, winsize.height*2));
    
    auto colorBg = LayerColor::create(Color4B(100, 150, 255, 255));
    addChild(colorBg);
    colorBg->setRotation3D(Vec3(-90,0,0));
    colorBg->setPosition3D(Vec3(-winsize.width*5,-150,-50));
    colorBg->setContentSize(winsize*10000);
    
//    배경 레이어 초기화
    
//    타일맵 초기화
    auto tileMap = TMXTiledMap::create("tilemap/map.tmx");
    CGameManager::getInstance()->setGameField(tileMap);
 //   tileMap->setPosition(Vec2(0.0f,-winsize.height/2));
//    tileMap->setPosition3D(Vec3(0.0f, winsize.height/5, tileMap->getContentSize().height*0.25f));
    tileMap->setRotation3D(Vec3(-90, 0, 0));
   CUtil::setTMXTileMapAntialias(tileMap);
    addChild(tileMap,(int)CUtil::zorderList::BACKGROUND);
    

    auto bgBack2 =TMXTiledMap::create("tilemap/map5.tmx");
    bgBack2->setPosition3D(Vec3(0, tileMap->getContentSize().height*2,0));
    bgBack2->setRotation3D(Vec3(90,0,0));
    CUtil::setTMXTileMapAntialias(bgBack2);
    tileMap->addChild(bgBack2);

    auto bgLeft2 =TMXTiledMap::create("tilemap/map3.tmx");
    bgLeft2->setPosition3D(Vec3(0,bgLeft2->getContentSize().height,bgLeft2->getContentSize().width));
    bgLeft2->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgLeft2);
    tileMap->addChild(bgLeft2);
    
    auto bgRight2 =TMXTiledMap::create("tilemap/map3.tmx");
    bgRight2->setPosition3D(Vec3(tileMap->getContentSize().width,bgRight2->getContentSize().height,bgRight2->getContentSize().width));
    bgRight2->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgRight2);
    tileMap->addChild(bgRight2);


    auto bgBack =TMXTiledMap::create("tilemap/map4.tmx");
    bgBack->setPosition3D(Vec3(0, tileMap->getContentSize().height,0));
    bgBack->setRotation3D(Vec3(90,0,0));
    CUtil::setTMXTileMapAntialias(bgBack);
    tileMap->addChild(bgBack);
    
    
    
    auto bgLeft =TMXTiledMap::create("tilemap/map3.tmx");
    bgLeft->setPosition3D(Vec3(0,0,bgLeft->getContentSize().width));
    bgLeft->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgLeft);
    tileMap->addChild(bgLeft);
    
    auto bgRight =TMXTiledMap::create("tilemap/map3.tmx");
    bgRight->setPosition3D(Vec3(tileMap->getContentSize().width,0,bgRight->getContentSize().width));
    bgRight->setRotation3D(Vec3(0, 90, 0));
    CUtil::setTMXTileMapAntialias(bgRight);
    tileMap->addChild(bgRight);
  
    auto bgTop = TMXTiledMap::create("tilemap/map2.tmx");
    bgTop->setPosition3D(Vec3(0, 0, winsize.height/2));
    tileMap->addChild(bgTop);
   CUtil::setTMXTileMapAntialias(bgTop);
    
    
    
//    리소스 로딩
    std::string fileName = CUtil::getHDSDname("texturePacker/game%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);


    //닭 집어넣기



    //    게임매니져 붙이기
    CGameManager::getInstance()->setGameField(tileMap);

    //    플레이어 초기화
    makePlayer();
    
    
    
    
    
    
    return true;
}

void CGameScene::makePlayer()
{
    auto player = CPlayerCharacterNode::create();
    if(player)
    {
        Size winsize = Director::getInstance()->getWinSize();
        player->setPosition(winsize.width/2,100);
        player->getSprite()->setScale(0.5f);
        CGameManager::getInstance()->getGameField()->addChild(player,(int)CUtil::unitTag::UNIT_PLAYER,(int)CUtil::unitTag::UNIT_PLAYER);
        CGameManager::getInstance()->setPlayerNode(player);
    }
    
}

CGameScene::CGameScene()
{
    
}
CGameScene::~CGameScene()
{
 //   removeChild(CGameManager::getInstance());
}

void CGameScene::onEnter()
{
    Scene::onEnter();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM/01 A Night Of Dizzy Spells.mp3",true);
    CGameManager::getInstance()->getMainTimerNode()->getTimer()->resume();
    
    addChild(CGameManager::getInstance(),(int)CUtil::zorderList::GAME_UI_Back,(int)CUtil::zorderList::GAME_UI_Back);
    CGameManager::getInstance()->getMainTimerNode()->scheduleUpdate();
    CGameManager::getInstance()->getMainTimerNode()->getTimer()->resume();
    if(CGameManager::getInstance()->getPlayerNode()==NULL)
    {
        makePlayer();
    }
    
}
void CGameScene::onExit()
{
    Scene::onExit();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->stopAllEffects();
    removeChild(CGameManager::getInstance());
    CGameManager::getInstance()->getMainTimerNode()->getTimer()->pause();

}