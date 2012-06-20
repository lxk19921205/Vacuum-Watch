#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;

//Log模块的接口，要实现这么个东西，并且要求是单例！
class ILog
{
public:
	static const ILog* Get();

	virtual const string& GetFileName() = 0;

	virtual void Info(const char* msg) = 0;
	virtual void Debug(const char* msg) = 0;
	virtual void Error(const char* msg) = 0;
};


#endif