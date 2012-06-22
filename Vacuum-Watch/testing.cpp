/************************************************************************/
/* 专门用于测试的类，自己添各个函数 by Andriy                           */
/************************************************************************/

#include <iostream>

#include "testing.h"
#include "option.h"

using std::cout;
using std::endl;


CTesting::CTesting()
{
}

CTesting::~CTesting()
{
}


void CTesting::TestOptions()
{
	COption option;

	cout << "DEF: " << endl
		<< " bgm_on? " << option.IsBackgroundOn() << endl
		<< " effect_on? " << option.IsSoundEffectOn() << endl
		<< " volume? " << option.GetSoundVolume() << endl
		<< " fire_key? " << option.GetFireKey() << endl;
	
	option.SetBackgroundOn(true);
	option.SetSoundEffectOn(false);
	option.SetSoundVolume(75);
	option.SetFireKey(20);

	COption option2;
	cout << "After Changed, in another instance: " << endl
		<< " bgm_on? " << option2.IsBackgroundOn() << endl
		<< " effect_on? " << option2.IsSoundEffectOn() << endl
		<< " volume? " << option2.GetSoundVolume() << endl
		<< " fire_key? " << option2.GetFireKey() << endl;
}
