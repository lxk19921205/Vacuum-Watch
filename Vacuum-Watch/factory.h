#ifndef _VW_FACTORY_H_
#define _VW_FACTORY_H_

#include "module_interfaces.h"

class CFactory
{
public:
	//���Logģ��Ψһ��ʵ��
	static ILog* getLog();

	//���Optionsģ��Ψһ��ʵ��
	static IOptions* getOptions();
};

#endif