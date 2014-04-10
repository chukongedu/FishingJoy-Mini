#include "musicOff.h"

backMusicOff2::backMusicOff2()
{
}

backMusicOff2::~backMusicOff2()
{
}
bool backMusicOff2:: init()
{
	return true;
}
void backMusicOff2:: selected() 
{
	/*MenuItemToggle::selected();*/
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}
void backMusicOff2:: unselected()
{
	/*MenuItemToggle::unselected();*/
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}