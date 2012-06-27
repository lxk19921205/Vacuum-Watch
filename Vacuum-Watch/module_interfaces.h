#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <Windows.h>
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
	//�������е�����
	virtual void ResetAll() = 0;

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
protected:
	//д�������ʱΪ�����ѣ��������������˳�ʱһ��Ҫ�ͷ�������ص���Դ
	virtual void Release() = 0;

public:
	//���ò������ֵ���������һ���ٷֱȣ���IOptions���SetSoundVolume����
	virtual void SetVolume(DWORD dwVolumn) = 0;

	//��ʼ���ű������֣�BGMһ��Ƚϳ���ͬʱ��ֻ����һ�����������ڲ��ţ�url��ΪBGM��ַ
	virtual void StartBGM(const LPCWSTR& url) = 0;
	//ֹͣ���ű������֣���������ڲ��Ļ�
	virtual void StopBGM() = 0;

	//����һ����Ч����Чһ��ʱ��Ƚ϶̣��޷���ͣ�������ж��effectͬʱ�ڲ���
	virtual void PlayEffect(const LPCWSTR& url) = 0;
	//ֹͣһ����Ч������effect��ַurl������ͣ�ĸ���Ч
	virtual void StopEffect(const LPCWSTR& url) = 0;
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

	//�ɻ���ǰ��һ���������˷���false����������ǰ�ˣ������򷵻�true
	virtual bool Step() = 0;

	//��ȡ����İ뾶
	virtual int GetTunnelRadius() = 0;

	//��ȡ��ǰ���˶�Զ
	virtual int GetCurrentLength() = 0;
	//���õ�ǰ���˶�Զ
	virtual void ResetCurrentLength() = 0;

	//��ȡһ���ж�Զ
	virtual int GetTotalLength() = 0;
	//����һ���ж�Զ
	virtual void SetTotalLength(int length) = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ViewEngine���������棩ģ��Ľӿڣ�������������Ⱦ��Ϸ����Ĳ���       */
/************************************************************************/
class IViewEngine
{
public:
	//������չʾ֮ǰ�ĳ�ʼ��
	virtual void Init(int* pargc, char** argv) = 0;

	//��ʼչʾ��Ϸ����
	virtual void StartDisplaying() = 0;

	//���������(pos_x, pos_y)��click��һ��
	virtual void OnLeftClicked(int pos_x, int pos_y) = 0;

//Ϊʲôע���أ�������һ��TimerFunc()�������Ե���controller��OnTimerClick()��ˢ��״̬��Ȼ���ػ棬��ͷ��Ӧ����ʽ��Ҫ���ػ�
// 	//׼���ػ�
// 	virtual void Redraw() = 0;

	//�ݳ�������д�����ã���ģʽ�л�����Ҫ����һЩ���ã���ʱҪ�ٵ�һ��
	virtual void SetupRC() = 0;
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



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ��Ϸ�߼��ܿ�ģ��Ľӿڣ�����������״̬�仯�Ĳ���                     */
/************************************************************************/
class IController
{
public:
// 	//��ȡ��ViewEngine������ÿ������������ViewEngine����һ�飬��Controller������һ��
// 	virtual IViewEngine* GetViewEngine() = 0;

	//��Ϸ��ʼ��
	virtual void StartGame() = 0;

	//���еĳ�ʼ������
	virtual void Init(int* pargc, char** argv) = 0;

	//��ȡ���е���Ϸ����
	virtual IGameData* GetGameData() = 0;

	//FIRE�İ�����������
	virtual void OnFireKeyClicked() = 0;
	//����(from_x, from_y)�ƶ�����to_x, to_y��
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y) = 0;
	//���������(pos_x, pos_y)��click��һ��
	virtual void OnLeftClicked(int pos_x, int pos_y) = 0;

	//��ʱ����ʱ���ˣ�ˢ��һ�£�����true������Ҫ�ػ�
	virtual bool OnTimerClick() = 0;

	//�õ���Ϸ���߼�״̬��VW_STATE_*
	virtual int GetState() = 0;

	//��ʼ��Ϸ�İ�ť������
	virtual void OnStartButton() = 0;
	//���õİ�ť������
	virtual void OnSettingButton() = 0;
	//���ڵİ�ť������
	virtual void OnAboutButton() = 0;
	//�˳��İ�ť������
	virtual void OnQuitButton() = 0;
};


#endif
