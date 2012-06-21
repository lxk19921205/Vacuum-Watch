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
	
	virtual const string& GetFileName();

	virtual void Info(string msg);
	virtual void Debug(string msg);
	virtual void Error(string msg);

private:
	string file_name;
};


#endif