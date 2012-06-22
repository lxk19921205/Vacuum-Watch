#ifndef _VW_OPTION_H_
#define _VW_OPTION_H_

#include <string>
#include "module_interfaces.h"

using std::string;

//IOptions的一个具体实现类
class COption : public IOptions
{
public:
	COption();
	virtual ~COption();

	//数据存在这个文件里
	const static string FILE_NAME;

	virtual bool IsBackgroundOn();
	virtual void SetBackgroundOn(bool on);

	virtual bool IsSoundEffectOn();
	virtual void SetSoundEffectOn(bool on);

	virtual int GetSoundVolume();
	virtual void SetSoundVolume(int percent);

	virtual int GetFireKey();
	virtual void SetFireKey(int key);

protected:
	//持久化存入文件中，返回成功与否
	bool SaveIntoFile();
	//从文件中恢复，如果没有这个文件，就恢复成默认值，返回有此文件否
	bool RestoreFromFile();

	bool m_bBackground;
	bool m_bEffect;
	int m_iVolume;
	int m_iFireKey;

//	bool bret;			//文件与内存中的数据一致性标识
//注：使用接口而不是具体的类，而且不用存成员变量，每次要的时候直接取就好了，by Andriy
// #if(VW_LOG_CLOSED)
// 	Clog *log;	//to ILog*
// #endif
};


#endif
