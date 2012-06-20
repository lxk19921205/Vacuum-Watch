#ifndef _VW_MODULE_INTERFACES_H_
#define _VW_MODULE_INTERFACES_H_

#include <string>
using std::string;

//Logģ��Ľӿڣ�������logģ����Ҫ�Ĳ���
class ILog
{
public:
	//��ô��info��log���ļ���
	virtual const string& GetInfoFileName() = 0;
	//��ô��debug��log���ļ���
	virtual const string& GetDebugFileName() = 0;
	//��ô��error��log���ļ���
	virtual const string& GetErrorFileName() = 0;

	//���info����log
	virtual void ClearInfo() = 0;
	//���debug����log
	virtual void ClearDebug() = 0;
	//���error����log
	virtual void ClearError() = 0;

	//д��һ��info����log
	virtual void Info(const string& msg) = 0;
	//д��һ��debug����log
	virtual void Debug(const string& msg) = 0;
	//д��һ��error����log
	virtual void Error(const string& msg) = 0;
};

#endif