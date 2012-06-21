#ifndef _VW_OPTION_H_
#define _VW_OPTION_H_
#include <string>
#include "module_interfaces.h"
#include "log.h"
using namespace std;
class COption:public IOptions
{
public:
	COption();
	~COption();
	virtual void SaveIntoFile();
	virtual void RestoreFromFile();
	virtual bool IsBackgroundOn();
	virtual void SetBackgroundOn(bool on);
	virtual bool IsSoundEffectOn();
	virtual void SetSoundEffectOn(bool on);
	//���δ��ȷ�����ļ����᷵��-1
	virtual int GetSoundVolume();
	//��������percent���ڷ�Χ�ڣ�����-1
	virtual int SetSoundVolume(int percent);
	virtual int GetFireKey();
	virtual void SetFireKey(int key);
private:
	string file_name;
	bool back_ground;
	bool effect;
	int  volume;
	int key;
	bool bret;			//�ļ����ڴ��е�����һ���Ա�ʶ
#if(VW_LOG_CLOSED)
	Clog *log;
#endif
};
#endif
