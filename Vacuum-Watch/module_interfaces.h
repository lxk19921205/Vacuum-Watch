#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <Windows.h>
#include <string>
using std::string;


//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Log（日志）模块的接口，定义了log模块所需的操作                       */
/************************************************************************/
class ILog
{
public:
	//获得存放info级log的文件名
	virtual const string& GetInfoFileName() = 0;
	//获得存放debug级log的文件名
	virtual const string& GetDebugFileName() = 0;
	//获得存放error级log的文件名
	virtual const string& GetErrorFileName() = 0;

	//清空info级的log
	virtual void ClearInfo() = 0;
	//清空debug级的log
	virtual void ClearDebug() = 0;
	//清空error级的log
	virtual void ClearError() = 0;

	//写入一条info级的log
	virtual void Info(const string& msg) = 0;
	//写入一条debug级的log
	virtual void Debug(const string& msg) = 0;
	//写入一条error级的log
	virtual void Error(const string& msg) = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Options模块（游戏设置模块）的接口，定义了options模块所需的操作，要求能够自动持久化存储
/************************************************************************/
class IOptions
{
public:
	//重置所有的设置
	virtual void ResetAll() = 0;

	//背景音乐是否播放
	virtual bool IsBackgroundOn() = 0;
	//设置是否播放背景音乐
	virtual void SetBackgroundOn(bool on) = 0;

	//音效是否打开
	virtual bool IsSoundEffectOn() = 0;
	//设置是否播放音效
	virtual void SetSoundEffectOn(bool on) = 0;

	//获取音乐的音量大小
	virtual int GetSoundVolume() = 0;
	//设置音乐的音量大小，为一个百分比，代表最大音量的百分之几，直接忽略错误的percent（not [0, 100]）
	virtual void SetSoundVolume(int percent) = 0;

	//获得飞机发射炮弹的按键
	virtual int GetFireKey() = 0;
	//设置飞机发射炮弹的按键
	virtual void SetFireKey(int key) = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Audio（音效）模块的接口，定义了audio模块所需的操作                   */
/************************************************************************/
class IAudio
{
protected:
	//写这个函数时为了提醒：在析构函数里退出时一定要释放所有相关的资源
	virtual void Release() = 0;

public:
	//设置播放音乐的音量，是一个百分比，见IOptions里的SetSoundVolume函数
	virtual void SetVolume(DWORD dwVolumn) = 0;

	//开始播放背景音乐，BGM一般比较长，同时间只能有一个背景音乐在播放，url即为BGM地址
	virtual void StartBGM(const LPCWSTR& url) = 0;
	//停止播放背景音乐，如果有正在播的话
	virtual void StopBGM() = 0;

	//播放一个音效，音效一般时间比较短，无法暂停，可以有多个effect同时在播放
	virtual void PlayEffect(const LPCWSTR& url) = 0;
	//停止一个音效，根据effect地址url决定是停哪个音效
	virtual void StopEffect(const LPCWSTR& url) = 0;
	//停止全部正在播放的音效
	virtual void StopAllEffect() = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* GameData（游戏数据）模块的接口，定义了所有游戏数据相关的操作         */
/************************************************************************/
class IGameData
{
public:
	//当前是第几关
	virtual int GetCurrentStage() = 0;
	//设置为进入下一关
	virtual void NextStage() = 0;
	//将关卡重置为初始状态
	virtual void ResetStage() = 0;

	//当前积分是多少
	virtual long GetCurrentScore() = 0;
	//在当前基础上增加/减少一部分分数
	virtual void AddScore(long score) = 0;
	//将当前积分重置为初始状态
	virtual void ResetScore() = 0;

	//飞机向前走一步，走完了返回false（不能再向前了），否则返回true
	virtual bool Step() = 0;

	//获取隧道的半径
	virtual int GetTunnelRadius() = 0;

	//获取当前跑了多远
	virtual int GetCurrentLength() = 0;
	//重置当前跑了多远
	virtual void ResetCurrentLength() = 0;

	//获取一共有多远
	virtual int GetTotalLength() = 0;
	//设置一共有多远
	virtual void SetTotalLength(int length) = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* ViewEngine（界面引擎）模块的接口，定义了所有渲染游戏界面的操作       */
/************************************************************************/
class IViewEngine
{
public:
	//做界面展示之前的初始化
	virtual void Init(int* pargc, char** argv) = 0;

	//开始展示游戏界面
	virtual void StartDisplaying() = 0;

	//鼠标的左键在(pos_x, pos_y)处click了一下
	virtual void OnLeftClicked(int pos_x, int pos_y) = 0;

//为什么注释呢：现在有一个TimerFunc()，周期性调用controller的OnTimerClick()，刷新状态，然后重绘，外头不应该显式的要求重绘
// 	//准备重绘
// 	virtual void Redraw() = 0;

	//据超级宝典写的设置，当模式切换后，需要重设一些设置，那时要再调一次
	virtual void SetupRC() = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* Input（输入控制）模块的接口，定义了所有鼠标与键盘操作的监听处理      */
/************************************************************************/
class IInput
{
public:
	//初始化监听
	virtual void InitListener() = 0;
};



//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 游戏逻辑总控模块的接口，定义了所有状态变化的操作                     */
/************************************************************************/
class IController
{
public:
// 	//获取其ViewEngine，避免每个函数都既在ViewEngine里有一遍，在Controller里再来一遍
// 	virtual IViewEngine* GetViewEngine() = 0;

	//游戏开始！
	virtual void StartGame() = 0;

	//所有的初始化工作
	virtual void Init(int* pargc, char** argv) = 0;

	//获取所有的游戏数据
	virtual IGameData* GetGameData() = 0;

	//FIRE的按键被按下了
	virtual void OnFireKeyClicked() = 0;
	//鼠标从(from_x, from_y)移动到（to_x, to_y）
	virtual void OnMouseMoved(int from_x, int from_y, int to_x, int to_y) = 0;
	//鼠标的左键在(pos_x, pos_y)处click了一下
	virtual void OnLeftClicked(int pos_x, int pos_y) = 0;

	//计时器到时候了，刷新一下，返回true代表需要重绘
	virtual bool OnTimerClick() = 0;

	//得到游戏的逻辑状态：VW_STATE_*
	virtual int GetState() = 0;

	//开始游戏的按钮被按下
	virtual void OnStartButton() = 0;
	//设置的按钮被按下
	virtual void OnSettingButton() = 0;
	//关于的按钮被按下
	virtual void OnAboutButton() = 0;
	//退出的按钮被按下
	virtual void OnQuitButton() = 0;
};


#endif
