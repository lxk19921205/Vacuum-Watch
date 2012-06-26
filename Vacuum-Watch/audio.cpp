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
	//NOTHING
}


//调节系统音量
void CAudio::SetVolume(int percent){

	DWORD dwVolume= (DWORD)(0xFFFF*1.0*percent/100.0);
	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.nChannels = 1;  
	wf.nSamplesPerSec = 8000 * 1000;
	wf.wBitsPerSample = 8;
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
	wf.cbSize = 0;
	HWAVEOUT hwo;

	for (UINT id = 0; id < waveOutGetNumDevs(); id++) {
		if (waveOutOpen(&hwo, id, &wf, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR)
		{ 
			waveOutSetVolume(hwo, dwVolume);//
			waveOutClose(hwo);
		}
	}
}

void CAudio::StartBGM(const LPCWSTR& url)
{
	PlaySound(url,NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
}

void CAudio::StopBGM()
{
	PlaySound(NULL,NULL,SND_FILENAME);
}


void CAudio::PlayEffect(const LPCWSTR& url)
{
	PlaySound(url,NULL,SND_FILENAME|SND_ASYNC);
}

void CAudio::StopEffect(const LPCWSTR& url)
{
	PlaySound(NULL,NULL,SND_FILENAME|SND_ASYNC);
}

void CAudio::StopAllEffect()
{
	PlaySound(NULL,NULL,SND_FILENAME|SND_ASYNC);
}
