#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;

//Logģ��Ľӿڣ�Ҫʵ����ô������������Ҫ���ǵ�����
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