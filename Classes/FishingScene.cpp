//
//  FishingScene.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "FishingScene.h"

bool FishingScene::init(){
	
	auto fishingLayer = FishingLayer::create();
	addChild(fishingLayer,0);
	
	return true;
}