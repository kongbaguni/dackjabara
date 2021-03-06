#include "AppDelegate.h"

#include "CTitleScene.h"
#include "CGameScene.h"
#include "CGameResultScene.h"
#include "CHomeScene.h"

#include "CSceneManager.h"
#include "CGameManager.h"
#include "CPauseScene.h"
#include "CUtil.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("cocio");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);
    
    bool bHD = CUtil::isHD();
    if(!bHD)
    {
        glview->setDesignResolutionSize(320, 480, ResolutionPolicy::FIXED_HEIGHT);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    
    //    리소스 로딩
    std::string fileName = CUtil::getHDSDname("texturePacker/home%s.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(fileName);

    // create a scene. it's an autorelease object

    CSceneManager::getInstance()->addScene(CTitleScene::create(), "title");
    CSceneManager::getInstance()->addScene(CGameScene::create(), "game");
    CSceneManager::getInstance()->addScene(CPauseScene::create(), "pause");
    CSceneManager::getInstance()->addScene(CGameResultScene::create(), "gameResult");
    CSceneManager::getInstance()->addScene(CHomeScene::create(), "home");

    auto scene = CSceneManager::getInstance()->getScene("title");


    // run
    director->runWithScene(scene);


    
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
