#include "module_interfaces.h"
#include "factory.h"
#include "audio.h"
#include <Windows.h>
#include <MMSystem.h>
#pragma comment(lib, "WINMM.LIB") 
using std::string;


CAudio::CAudio()
{

}

CAudio::~CAudio()
{

}
void CAudio::Release()
{

}




void CAudio::SetVolume(int percent)
{

}


void CAudio::StartBGM(const LPCWSTR& url)
{

	PlaySound(url,NULL,SND_FILENAME|SND_SYNC|SND_LOOP);

}

void CAudio::StopBGM()
{
	PlaySound(NULL,NULL,SND_FILENAME);
}


void CAudio::PlayEffect(const LPCWSTR& url)
{
	PlaySound(url,NULL,SND_FILENAME|SND_SYNC);
}

void CAudio::StopEffect(const LPCWSTR& url)
{

}

void CAudio::StopAllEffect()
{

}
