#ifndef _VW_AUDIO_H_
#define _VW_AUDIO_H_

#include <string>
#include "module_interfaces.h"

using std::string;

//IAudio��һ������ʵ����
class CAudio : public IAudio
{
public:
	virtual void Release();

	virtual void SetVolume(int percent) ;
	
	virtual void StartBGM(const LPCWSTR& url);
	virtual void StopBGM();

	virtual void PlayEffect(const LPCWSTR& url) ;
	virtual void StopEffect(const LPCWSTR& url);
	virtual void StopAllEffect();

	//for Singleton
	static inline CAudio& Instance()
	{
		static CAudio _audio;
		return _audio;
	}

private:
	//for Singleton
	CAudio();
	virtual ~CAudio();
	CAudio(const CAudio& rhs);				//��ʵ��
	CAudio& operator=(const CAudio& rhs);	//��ʵ��

};


#endif
