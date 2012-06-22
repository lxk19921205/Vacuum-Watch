#include "factory.h"
#include "log.h"
#include "option.h"


ILog* CFactory::getLog()
{
	return &CLog::Instance();
}


IOptions* CFactory::getOptions()
{
	return &COption::Instance();
}


IAudio* CFactory::getAudio()
{
	//TODO
	return NULL;
}