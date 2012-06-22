#ifndef _VW_LOG_H_
#define _VW_LOG_H_

#include <string>
#include "module_interfaces.h"

using std::string;


//IAudio��һ������ʵ����
class CLog : public ILog
{
public:
	virtual const string& GetInfoFileName();
	virtual const string& GetDebugFileName();
	virtual const string& GetErrorFileName();

	virtual void ClearInfo();
	virtual void ClearDebug();
	virtual void ClearError();

	virtual void Info(const string& msg);
	virtual void Debug(const string& msg);
	virtual void Error(const string& msg);

	//for Singleton
	static inline CLog& Instance()
	{
		static CLog _log;
		return _log;
	}

protected:
	static const string INFO_LOG_NAME;
	static const string DEBUG_LOG_NAME;
	static const string ERROR_LOG_NAME;

	//for Singleton
	CLog();
	virtual ~CLog();
	CLog(const CLog& rhs);				//��ʵ��
	CLog& operator=(const CLog& rhs);	//��ʵ��
};


#endif
