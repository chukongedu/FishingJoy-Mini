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
    
	Layer::init();
    
	_bullet = NULL;
	_musicSwitch = true;
    
    //Set tag of the layer, and get it in pause layer
    setTag(101);
	
	//Add background picture
	auto background = Sprite::create("CocoStudioRes/FishMiniGameLayer_1/background.jpg");
	background->setAnchorPoint(Point(0,0));
	background->setPosition(Point(0,0));
	background->setTag(102);
	addChild(background,0);
	
	//Read the resources of CocoStudio json file, and add it to the scene
	widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("CocoStudioRes/FishMiniGameLayer_1/FishJoyMini_1.json"));
	addChild(widget,2);
    
	//Read the texture to sprite frame cache
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CocoStudioRes/FishMiniGameLayer_1/cannon-hd.plist");
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
    
	//turn off the background music
	auto musicBtn = dynamic_cast<Button *>(widget->getChildByName("music"));
	musicBtn->addTouchEventListener(this,toucheventselector(FishingLayer::musicControl));
    
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
		
        //Calulatethe rotation of cannon
        auto radian=atan2(target->getTouchEndPos().y-21.6f ,target->getTouchEndPos().x-480.0f);
        auto inclination= radian*180/3.14;
        auto rotation= -(inclination)+90;
        
		//Shoot the bullet
        if(rotation<=70 && rotation >=-70)
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
        
		//Shoot the bullet and release after the action ended
		_bullet->runAction(Sequence::create(MoveTo::create(1, endPosition),
											CallFunc::create(CC_CALLBACK_0(FishingLayer::bulletRelease,this)),
											NULL));
		addChild(_bullet,1);
		
		//Play bullet shoot music effect
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_FIRE);
	}
}


void FishingLayer::bulletRelease(){
    
    
	//Release the bullet, and set the _bullet to NULL
	if(_bullet!=NULL){
        
        //Init fishing net
        netInit(_bullet->getPosition());
        
		_bullet->removeFromParent();
		_bullet = NULL;
	}
}

void FishingLayer::netInit(cocos2d::Point netPosition){
    
    auto netScale1=ScaleTo::create(0.3f,0.4f);
    auto netScale2=ScaleTo::create(0.3f,0.3f);
    auto netScale3=ScaleTo::create(0.3f,0.2f);
    
    auto netFish=SpriteBatchNode::create("GameScene/bullet10-hd.png",5);
    
    //Create fishing net and run the fishing animation
    for (int i=0; i<4; i++) {
        
        auto net = Sprite::createWithTexture(netFish->getTexture(),Rect(0,0,80,80));
        net->setRotation(90.0f*i);
        net->setAnchorPoint(Point(0.0f,0.0f));
        net->setPosition(netPosition);
        addChild(net,1);
        
        net->runAction(Sequence::create(netScale1->clone(), netScale2->clone(), netScale3->clone(), CallFunc::create(CC_CALLBACK_0(FishingLayer::netRelease,this,net)), NULL));
    }
}

void FishingLayer::netRelease(Node* sender){
    
    sender->removeFromParent();
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

void FishingLayer::musicControl(Widget* target,TouchEventType type){
   
    if(type == TouchEventType::TOUCH_EVENT_ENDED){
        
        if(_musicSwitch){
       
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            _musicSwitch = false;
        }else{
    
            CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            _musicSwitch = true;
        }
    }
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

void FishingLayer::collideCheck(){
	
	//Check the collide when the bullet is exist
	if(_bullet!=NULL){
        
		auto it_self = fishActors.begin();
		
		while (it_self!= fishActors.end()) {
            
			//If the bullet collide the fish
			if (_bullet->getBoundingBox().intersectsRect(dynamic_cast<FishActor*>(*it_self)->getBoundingBox())) {
                
				//Release the bullet
				_bullet->removeFromParent();
				_bullet=NULL;
				
				//Set the score
				score+=dynamic_cast<FishActor*>(*it_self)->getFishScore();
				char temp[64];
				sprintf(temp, "%d",score);
				scoreLabel->setStringValue(temp);
				
				auto fish_to_remove = dynamic_cast<FishActor*>(*it_self);
                _fishToBeRemoved.pushBack(fish_to_remove);

                netInit(dynamic_cast<FishActor*>(*it_self)->getPosition());
				
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
			
	//Remove the collided fish
    for(auto fish : _fishToBeRemoved){
     
        fish->removeFromParentAndCleanup(true);
    }

    _fishToBeRemoved.clear();
	
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
		
        //Activate fish own movement event
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