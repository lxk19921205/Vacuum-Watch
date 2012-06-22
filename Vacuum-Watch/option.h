#ifndef _VW_OPTION_H_
#define _VW_OPTION_H_

#include <string>
#include "module_interfaces.h"

using std::string;

//IOptions��һ������ʵ����
class COption : public IOptions
{
public:
	COption();
	virtual ~COption();

	//���ݴ�������ļ���
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
	//�־û������ļ��У����سɹ����
	bool SaveIntoFile();
	//���ļ��лָ������û������ļ����ͻָ���Ĭ��ֵ�������д��ļ���
	bool RestoreFromFile();

	bool m_bBackground;
	bool m_bEffect;
	int m_iVolume;
	int m_iFireKey;
};


#endif
