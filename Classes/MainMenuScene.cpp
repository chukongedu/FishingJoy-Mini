//
//  MainMenuScene.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-6.
//
//

#include "MainMenuScene.h"
#include "MainMenuLayer.h"

bool MainMenuScene::init(){

	//Init the main menu layer
	MainMenuLayer* mainMenuLyaer = MainMenuLayer::create();
	
	//Add the main menu layer to the scene
	addChild(mainMenuLyaer,10);
	
	return true;
}
