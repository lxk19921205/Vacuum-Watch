/************************************************************************/
/* 专门用于测试的类，自己添各个函数 by Andriy                           */
/************************************************************************/

#include <iostream>
#include <fstream>

#include "testing.h"
#include "option.h"
#include "log.h"

using std::cout;
using std::endl;
using std::ifstream;


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


void CTesting::TestLog()
{
	CLog log;
// 	log.ClearDebug();
// 	log.ClearError();
// 	log.ClearInfo();

	log.Info("hello in info");
	log.Debug("world in debug");
	log.Error("graphics in error");

	log.Info("hello again in info");
	log.ClearInfo();
	log.Info("hello 3rd in info");
	log.Info("hello 4th in info");
}
