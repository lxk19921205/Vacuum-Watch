#include "log.h"


CLog::CLog()
	:file_name("vw_log_file.log")
{
}

CLog::~CLog()
{

}

const string& CLog::GetFileName()
{
	return this->file_name;
}

void CLog::Info(const char* msg)
{
	// TODO
}

void CLog::Debug(const char* msg)
{
	// TODO
}

void CLog::Error(const char* msg)
{
	// TODO
}
