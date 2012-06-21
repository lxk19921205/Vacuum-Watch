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

	virtual void Info(string msg) = 0;
	virtual void Debug(string msg) = 0;
	virtual void Error(string msg) = 0;
	
};


#endif