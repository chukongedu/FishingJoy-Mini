//
//  FishingLayer.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#include "FishingLayer.h"

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SOUND_COIN        "Audio/sound_coin.ogg"
#else
#define SOUND_COIN        "Audio/sound_coin.mp3"
#endif // CC_PLATFOR_ANDROID

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define SOUND_FIRE        "Audio/sound_fire.ogg"
#else
#define SOUND_FIRE        "Audio/sound_fire.mp3"
#endif // CC_PLATFOR_ANDROID

bool FishingLayer::init(){
    
	musicTurnOff=true;
	Layer::init();
	_bullet=NULL;
    
    //Set tag of the layer, and get it in pause layer
    setTag(101);
	
	//Add background picture
	auto background = Sprite::create("CocoStudioRes/background.jpg");
	background->setAnchorPoint(Point(0,0));
	background->setPosition(Point(0,0));
	background->setTag(102);
	addChild(background,0);
	
	//Read the resources of CocoStudio json file, and add it to the scene
	widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioRes/FishJoyMini_1.json"));
	addChild(widget,2);
    
	//Read the texture to sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/cannon-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("GameScene/Item-chaojiwuqi-iphone-hd.plist");
	
	//Get the instantce of ui_box_01_01 and make it rotate forever
	auto ui_box_01_01 = dynamic_cast<ImageView*>(widget->getChildByName("ui_box_01_01"));
	ui_box_01_01->runAction(RepeatForever::create((RotateBy::create(3, 360, 360))));
	
	//Get the instance of label of score
	scoreLabel = dynamic_cast<TextAtlas*>(widget->getChildByName("Score"));
	score = 0;
	
	//Get the instance of cannon
	cannon = dynamic_cast<ImageView*>(widget->getChildByName("cannon"));
	
	//Set the touch event enable
	widget->setTouchEnabled(true);
	
	//Add the touch event callback function
	widget->addTouchEventListener(this, toucheventselector(FishingLayer::shootEvent));
	
	//Get the pause buton and its touch event callback function
	auto pauseBtn = dynamic_cast<Button*>(widget->getChildByName("pauseBtn"));
	pauseBtn->addTouchEventListener(this, toucheventselector(FishingLayer::pauseEvent));
    
	//turn on the background music
	auto turnOnMusicBtn= dynamic_cast<ImageView *>(widget->getChildByName("ImageView_42"));
	turnOnMusicBtn->addTouchEventListener(this,toucheventselector(FishingLayer::turnOnMusic));
	//turn off the background music
	auto turnOffMusicBtn= dynamic_cast<Button *>(widget->getChildByName("music"));
	turnOffMusicBtn->addTouchEventListener(this,toucheventselector(FishingLayer::turnOffMusic));
    
	//addChild(turnOffMusicBtn,1,99);
	//Activate update
	scheduleUpdate();
	
	//Init the fishes
	fishActorsInital();
	
	//Update the fishes one time
	updateFishMovement();
	
	//Preload background effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_COIN);
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_FIRE);
	
	return true;
}

void FishingLayer::shootEvent(Widget* target,TouchEventType type){
	
	if(type == TouchEventType::TOUCH_EVENT_BEGAN){
        
		//Change the texture of the cannot at the beginning of touch to make it more real
		cannon->loadTexture("actor_cannon1_72.png", UI_TEX_TYPE_PLIST);
		
	}else if(type == TouchEventType::TOUCH_EVENT_ENDED){
		
		//Change back the texture of the cannon at the end of the touch event
		cannon->loadTexture("actor_cannon1_71.png", UI_TEX_TYPE_PLIST);
		
		//Change the cannon rotation
		FishingLayer::setCannonRotation(target,target->getTouchEndPos());
		
		//Shoot the bullet
		bulletEndPosition=target->getTouchEndPos();
		bulletShoot(target->getTouchEndPos());
		
		
	}else if(type == TouchEventType::TOUCH_EVENT_MOVED){
        
		//Change the cannon ratation
		FishingLayer::setCannonRotation(target, target->getTouchMovePos());
	}
}

void FishingLayer::bulletShoot(Point endPosition){
	
	if(_bullet==NULL){
		
		//Init the bullet
		auto bullet = Sprite::createWithSpriteFrameName("weapon_bullet_007.png");
		auto netFish=SpriteBatchNode::create("GameScene/bullet10-hd.png",5);
		//addChild(netFish,1);
		
        net=Sprite::createWithTexture(netFish->getTexture(),Rect(0,0,80,80));
        net1=Sprite::createWithTexture(netFish->getTexture(),Rect(0,0,80,80));
        net2=Sprite::createWithTexture(netFish->getTexture(),Rect(0,0,80,80));
        net3=Sprite::createWithTexture(netFish->getTexture(),Rect(0,0,80,80));
        
        net1->setRotation(90.0f);
        net2->setRotation(180.0f);
        net3->setRotation(270.0f);
		
		float shifting;
        
		//Set the offest of the raotation
		if(cannon->getRotation()<=0){
			
			shifting = 20.0f;
		}else{
			
			shifting = -20.0f;
		}
		
		//Set the anchorpoint, rotation, position of the bullet
		_bullet = bullet;
		_bullet->setAnchorPoint(Point(0.5, 0.5));
		_bullet->setRotation(cannon->getRotation());
		_bullet->setPosition(Point(cannon->getPosition().x-shifting, cannon->getPosition().y+20));
        
		auto scale0=ScaleTo::create(0.5,0.3);
		auto scale1=ScaleTo::create(0.5,0.1);
		auto scale2=ScaleTo::create(0.5,0.35);
		auto scale3=ScaleTo::create(0.5,0.15);
		auto scale4=ScaleTo::create(0.1,0);
		auto scale00=ScaleTo::create(0.5,0.3);
		auto scale01=ScaleTo::create(0.5,0.1);
		auto scale02=ScaleTo::create(0.5,0.35);
		auto scale03=ScaleTo::create(0.5,0.15);
		auto scale04=ScaleTo::create(0.1,0);
		auto scale000=ScaleTo::create(0.5,0.3);
		auto scale001=ScaleTo::create(0.5,0.1);
		auto scale002=ScaleTo::create(0.5,0.35);
		auto scale003=ScaleTo::create(0.5,0.15);
		auto scale004=ScaleTo::create(0.1,0);
		auto scale0000=ScaleTo::create(0.5,0.3);
		auto scale0001=ScaleTo::create(0.5,0.1);
		auto scale0002=ScaleTo::create(0.5,0.35);
		auto scale0003=ScaleTo::create(0.5,0.15);
		auto scale0004=ScaleTo::create(0.1,0);
		net->setAnchorPoint(Point(0, 0));
		net1->setAnchorPoint(Point(0, 0));
		net2->setAnchorPoint(Point(0, 0));
		net3->setAnchorPoint(Point(0, 0));
		
		//Shoot the bullet and release after the action ended
		_bullet->runAction(Sequence::create(MoveTo::create(1, endPosition),
											CallFunc::create(CC_CALLBACK_0(FishingLayer::bulletRelease,this)),
											NULL));
		addChild(_bullet,1);
		net->runAction(Sequence::create(scale0,scale1,scale2,scale3,scale4,NULL));
		net1->runAction(Sequence::create(scale00,scale01,scale02,scale03,scale04,NULL));
		net2->runAction(Sequence::create(scale000,scale001,scale002,scale003,scale004,NULL));
		net3->runAction(Sequence::create(scale0000,scale0001,scale0002,scale0003,scale0004,NULL));
		
		//Play bullet shoot music effect
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_FIRE);
	}
}


void FishingLayer::bulletRelease(){
    
	//Release the bullet, and set the _bullet to NULL
	if(_bullet!=NULL){
		_bullet->removeFromParent();
		_bullet = NULL;
	}
	net->setPosition(bulletEndPosition);
	net1->setPosition(bulletEndPosition);
	net2->setPosition(bulletEndPosition);
	net3->setPosition(bulletEndPosition);
	addChild(net,1);
	addChild(net1,1);
	addChild(net2,1);
	addChild(net3,1);
}

void FishingLayer::netRelease(){
    
	if (net!=NULL)
	{
		net->removeFromParent();
		net=NULL;
	}
}

void FishingLayer::pauseEvent(Widget* target, TouchEventType type){
    
	if(type == TouchEventType::TOUCH_EVENT_ENDED){
		
		//Get the windows size of fishlayer
		auto winSize = Director::getInstance()->getWinSize();
        
		//Pause all the actions and animations
        this->onExit();
        
		//Get the background ant change it to the pause texture
		auto background = (Sprite*)getChildByTag(102);
		background->setTexture("GameScene/bgblur01_01-hd.png");
		background->setScaleX(winSize.width/background->getContentSize().width);
		background->setScaleY(winSize.height/background->getContentSize().height);
		background->setZOrder(2);
        
		//Create the pause layer
		auto pauseLayer = FishingPauseLayer::create();
		this->getParent()->addChild(pauseLayer,3);
	}
}

void FishingLayer::turnOffMusic(Widget* target,TouchEventType type)
{
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("Audio/music_1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void FishingLayer::turnOnMusic(Widget* target,TouchEventType type){
    
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void FishingLayer::setCannonRotation(Widget* target, Point targetPos){
	
	//Calulatethe rotation of cannon
	auto radian=atan2(targetPos.y-21.6f ,targetPos.x-480.0f);
	auto inclination= radian*180/3.14;
	auto rotation= -(inclination)+90;
	
	//Set the rotation range
	if(rotation<=70 && rotation>=-70){
		
		cannon->setRotation(rotation);
	}
}

void FishingLayer::update(float delta){
	
	//Update the movement of fishes by their speed, limit the move area of the fishes
	for(auto fish:fishActors){
        
		if(fish->getPositionX()>1000){
			
			fish->setPosition(Point(-40,rand()% 480));
		}else if (fish->getPositionX()<-100){
			
			fish->setPosition(1000,rand()%480);
		}else if (fish->getPositionY()<-100){
            
			fish->setPosition(rand()%960,520);
		}else if (fish->getPositionY()<-100){
            
			fish->setPosition(rand()%960,-40);
		}else{
            
			fish->setPosition(fish->getPositionX()+fish->getSpeedX(), fish->getPositionY()+fish->getSpeedY());
		}
	}
	
	//Check the collide
	collideCheck();
}

void FishingLayer::collideCheck(){//Åö×²¼ì²â
	
	//Check the collide when the bullet is exist
	if(_bullet!=NULL){
        
		auto it_self = fishActors.begin();
		
		while (it_self!= fishActors.end()) {
            
			//If the bullet collide the fish
			if (_bullet->getBoundingBox().intersectsRect(dynamic_cast<FishActor*>(*it_self)->getBoundingBox())) {
                
				net->setPosition(Point(dynamic_cast<FishActor*>(*it_self)->getPositionX(),dynamic_cast<FishActor*>(*it_self)->getPositionY()));
				net1->setPosition(Point(dynamic_cast<FishActor*>(*it_self)->getPositionX(),dynamic_cast<FishActor*>(*it_self)->getPositionY()));
				net2->setPosition(Point(dynamic_cast<FishActor*>(*it_self)->getPositionX(),dynamic_cast<FishActor*>(*it_self)->getPositionY()));
				net3->setPosition(Point(dynamic_cast<FishActor*>(*it_self)->getPositionX(),dynamic_cast<FishActor*>(*it_self)->getPositionY()));
				addChild(net,1);
				addChild(net1,1);
				addChild(net2,1);
				addChild(net3,1);
                
				//Release the bullet
				_bullet->removeFromParent();
				_bullet=NULL;
				
				//Set the score
				score+=dynamic_cast<FishActor*>(*it_self)->getFishScore();
				char temp[64];
				sprintf(temp, "%d",score);
				scoreLabel->setStringValue(temp);
				
				//Tag the collided fish
				dynamic_cast<FishActor*>(*it_self)->setTag(200);
				
				//Play the fish death's animations and release them
				switch (dynamic_cast<FishActor*>(*it_self)->fishType) {
						
					case FishActor::FishActorType::SmallFish:
                        dynamic_cast<FishActor*>(*it_self)->
						runAction(Sequence::create(dynamic_cast<SmallFishActor*>(*it_self)->playDeathAnimation(),
                                                   CallFunc::create(CC_CALLBACK_0(FishingLayer::removeFishes,this)),
                                                   NULL));
						break;
						
					case FishActor::FishActorType::AngelFish:
                        dynamic_cast<FishActor*>(*it_self)->runAction(Sequence::create(dynamic_cast<AngelFishActor*>(*it_self)->playDeathAnimation(),
                                                                                       CallFunc::create(CC_CALLBACK_0(FishingLayer::removeFishes,this)),
                                                                                       NULL));
						break;
						
					case FishActor::FishActorType::Amphiprion:
                        dynamic_cast<FishActor*>(*it_self)->runAction(Sequence::create(dynamic_cast<AmphiprionActor*>(*it_self)->playDeathAnimation(),
                                                                                       CallFunc::create(CC_CALLBACK_0(FishingLayer::removeFishes,this)),
                                                                                       NULL));
						break;
						
					case FishActor::FishActorType::Croaker:
                        dynamic_cast<FishActor*>(*it_self)->runAction(Sequence::create(dynamic_cast<CroakerActor*>(*it_self)->playDeathAnimation(),
                                                                                       CallFunc::create(CC_CALLBACK_0(FishingLayer::removeFishes,this)),
                                                                                       NULL));
						break;
                        
					case FishActor::FishActorType::Bream:
                        dynamic_cast<FishActor*>(*it_self)->runAction(Sequence::create(dynamic_cast<BreamActor*>(*it_self)->playDeathAnimation(),
                                                                                       CallFunc::create(CC_CALLBACK_0(FishingLayer::removeFishes,this)),
                                                                                       NULL));
						break;
					default:
						break;
				}
				
				//Move the fish from the fishes vector
				it_self=fishActors.erase(it_self);
				
				break;
			}else{
				
				++it_self;
			}
		}
	}
}

void FishingLayer::removeFishes(){
	
	//Get the collided fish
	auto fishActor = this->getChildByTag(200);
	
	//Remove the collided fish
	fishActor->setVisible(false);
	fishActor->removeAllChildrenWithCleanup(true);
	fishActor->removeFromParent();
	
	//Play music effect when catch a fish
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_COIN);
}

void FishingLayer::fishActorsInital(){
	
	//Get the windows size
	auto winSize = Director::getInstance()->getWinSize();
	
	//Init fishes
	for (int fishIndex=0; fishIndex<8; fishIndex++) {
		
		//Create fishes
		auto smallFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		auto angelFishActor = FishActor::createWithType(FishActor::FishActorType::AngelFish);
		auto croakerFishActor = FishActor::createWithType(FishActor::FishActorType::Croaker);
		auto amphiprionFishActor = FishActor::createWithType(FishActor::FishActorType::Bream);
		auto breamFishActor = FishActor::createWithType(FishActor::FishActorType::SmallFish);
		
		//Set the fishes position
		smallFishActor->setPosition(Point(rand()%910,rand()%590));
		angelFishActor->setPosition(Point(rand()%910,rand()%590));
		croakerFishActor->setPosition(Point(rand()%910,rand()%590));
		amphiprionFishActor->setPosition(Point(rand()%910,rand()%590));
		breamFishActor->setPosition(Point(rand()%910,rand()%430));
		
		((SmallFishActor*)smallFishActor)->activateFishMovement();
		((AngelFishActor*)angelFishActor)->activateFishMovement();
		((CroakerActor*)croakerFishActor)->activateFishMovement();
		((AmphiprionActor*)amphiprionFishActor)->activateFishMovement();
		((BreamActor*)breamFishActor)->activateFishMovement();
		
		//Add the fishes into the layer
		addChild(smallFishActor,1);
		addChild(angelFishActor,1);
		addChild(croakerFishActor,1);
		addChild(amphiprionFishActor,1);
		addChild(breamFishActor,1);
    
		//Add the fishes into the fish vector
		fishActors.pushBack(smallFishActor);
		fishActors.pushBack(angelFishActor);
		fishActors.pushBack(croakerFishActor);
		fishActors.pushBack(amphiprionFishActor);
		fishActors.pushBack(breamFishActor);
	}
}

void FishingLayer::updateFishMovement(){
	
	//Change the direction and speed of the fishes
	for (auto fish:fishActors) {
		
		auto direction = rand()%3-1.0f;
		auto shiftX = (rand()%3+1)*direction;
		auto shiftY = (rand()%3+1)*direction;
        
		fish->setSpeedX(shiftX==0?1:shiftX);
		fish->setSpeedY(shiftY==0?1:shiftY);
		auto rotation = -atan2(shiftY, shiftX);
		fish->setRotation(rotation*180.0f/3.14f+180.0f);
	}
}