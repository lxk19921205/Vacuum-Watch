#ifndef _VW_INPUT_H_
#define _VW_INPUT_H_

#include "module_interfaces.h"

/************************************************************************/
/* 用于监听键盘和鼠标的动作，将其包装成对我们有意义的消息               */
/************************************************************************/
class CInput : public IInput
{
public:
	CInput();
	virtual ~CInput();

	virtual void InitListener();
	virtual void OnFireKeyClicked();
};

#endif