#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Log����־��ģ��Ľӿڣ�������logģ������Ĳ���                       */
/************************************************************************/
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
/************************************************************************/
/* Optionsģ�飨��Ϸ����ģ�飩�Ľӿڣ�������optionsģ������Ĳ�����Ҫ���ܹ��Զ��־û��洢
/************************************************************************/
class IOptions
{
public:
	//���������Ƿ񲥷�
	virtual bool IsBackgroundOn() = 0;
	//�����Ƿ񲥷ű�������
	virtual void SetBackgroundOn(bool on) = 0;

	//��Ч�Ƿ��
	virtual bool IsSoundEffectOn() = 0;
	//�����Ƿ񲥷���Ч
	virtual void SetSoundEffectOn(bool on) = 0;

	//��ȡ���ֵ�������С
	virtual int GetSoundVolume() = 0;
	//�������ֵ�������С��Ϊһ���ٷֱȣ�������������İٷ�֮����ֱ�Ӻ��Դ����percent��not [0, 100]��
	virtual void SetSoundVolume(int percent) = 0;

	//��÷ɻ������ڵ��İ���
	virtual int GetFireKey() = 0;
	//���÷ɻ������ڵ��İ���
	virtual void SetFireKey(int key) = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Audio����Ч��ģ��Ľӿڣ�������audioģ������Ĳ���                   */
/************************************************************************/
class IAudio
{
public:
	//д�������ʱΪ�����ѣ��������������˳�ʱһ��Ҫ�ͷ�������ص���Դ
	virtual void Release() = 0;

	//���ò������ֵ���������һ���ٷֱȣ���IOptions���SetSoundVolume����
	virtual void SetVolume(int percent) = 0;

	//��ʼ���ű������֣�BGMһ��Ƚϳ���ͬʱ��ֻ����һ�����������ڲ��ţ�url��ΪBGM��ַ
	virtual void StartBGM(const string& url) = 0;
	//ֹͣ���ű������֣���������ڲ��Ļ�
	virtual void StopBGM() = 0;

	//����һ����Ч����Чһ��ʱ��Ƚ϶̣��޷���ͣ�������ж��effectͬʱ�ڲ���
	virtual void PlayEffect(const string& url) = 0;
	//ֹͣһ����Ч������effect��ַurl������ͣ�ĸ���Ч
	virtual void StopEffect(const string& url) = 0;
	//ֹͣȫ�����ڲ��ŵ���Ч
	virtual void StopAllEffect() = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* GameData����Ϸ���ݣ�ģ��Ľӿڣ�������������Ϸ������صĲ���         */
/************************************************************************/
class IGameData
{
public:
	//��ǰ�ǵڼ���
	virtual int GetCurrentStage() = 0;
	//����Ϊ������һ��
	virtual void NextStage() = 0;
	//���ؿ�����Ϊ��ʼ״̬
	virtual void ResetStage() = 0;

	//��ǰ�����Ƕ���
	virtual long GetCurrentScore() = 0;
	//�ڵ�ǰ����������/����һ���ַ���
	virtual void AddScore(long score) = 0;
	//����ǰ��������Ϊ��ʼ״̬
	virtual void ResetScore() = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ViewEngine���������棩ģ��Ľӿڣ�������������Ⱦ��Ϸ����Ĳ���       */
/************************************************************************/
class IViewEngine
{
public:

};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Input��������ƣ�ģ��Ľӿڣ������������������̲����ļ�������      */
/************************************************************************/
class IInput
{
public:
	//��ʼ������
	virtual void InitListener() = 0;
};

#endif
