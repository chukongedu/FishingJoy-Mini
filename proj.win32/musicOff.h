#ifndef FishJoyMini_backMusicOff_h
#define FishJoyMini_backMusicOff_h

#include "FishingLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
class backMusicOff2: public cocos2d::MenuItemToggle
{
public:
	backMusicOff2();
	~backMusicOff2();
	void selected() ;
	void unselected() ;

	bool init();
	CREATE_FUNC(backMusicOff2);

private:

};
#endif