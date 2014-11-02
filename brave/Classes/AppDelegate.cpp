#include "AppDelegate.h"
#include "MainScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    //Begin added by Wenbo Lin
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("AudioClip/Willow_and_the_Light.mp3");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("AudioClip/Willow_and_the_Light.mp3", true);
    //Ended added by Wenbo Lin
    
    // create a scene. it's an autorelease object
    Scene *scene = StartScene::createScene();

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

    //Begin added by Wenbo Lin
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("AudioClip/Willow_and_the_Light.mp3");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("AudioClip/Willow_and_the_Light.mp3", true);
    //Ended added by Wenbo Lin
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
