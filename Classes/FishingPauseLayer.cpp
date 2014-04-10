//
//  FishingPauseLayer.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-16.
//
//

#include "FishingPauseLayer.h"
using namespace cocos2d::ui;

bool FishingPauseLayer::init(){
	
	//Read the resources of CocoStudio json file
	auto pauseWidget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioRes/FishMiniPauseLayer_1/FishMiniPauseLayer_1.json"));
	
	//Get the buttons of continue button, main menu button, select button, setting button
	Button* continueBtn = dynamic_cast<Button*>(pauseWidget->getChildByName("ContinueBtn"));
	Button* mainMenuBtn = dynamic_cast<Button*>(pauseWidget->getChildByName("MainMenuBtn"));
	Button* selectBtn = dynamic_cast<Button*>(pauseWidget->getChildByName("SelectSceneBtn"));
	Button* settingBtn = dynamic_cast<Button*>(pauseWidget->getChildByName("SettingBtn"));
    
	//Add the touch event to each button
	continueBtn->addTouchEventListener(this, toucheventselector(FishingPauseLayer::continueEvent));
	mainMenuBtn->addTouchEventListener(this, toucheventselector(FishingPauseLayer::mainMenuEvent));
	selectBtn->addTouchEventListener(this, toucheventselector(FishingPauseLayer::selectEvent));
	settingBtn->addTouchEventListener(this, toucheventselector(FishingPauseLayer::settingEvent));
	
	addChild(pauseWidget,0);
	
	return true;
}

void FishingPauseLayer::continueEvent(Widget* target, TouchEventType type){
	
	if(type==TouchEventType::TOUCH_EVENT_ENDED){
        
		//Set the background to normal
		auto background = (Sprite*)(getParent()->getChildByTag(101)->getChildByTag(102));
		background->setTexture("CocoStudioRes/background.jpg");
		background->setScale(1.0f);
		background->setZOrder(-1.0f);
        
		//Resume all the action and touch events
		getParent()->getChildByTag(101)->onEnter();
        
		//Remove the pause layer and its children
		removeAllChildrenWithCleanup(true);
		removeFromParent();
	}
}

void FishingPauseLayer::selectEvent(Widget* target, TouchEventType type){
	
	
}

void FishingPauseLayer::mainMenuEvent(Widget* target, TouchEventType type){
	
	//back from the replace scene
	if(type==TouchEventType::TOUCH_EVENT_ENDED){
        
		auto replaceScene = TransitionFadeBL::create(2, MainMenuScene::create());
        
		Director::getInstance()->replaceScene(replaceScene);
	}
}

void FishingPauseLayer::settingEvent(Widget* target, TouchEventType type){
	
	
}