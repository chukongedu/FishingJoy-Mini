//
//  FishActor.cpp
//  FishJoyMini
//
//  Created by Ken on 14-3-7.
//
//

#include "FishActor.h"

FishActor* FishActor::createWithType(FishActorType fishType){
	
	FishActor* fish;

	//Create the fishes by the fish type
	switch (fishType) {
		case FishActorType::SmallFish:
			
			fish = SmallFishActor::create();
			break;
		case FishActorType::AngelFish:
			
			fish = AngelFishActor::create();
			break;
		case FishActorType::Croaker:
			
			fish = CroakerActor::create();
			break;
		case FishActorType::Amphiprion:
			
			fish = AmphiprionActor::create();
			break;
			
		case FishActorType::Bream:
			
			fish = BreamActor::create();
			break;
			
		case FishActorType::MarlinsFish:
			
			fish = MarlinsFishActor::create();
			break;
			
		default:
			break;
	}

	return fish;
}

void FishActor::updateFishMovement(float delta){
	
	auto direction = rand()%3-1.0f;
	auto shiftX = (rand()%5+1)*direction;
	auto shiftY = (rand()%5+1)*direction;
	
	setSpeedX(shiftX==0?1:shiftX);
	setSpeedY(shiftY==0?1:shiftY);
	auto rotation = -atan2(shiftY, shiftX);
	setRotation(rotation*180.0f/3.14f+180.0f);
}

bool SmallFishActor::init(){
	
	FishActor::init();
	
	setSpeedX(1.0f);
	setSpeedY(1.0f);
	
	setFishScore(1.0f);
	
	fishType = FishActorType::SmallFish;
	
	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();//动态数组容器
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_actor_001.png"));
	/*
	这几句注释掉后，就无法动画了
	详见P110：
	CCSpriteBatchNode

	TextPacker------->.plist+.ccz但用.plist
	CCSpriteFrameCache--------.plist
	CCSprite					 --------.png

	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_actor_004.png"));
	*/

	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.1);
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
	
	
	return true;
}

void SmallFishActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 3+rand()%2);
}

Animate* SmallFishActor::playDeathAnimation(){
	
	//Read the death anmtions textures
	auto deathFrames = Vector<SpriteFrame*>();
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_004.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("SmallFish_death_005.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	auto deathAnimate = Animate::create(deathAnimation);
	
	return deathAnimate;
}

bool AngelFishActor::init(){
	
	FishActor::init();
	
	setSpeedX(1.5f);
	setSpeedY(1.5f);

	setFishScore(5.0f);

	fishType = FishActorType::AngelFish;

	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_001.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_004.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_005.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_006.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_007.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_008.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_009.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_actor_010.png"));

	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.1);
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
		
	return true;
}

void AngelFishActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 3.5+rand()%2);
}


Animate* AngelFishActor::playDeathAnimation(){
	
	auto deathFrames = Vector<SpriteFrame*>();
	
	//Read the death anmtions textures
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_004.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("AngelFish_death_005.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	auto deathAnimate = Animate::create(deathAnimation);
	
	return deathAnimate;
}

bool CroakerActor::init(){
	
	FishActor::init();
	
	setSpeedX(2.0f);
	setSpeedY(2.0f);
	
	fishType = FishActorType::Croaker;

	setFishScore(3.0f);

	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();	
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_actor_001.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_actor_004.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_actor_005.png"));
	
	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.1);
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
	
	return true;
}

void CroakerActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 2+rand()%4);
}

Animate* CroakerActor::playDeathAnimation(){
	
	//Read the death anmtions textures
	auto deathFrames = Vector<SpriteFrame*>();
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_004.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Croaker_death_005.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);	
	auto deathAnimate = Animate::create(deathAnimation);
	
	return deathAnimate;
}

bool AmphiprionActor::init(){
		
	FishActor::init();
	
	setSpeedX(1.8f);
	setSpeedY(1.8f);
	
	fishType = FishActorType::Amphiprion;

	setFishScore(4.0f);

	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_001.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_004.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_005.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_actor_006.png"));
		
	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.2);		
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
	
	
	return true;
}

void AmphiprionActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 1+rand()%4);
}

Animate* AmphiprionActor::playDeathAnimation(){
	
	//Read the death anmtions textures
	auto deathFrames = Vector<SpriteFrame*>();
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_death_004.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Amphiprion_death_005.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);	
	auto deathAnimate = Animate::create(deathAnimation);
	
	return deathAnimate;
}

bool BreamActor::init(){
	
	FishActor::init();
	
	setSpeedX(0.4f);
	setSpeedY(0.4f);

	setFishScore(10.0f);

	fishType = FishActorType::Bream;

	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();
	
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_001.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_004.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_005.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_006.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_007.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_008.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_actor_009.png"));
		
	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.2);	
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
	
	return true;
}

void BreamActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 2+rand()%3);
}

Animate* BreamActor::playDeathAnimation(){
	
	//Read the death anmtions textures
	auto deathFrames = Vector<SpriteFrame*>();
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_death_004.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Bream_death_005.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	auto deathAnimate = Animate::create(deathAnimation);

	return deathAnimate;
}

bool MarlinsFishActor::init(){
	
	FishActor::init();
	
	setSpeedX(0.1f);
	setSpeedY(0.1f);
	
	setFishScore(100.0f);
	
	fishType = FishActorType::MarlinsFish;
	
	//Read the swimming animations textures
	auto fishes = Vector<SpriteFrame*>();
	
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_001.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_002.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_003.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_004.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_005.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_006.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_007.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_008.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_009.png"));
	fishes.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_actor_010.png"));
	
	//Create swimming animation
	auto fishAnimation = Animation::createWithSpriteFrames(fishes,0.1);
	auto fishAnimate = Animate::create(fishAnimation);
	
	//Run the swiming action forever
	runAction(RepeatForever::create(fishAnimate));
	
	return true;
}

void MarlinsFishActor::activateFishMovement(){
	
    schedule(schedule_selector(FishActor::updateFishMovement), 2+rand()%3);
}

Animate* MarlinsFishActor::playDeathAnimation(){
	
	//Read the death anmtions textures
	auto deathFrames = Vector<SpriteFrame*>();
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_death_001.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_death_002.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_death_003.png"));
	deathFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("MarlinsFish_death_004.png"));
	
	//Create the death anmation
	auto deathAnimation = Animation::createWithSpriteFrames(deathFrames, 0.1);
	auto deathAnimate = Animate::create(deathAnimation);
	
	return deathAnimate;
}
