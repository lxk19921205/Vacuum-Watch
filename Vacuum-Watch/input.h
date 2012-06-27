#ifndef _VW_INPUT_H_
#define _VW_INPUT_H_

#include "module_interfaces.h"

/************************************************************************/
/* 用于监听键盘和鼠标的动作，将其包装成对我们有意义的消息                   */
/* 现在几乎被废弃了...在隧道中重要的几个按键上下左右在ViewEngine里链接      */
/************************************************************************/
class CInput : public IInput
{
public:
	CInput();
	virtual ~CInput();

	virtual void InitListener();
};

#endif