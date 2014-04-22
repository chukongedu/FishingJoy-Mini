//testing-sl
//  FishingLayer.h
//  FishJoyMini
//
//  Created by Ken on 14-3-11.
//
//

#ifndef FishJoyMini_FishingLayer_h
#define FishJoyMini_FishingLayer_h
#include "cocos2d.h"
#include "FishActor.h"
#include <cstdlib>
#include "MainMenuLayer.h"
#include "FishingPauseLayer.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "CCScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class FishingLayer : public Layer{
	
public:
	
	bool init();
	CREATE_FUNC(FishingLayer);
    
protected:
	
	void fishActorsInital();
	Vector<FishActor*> fishActors;
	Vector<FishActor*> _fishToBeRemoved;
    
	bool _musicSwitch;
	
	ImageView* cannon;
	
	Sprite* _bullet;
    
    Vector<Sprite*> netVec;
	
	Layout* widget;
	TextAtlas* scoreLabel;
    	
	int score;
	void bulletRelease();
	
	virtual void update(float delta);
	
	/** Callback func of shoot */
	void shootEvent(Widget* target,TouchEventType type);
    
	/** Callback func of pause button */
	void pauseEvent(Widget* target,TouchEventType type);
    
	/**turn on/off backgroundMusic*/
	void musicControl(Widget* target,TouchEventType type);
    
	void bulletShoot(Point endPosition);
	
	void setCannonRotation(Widget* target, Point targetPos);
	
	void collideCheck();
	
	void removeFishes();
	
	void updateFishMovement();
    
    void netInit(Point bulletPosition);

	void netRelease(Node* sender);
};

#endif
