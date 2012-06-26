#include "factory.h"
#include "log.h"
#include "option.h"
#include "controller.h"
#include "audio.h"


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
	return &CAudio::Instance();
}

IController* CFactory::getController()
{
	return &CController::Instance();
}
