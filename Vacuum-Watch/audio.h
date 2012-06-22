#ifndef _VW_OPTION_H_
#define _VW_OPTION_H_

#include <string>
#include "module_interfaces.h"

using std::string;

//IAudio��һ������ʵ����
class CAudio : public IAudio
{
public:
	CAudio();
	virtual ~CAudio();

	//���ݴ�������ļ���
	const static string FILE_NAME;

	virtual void Release();

	virtual void SetVolume(int percent) ;
	
	virtual void StartBGM(const LPCWSTR& url);
	virtual void StopBGM();

	virtual void PlayEffect(const LPCWSTR& url) ;
	virtual void StopEffect(const LPCWSTR& url);

	virtual void StopAllEffect();


	
	
};


#endif
