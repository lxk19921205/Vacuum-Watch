#ifndef _VW_FACTORY_H_
#define _VW_FACTORY_H_

#include "module_interfaces.h"

class CFactory
{
public:
	//���Logģ���Ψһʵ��
	static ILog* getLog();

	//���Optionsģ���Ψһʵ��
	static IOptions* getOptions();

	//���Audioģ���Ψһʵ��
	static IAudio* getAudio();
};

#endif