//
//  FishingPauseLayer.h
//  FishJoyMini
//
//  Created by Ken on 14-3-16.
//
//

#ifndef FishJoyMini_FishingPauseLayer_h
#define FishJoyMini_FishingPauseLayer_h

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FishingPauseLayer : public Layer
{
public:
	
	bool init();
	CREATE_FUNC(FishingPauseLayer);
	
protected:
	
	/* Events of continue button, select scene button, main menu event, setting button */
	void continueEvent(ui::Widget* target, ui::TouchEventType type);
	void selectEvent(ui::Widget* target, ui::TouchEventType type);
	void mainMenuEvent(ui::Widget* target, ui::TouchEventType type);
	void settingEvent(ui::Widget* target, ui::TouchEventType type);
};

#endif
