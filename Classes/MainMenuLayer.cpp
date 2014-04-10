//
//  MainMenuLayer.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-6.
//
//

#include "MainMenuLayer.h"
#include "SimpleAudioEngine.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define BG_MUSIC        "Audio/music_1.ogg"
#else
#define BG_MUSIC        "Audio/music_1.mp3"
#endif // CC_PLATFOR_ANDROID

bool MainMenuLayer::init(){
	
	//Get the windows size
	auto winSize = Director::getInstance()->getWinSize();
	
	//Set the background picture
	auto ui_background = Sprite::create("MainMenu/ui_background_normal-hd.png");
	ui_background->setAnchorPoint(ccp(0.0f,0.0f));
	ui_background->setPosition(Point(0.0f,0.0f));
	addChild(ui_background,0.0f);
	
	//Set game logo
	auto ui_Logo = Sprite::create("MainMenu/main_ui_title_cn-hd.png");
	ui_Logo->setPosition(Point(winSize.width/2.0f, winSize.height/1.35f));
	addChild(ui_Logo,2);
	
	//Read the texture to sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/UI_GameMenuText_cn-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/UI_GameStartMenuLayer-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/FishActor-Small-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MainMenu/FishActor-Marlin-hd.plist");
	
	//Create the start button of the game
	auto startGameBtn = Sprite::createWithSpriteFrameName("ui_button_box02_02.png");
	auto startGameBtnPush = Sprite::createWithSpriteFrameName("ui_button_box02_01.png");
	auto startGameFont = Sprite::createWithSpriteFrameName("ui_2p_010.png");
	
	//Create the scene choose button
	auto sceneChooseBtn = Sprite::createWithSpriteFrameName("ui_button_box01_02.png");
	auto sceneChooseBtnPush = Sprite::createWithSpriteFrameName("ui_button_box01_01.png");
	auto sceneChooseFont = Sprite::createWithSpriteFrameName("button_other_014.png");
	
	//Create the menu
	auto startGameMenuItem = MenuItemSprite::create(startGameBtn, startGameBtnPush, CC_CALLBACK_1(MainMenuLayer::startGameEvent, this));
	auto sceneChooseMenuItem = MenuItemSprite::create(sceneChooseBtn, sceneChooseBtnPush, CC_CALLBACK_1(MainMenuLayer::sceneChoose, this));
	sceneChooseMenuItem->setPosition(Point(startGameMenuItem->getPosition().x, startGameMenuItem->getPosition().y-140));
	auto startGameMenu = Menu::create(startGameMenuItem, sceneChooseMenuItem, NULL);
	
	//Set the posiiton of menu
	startGameMenu->setPosition(Point(ui_Logo->getPosition().x, ui_Logo->getPosition().y-230));
	startGameFont->setPosition(Point(ui_Logo->getPosition().x, ui_Logo->getPosition().y-220));
	sceneChooseFont->setPosition(Point(ui_Logo->getPosition().x, ui_Logo->getPosition().y-370));
	
	//Add the menu into the scene
	addChild(startGameMenu,2);
	addChild(startGameFont,3);
	addChild(sceneChooseFont,3);
	
	//Create the bubble on the lower left corner
	auto paopaoLeft = createPaopao(Point(0,0));
	addChild(paopaoLeft,4);
	
	//Create the bubble on the lower right corner
	auto paopaoRight = createPaopao(Point(winSize.width, 0));
	addChild(paopaoRight,4);
		
	//Init the fishes
	fishActorsInital();
	
	unscheduleUpdate();
	
    /**Preload background music
       set default volume
	   Play background music.**/
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BG_MUSIC);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(BG_MUSIC, true);
	
	return true;
}

void MainMenuLayer::fishActorsInital(){
	
	//Get the window size
	auto winSize = Director::getInstance()->getWinSize();
	
	//Create fishes
	for (int fishIndex=0; fishIndex<7; fishIndex++) {//同种类鱼的条数

		auto smallFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		auto angelFishActor = FishActor::createWithType(FishActor::FishActorType::AngelFish);
		auto croakerFishActor = FishActor::createWithType(FishActor::FishActorType::Croaker);
		auto amphiprionFishActor = FishActor::createWithType(FishActor::FishActorType::Bream);
		auto breamFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		
		//Set the position of the fishes like a matrix
		smallFishActor->setPosition(Point(2000-winSize.width/10*(fishIndex+1),winSize.height-winSize.height/6));
		angelFishActor->setPosition(Point(2000-winSize.width/10*(fishIndex+1),winSize.height-winSize.height/6*2));
		croakerFishActor->setPosition(Point(2000-winSize.width/10*(fishIndex+1),winSize.height-winSize.height/6*3));
		amphiprionFishActor->setPosition(Point(2000-winSize.width/10*(fishIndex+1),winSize.height-winSize.height/6*4));
		breamFishActor->setPosition(Point(2000-winSize.width/10*(fishIndex+1),winSize.height-winSize.height/6*5));
		
		smallFishActor->runAction(createFishMoveAction(smallFishActor));
		angelFishActor->runAction(createFishMoveAction(angelFishActor));
		croakerFishActor->runAction(createFishMoveAction(croakerFishActor));
		amphiprionFishActor->runAction(createFishMoveAction(amphiprionFishActor));
		breamFishActor->runAction(createFishMoveAction(breamFishActor));

		
		//Add the fishes into the scene
		addChild(smallFishActor,1);
		addChild(angelFishActor,1);
		addChild(croakerFishActor,1);
		addChild(amphiprionFishActor,1);
		addChild(breamFishActor,1);
	}
	
	auto marlin = FishActor::createWithType(FishActor::FishActorType::MarlinsFish);
	marlin->setVisible(false);
	marlin->setPosition(Point(1000, winSize.height/2));
	marlin->runAction(MainMenuLayer::createMarlinMoveAction((MarlinsFishActor*)marlin));
	addChild(marlin, 1);
}

void MainMenuLayer::startGameEvent(Ref* sender){

	//Create the scene of FishingScene with a transtionFadeBL effect
	auto replaceScene = TransitionFadeBL::create(2, FishingScene::create());
	
	//Replace the scene with the trasition effect scene
	Director::getInstance()->replaceScene(replaceScene);
}

void MainMenuLayer::sceneChoose(Ref* sender){
		
}

ParticleSystemQuad* MainMenuLayer::createPaopao(Point position){
	
	//Create the paraticle of bubble
	auto paopao = ParticleSystemQuad::create("MainMenu/lizhi_qipao.plist");
	
	//Set the bubble position type form the ground
	paopao->setPositionType(ParticleSystemQuad::PositionType::RELATIVE);
	
	paopao->setPosition(position);
	paopao->setScale(2.0f);
	
	return paopao;
}

void MainMenuLayer::turnBack(Node* sender){
	
	if(sender->getRotation()==0.0f){
		
		sender->setRotation(180.00f);
	}else {
		
		sender->setRotation(0.00f);
	}
}

void MainMenuLayer::marlinTurnBack(Node *sender){
	
	if(sender->getRotation()==0.0f){
		
		sender->setVisible(true);
		sender->setRotation(180.00f);
	}else {
		
		sender->setVisible(false);
		sender->setRotation(0.00f);
	}
}

ActionInterval* MainMenuLayer::createFishMoveAction(FishActor *fish){
	
	//Let the matrix of fishes move back and forth
	return RepeatForever::create(
		Sequence::create(
		MoveTo::create(12, Point(fish->getPositionX()-1300, fish->getPositionY())),CallFunc::create(CC_CALLBACK_0(MainMenuLayer::turnBack,this,fish)),
		MoveTo::create(8,   Point(fish->getPositionX()+1000,fish->getPositionY())),CallFunc::create(CC_CALLBACK_0(MainMenuLayer::turnBack,this,fish)), NULL));
}

ActionInterval* MainMenuLayer::createMarlinMoveAction(MarlinsFishActor *fish){
	
	//Let the marlin fis move behind the matrix of fishes
	return RepeatForever::create(
		Sequence::create(
		MoveTo::create(12, Point(fish->getPositionX()-1300, fish->getPositionY())),CallFunc::create(CC_CALLBACK_0(MainMenuLayer::marlinTurnBack,this,fish)),
		MoveTo::create(8, Point(fish->getPositionX()+1000,fish->getPositionY())),CallFunc::create(CC_CALLBACK_0(MainMenuLayer::marlinTurnBack,this,fish)), NULL));
}