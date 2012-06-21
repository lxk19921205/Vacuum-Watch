#ifndef _VW_LOG_H_
#define _VW_LOG_H_

#include <string>
#include "module_interfaces.h"

using std::string;


class CLog : public ILog
{
public:
	CLog();
	 ~CLog();
	
	virtual void Info(const string& msg);
	virtual void Debug(const string& msg);
	virtual void Error(const string& msg);

	//获得存放info级log的文件名
	virtual const string& GetInfoFileName();
	//获得存放debug级log的文件名
	virtual const string& GetDebugFileName();
	//获得存放error级log的文件名
	virtual const string& GetErrorFileName();

	//清空info级的log
	virtual void ClearInfo();
	//清空debug级的log
	virtual void ClearDebug();
	//清空error级的log
	virtual void ClearError();

private:
	string file_name;
};


#endif