#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;


//////////////////////////////////////////////////////////////////////////

//Log模块的接口，定义了log模块所需的操作
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
	virtual void SetBackground(bool on) = 0;

	//音效是否打开
	virtual bool IsSoundEffectOn() = 0;
	//设置是否播放音效
	virtual void SetSoundEffect(bool on) = 0;

	//获得飞机发射炮弹的按键
	virtual int GetFireKey() = 0;
	//设置飞机发射炮弹的按键
	virtual void SetFireKey(int key) = 0;
};

//////////////////////////////////////////////////////////////////////////
#endif