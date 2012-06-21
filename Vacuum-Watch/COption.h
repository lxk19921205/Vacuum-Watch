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
	//如果未正确加载文件，会返回-1
	virtual int GetSoundVolume();
	//如果输入的percent不在范围内，返回-1
	virtual int SetSoundVolume(int percent);
	virtual int GetFireKey();
	virtual void SetFireKey(int key);
private:
	string file_name;
	bool back_ground;
	bool effect;
	int  volume;
	int key;
	bool bret;			//文件与内存中的数据一致性标识
#if(VW_LOG_CLOSED)
	Clog *log;
#endif
};
#endif
