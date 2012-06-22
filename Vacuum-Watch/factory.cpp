#include "factory.h"
#include "log.h"


CLog g_log;


ILog* CFactory::getLog()
{
	//TODO
	return &g_log;
}


IOptions* CFactory::getOptions()
{
	//TODO
	return NULL;
}


IAudio* CFactory::getAudio()
{
	//TODO
	return NULL;
}