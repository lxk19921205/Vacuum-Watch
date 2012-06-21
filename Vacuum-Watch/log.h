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

	//��ô��info��log���ļ���
	virtual const string& GetInfoFileName();
	//��ô��debug��log���ļ���
	virtual const string& GetDebugFileName();
	//��ô��error��log���ļ���
	virtual const string& GetErrorFileName();

	//���info����log
	virtual void ClearInfo();
	//���debug����log
	virtual void ClearDebug();
	//���error����log
	virtual void ClearError();

private:
	string file_name;
};


#endif