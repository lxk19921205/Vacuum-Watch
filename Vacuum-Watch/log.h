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

	virtual const string& GetFileName();

	virtual void Info(const char* msg);
	virtual void Debug(const char* msg);
	virtual void Error(const char* msg);

private:
	string file_name;
};


#endif