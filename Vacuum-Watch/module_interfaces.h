#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;


//////////////////////////////////////////////////////////////////////////

//Logģ��Ľӿڣ�������logģ������Ĳ���
class ILog
{
public:
	//��ô��info��log���ļ���
	virtual const string& GetInfoFileName() = 0;
	//��ô��debug��log���ļ���
	virtual const string& GetDebugFileName() = 0;
	//��ô��error��log���ļ���
	virtual const string& GetErrorFileName() = 0;

	//���info����log
	virtual void ClearInfo() = 0;
	//���debug����log
	virtual void ClearDebug() = 0;
	//���error����log
	virtual void ClearError() = 0;

	//д��һ��info����log
	virtual void Info(const string& msg) = 0;
	//д��һ��debug����log
	virtual void Debug(const string& msg) = 0;
	//д��һ��error����log
	virtual void Error(const string& msg) = 0;
};

//////////////////////////////////////////////////////////////////////////

//Optionsģ�飨��Ϸ����ģ�飩�Ľӿڣ�������optionsģ������Ĳ���
class IOptions
{
public:
	//����ǰ�����ô����ļ�
	virtual void SaveIntoFile() = 0;
	//��֮ǰ��õ��ļ������֮ǰ�����ã����û��֮ǰ��õ��ļ����Ͳ����޸�
	virtual void RestoreFromFile() = 0;

	//���������Ƿ񲥷�
	virtual bool IsBackgroundOn() = 0;
	//�����Ƿ񲥷ű�������
	virtual void SetBackground(bool on) = 0;

	//��Ч�Ƿ��
	virtual bool IsSoundEffectOn() = 0;
	//�����Ƿ񲥷���Ч
	virtual void SetSoundEffect(bool on) = 0;

	//��÷ɻ������ڵ��İ���
	virtual int GetFireKey() = 0;
	//���÷ɻ������ڵ��İ���
	virtual void SetFireKey(int key) = 0;
};

//////////////////////////////////////////////////////////////////////////
#endif