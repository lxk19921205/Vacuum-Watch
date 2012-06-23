#ifndef _VW_VIEW_ENGINE_H_
#define _VW_VIEW_ENGINE_H_

#include <gl/GL.h>
#include "module_interfaces.h"

/************************************************************************/
/* ר������ʹ��OpenGL��չʾ��Ϸ����                                     */
/************************************************************************/
class CViewEngine : public IViewEngine
{
public:
	CViewEngine();
	virtual ~CViewEngine();

	virtual void Init();
	//��Init�е��ã�ΪOpenGL����������д�Ŀ��
	void SetupRC();

	virtual void StartDisplaying();
};

#endif
