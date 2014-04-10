//
//  MainMenuLayer.h
//  FishJoyMini
//
//  Created by Ken on 14-3-6.
//
//
#include "MainMenuScene.h"
#include "FishActor.h"
#include "FishingScene.h"

#ifndef FishJoyMini_MainMenuLayer_h
#define FishJoyMini_MainMenuLayer_h
USING_NS_CC;

class MainMenuLayer : public cocos2d::Layer
{
public:
	
	/** Init the layer */
	bool init();
	CREATE_FUNC(MainMenuLayer);
	
protected:
	
	/** Init the fishes */
	void fishActorsInital();//界面出现鱼队列
	
	/** Create Bubble */
	ParticleSystemQuad* createPaopao(Point position);//游戏主界面上的水其气泡
	
	/** Callback func when touch the startgame button */
	void startGameEvent(Ref* sender);
	
	/** Callback func when touch the select scne button */
	void sceneChoose(Ref* sender);
	
	/** Callback func when the fish need to turn back */
	void turnBack(Node* sender);
	
	/** Callback func when the fish need to turn back */
	void marlinTurnBack(Node* sender);
	
	/** Create the action of fish and return */
	ActionInterval* createFishMoveAction(FishActor* fish);
		
	/** Create the action of marlin and return */
	ActionInterval* createMarlinMoveAction(MarlinsFishActor* fish);
};


#endif
