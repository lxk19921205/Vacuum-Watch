/************************************************************************/
/* 专门用于测试的类，自己添各个函数 by Andriy                           */
/************************************************************************/

#include <iostream>
#include <fstream>

#include "testing.h"
#include "option.h"
#include "log.h"
#include "game_data.h"
#include "factory.h"
#include "audio.h"

using std::cin;
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
	IOptions* option = CFactory::getOptions();

	cout << "DEF: " << endl
		<< " bgm_on? " << option->IsBackgroundOn() << endl
		<< " effect_on? " << option->IsSoundEffectOn() << endl
		<< " volume? " << option->GetSoundVolume() << endl
		<< " fire_key? " << option->GetFireKey() << endl;
	
	option->SetBackgroundOn(true);
	option->SetSoundEffectOn(false);
	option->SetSoundVolume(150);
	option->SetFireKey(20);

	IOptions* option2 = CFactory::getOptions();
	cout << "After Changed, in another instance: " << endl
		<< " bgm_on? " << option2->IsBackgroundOn() << endl
		<< " effect_on? " << option2->IsSoundEffectOn() << endl
		<< " volume? " << option2->GetSoundVolume() << endl
		<< " fire_key? " << option2->GetFireKey() << endl;
}


void CTesting::TestLog()
{
	ILog* log = CFactory::getLog();
 	log->ClearDebug();
 	log->ClearError();
 	log->ClearInfo();

	log->Info("hello in info");
	log->Debug("world in debug");
	log->Error("graphics in error");

	log->Info("hello again in info");
//	log->ClearInfo();
//	log->Info("hello 3rd in info");
//	log->Info("hello 4th in info");
}


void CTesting::TestGameData()
{
	CGameData data;

	cout << "DEF: "<< endl
		<< "current stage: " << data.GetCurrentStage() << endl;

	data.NextStage();
	data.NextStage();
	cout << "after 2 NextStage(), stage:  "<< data.GetCurrentStage() << endl;
	
	data.ResetStage();
	cout << "after ResetStage(), stage: " << data.GetCurrentStage() << endl;

	data.NextStage();
	data.NextStage();
	data.NextStage();
	data.NextStage();
	data.NextStage();
	data.NextStage();
	cout << "after 6 NextStage(), stage: " << data.GetCurrentStage() << endl;

	cout << endl
		<< "DEF: " << endl
		<< "current score: " << data.GetCurrentScore() << endl;

	data.AddScore(100);
	cout << "after + 100, score:  " << data.GetCurrentScore() << endl;
	data.AddScore(1000);
	cout << "after + 1000, score: " << data.GetCurrentScore() << endl;
	data.AddScore(-1500);
	cout << "after - 1500, score: " << data.GetCurrentScore() << endl;

	data.ResetScore();
	cout << "after reset score, score: " << data.GetCurrentScore() << endl;
}

void CTesting::WaitUntil(char target_c)
{
	char c = '\0';
	while ((c = getchar()) != target_c)
	{
	}
}

void CTesting::TestAudio()
{
	IAudio* audio = CFactory::getAudio();

	cout << "to START_BGM" << endl;
	this->WaitUntil('n');
//	audio->StartBGM(L"..\\Resource\\audio\\dreamcatcher.wav");

	cout << "to SET_VOLUMN 100" << endl;
	this->WaitUntil('n');
	audio->SetVolume(0xFFFF);

	cout << "to SET_VOLUMN 0" << endl;
	this->WaitUntil('n');
	audio->SetVolume(0);

	cout << "to SET_VOLUMN 150" << endl;
	this->WaitUntil('n');
	audio->SetVolume(150);

	cout << "to SET_VOLUMN -50" << endl;
	this->WaitUntil('n');
	audio->SetVolume(-50);

	cout << "to SET_VOLUMN 50" << endl;
	this->WaitUntil('n');
	audio->SetVolume(50);

	cout << "to STOP_BGM" << endl;
	this->WaitUntil('n');
	audio->StopBGM();

	cout << "to PLAY_EFFECT together" << endl;
	this->WaitUntil('n');
	audio->PlayEffect(L"..\\Resource\\audio\\effect1.wav");
	audio->PlayEffect(L"..\\Resource\\audio\\effect2.wav");

	cout << "to STOP_ONE_EFFECT" << endl;
	this->WaitUntil('n');
	audio->StopEffect(L"..\\Resource\\audio\\effect1.wav");

	cout << "to STOP_ALL_EFFECT" << endl;
	this->WaitUntil('n');
	audio->PlayEffect(L"..\\Resource\\audio\\effect1.wav");
	audio->StopAllEffect();

	cout << "TEST DONE" << endl;
}
