#ifndef _VW_INPUT_H_
#define _VW_INPUT_H_

#include "module_interfaces.h"

/************************************************************************/
/* ���ڼ������̺����Ķ����������װ�ɶ��������������Ϣ               */
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