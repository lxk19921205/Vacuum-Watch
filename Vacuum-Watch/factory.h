#ifndef _VW_FACTORY_H_
#define _VW_FACTORY_H_

#include "module_interfaces.h"

class CFactory
{
public:
	//获得Log模块唯一的实例
	static ILog* getLog();

	//获得Options模块唯一的实例
	static IOptions* getOptions();
};

#endif