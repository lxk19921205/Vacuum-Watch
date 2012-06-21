#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;


//////////////////////////////////////////////////////////////////////////

//Log（日志）模块的接口，定义了log模块所需的操作
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

//Options模块（游戏设置模块）的接口，定义了options模块所需的操作
class IOptions
{
public:
	//将当前的设置存入文件
	virtual void SaveIntoFile() = 0;
	//从之前存好的文件里读出之前的设置，如果没有之前存好的文件，就不用修改
	virtual void RestoreFromFile() = 0;

	//背景音乐是否播放
	virtual bool IsBackgroundOn() = 0;
	//设置是否播放背景音乐
	virtual void SetBackgroundOn(bool on) = 0;

<<<<<<< HEAD
	virtual void Info(string msg) = 0;
	virtual void Debug(string msg) = 0;
	virtual void Error(string msg) = 0;
	
=======
	//音效是否打开
	virtual bool IsSoundEffectOn() = 0;
	//设置是否播放音效
	virtual void SetSoundEffectOn(bool on) = 0;

	//获取音乐的音量大小
	virtual int GetSoundVolume() = 0;
	//设置音乐的音量大小，为一个百分比，代表最大音量的百分之几
	/*
	 * TODO 特别注意，需要判断0和100范围之外的输入，这句话看完了做到了就删掉吧
	 */
	virtual int SetSoundVolume(int percent) = 0;

	//获得飞机发射炮弹的按键
	virtual int GetFireKey() = 0;
	//设置飞机发射炮弹的按键
	virtual void SetFireKey(int key) = 0;
>>>>>>> 85a8710666462ba30f6c52f2006f679e215c747c
};

//////////////////////////////////////////////////////////////////////////

//Audio（音效）模块的接口，定义了audio模块所需的操作
class IAudio
{
public:
	//写这个函数时为了提醒：在析构函数里退出时一定要释放所有相关的资源
	virtual void Release() = 0;

	//设置播放音乐的音量，是一个百分比，见IOptions里的SetSoundVolume函数
	virtual void SetVolume(int percent) = 0;

	//开始播放背景音乐，BGM一般比较长，同时间只能有一个背景音乐在播放，url即为BGM地址
	virtual void StartBGM(const string& url) = 0;
	//停止播放背景音乐，如果有正在播的话
	virtual void StopBGM() = 0;

	//播放一个音效，音效一般时间比较短，无法暂停，可以有多个effect同时在播放
	virtual void PlayEffect(const string& url) = 0;
	//停止一个音效，根据effect地址url决定是停哪个音效
	virtual void StopEffect(const string& url) = 0;
	//停止全部正在播放的音效
	virtual void StopAllEffect() = 0;
};

//////////////////////////////////////////////////////////////////////////
#endif