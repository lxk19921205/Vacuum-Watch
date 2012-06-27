#include "audio.h"

#include <Windows.h>
#include <MMSystem.h>
#include <Digitalv.h>  
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
void CAudio::SetVolume(DWORD dwVolumn){

	//DWORD dwVolume= (DWORD)(0xFFFF*1.0*percent/100.0);
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
			waveOutSetVolume(hwo, dwVolumn);//
			waveOutClose(hwo);
		}
	}
}

void CAudio::StartBGM(const LPCWSTR& url)
{
	MCI_OPEN_PARMS mciOpen;
	MCIERROR mciError;
	mciOpen.lpstrDeviceType =TEXT( "mpegvideo");
	mciOpen.lpstrElementName = url;

	mciError = mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,(DWORD)&mciOpen);
	if(mciError)
	{
	
	}
	UINT DeviceID = mciOpen.wDeviceID ;
	MCI_PLAY_PARMS mciPlay;

	mciError = mciSendCommand(DeviceID,MCI_PLAY,MCI_DGV_PLAY_REPEAT ,(DWORD)&mciPlay);//循环重复播放
	if(mciError)
	{
		
	}

	//WinExec("sndvol32.exe",SW_SHOWNORMAL);
	//这个可以打开音量控制不过可以用编程实现。

	while(1)
	{
		//sprintf(str,"播放时间:\t%d",i);
		//printf("%s\r",str);
		//i++;
		//Sleep(1000);
	}
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
