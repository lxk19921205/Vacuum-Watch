#include "factory.h"
#include "log.h"


CLog g_log;


ILog* CFactory::getLog()
{
	return &g_log;
}