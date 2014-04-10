//
//  FishActor.h
//  FishJoyMini
//
//  Created by Ken on 14-3-7.
//
//

#include "cocos2d.h"
#ifndef FishJoyMini_FishActor_h
#define FishJoyMini_FishActor_h

USING_NS_CC;

class FishActor : public cocos2d::Sprite
{
public:
	
	enum class FishActorType
    {
		SmallFish,
		AngelFish,
		Croaker,
		Amphiprion,
		Bream,
		MarlinsFish,
    };
	
	/** Speed property of the fishes */
	CC_SYNTHESIZE(float, speedX, SpeedX);
	CC_SYNTHESIZE(float, speedY, SpeedY);
	
	FishActorType fishType;
	
	/** Create the fish by their types */
	static FishActor* createWithType(FishActorType fishType);

	/** Play the death animation */
	Animate* playDeathAnimation();
	
	/** Update the fish movement */
	void updateFishMovement(float dt);
	
	/** Activate the fish movement */
	void activateFishMovement();
	
protected:
	CC_SYNTHESIZE(float, fishScore, FishScore);
};

class SmallFishActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(SmallFishActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};

class AngelFishActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(AngelFishActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};

class CroakerActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(CroakerActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};

class AmphiprionActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(AmphiprionActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};

class BreamActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(BreamActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};

class MarlinsFishActor : public FishActor{
	
public:
	
	bool init();
	
	CREATE_FUNC(MarlinsFishActor);
	Animate* playDeathAnimation();
	void activateFishMovement();
};


#endif
