#ifndef _VW_FACTORY_H_
#define _VW_FACTORY_H_

#include "module_interfaces.h"

class CFactory
{
public:
	//获得Log模块的唯一实例
	static ILog* getLog();

	//获得Options模块的唯一实例
	static IOptions* getOptions();

	//获得Audio模块的唯一实例
	static IAudio* getAudio();
};

#endif