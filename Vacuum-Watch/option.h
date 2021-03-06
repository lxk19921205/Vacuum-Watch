#ifndef _VW_OPTION_H_
#define _VW_OPTION_H_

#include <string>
#include "module_interfaces.h"

using std::string;

//IOptions的一个具体实现类
class COption : public IOptions
{
public:
	//数据存在这个文件里
	const static string FILE_NAME;

	virtual void ResetAll();

	virtual bool IsBackgroundOn();
	virtual void SetBackgroundOn(bool on);

	virtual bool IsSoundEffectOn();
	virtual void SetSoundEffectOn(bool on);

	virtual int GetSoundVolume();
	virtual void SetSoundVolume(int percent);

	virtual int GetFireKey();
	virtual void SetFireKey(int key);

	//for Singleton
	static inline COption& Instance()
	{
		static COption _option;
		return _option;
	}

protected:
	//for Singleton
	COption();
	virtual ~COption();
	COption(const COption& rhs);			//不实现
	COption& operator=(const COption& rhs);	//不实现


	//持久化存入文件中，返回成功与否
	bool SaveIntoFile();
	//从文件中恢复，如果没有这个文件，就恢复成默认值，返回有此文件否
	bool RestoreFromFile();

	bool m_bBackground;
	bool m_bEffect;
	int m_iVolume;
	int m_iFireKey;
};


#endif
