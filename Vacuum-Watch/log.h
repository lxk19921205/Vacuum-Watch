#ifndef _VW_LOG_H_
#define _VW_LOG_H_

#include <string>
#include "module_interfaces.h"

using std::string;


class CLog : public ILog
{
public:
	CLog();
	virtual ~CLog();

	virtual const string& GetInfoFileName();
	virtual const string& GetDebugFileName();
	virtual const string& GetErrorFileName();

	virtual void ClearInfo();
	virtual void ClearDebug();
	virtual void ClearError();

	virtual void Info(const string& msg);
	virtual void Debug(const string& msg);
	virtual void Error(const string& msg);

private:
};


#endif