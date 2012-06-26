#ifndef _VW_VIEW_ENGINE_H_
#define _VW_VIEW_ENGINE_H_

#include <gl/GL.h>
#include "module_interfaces.h"
#include "button.h"

/************************************************************************/
/* ר������ʹ��OpenGL��չʾ��Ϸ����                                     */
/************************************************************************/
class CViewEngine : public IViewEngine
{
public:
	CViewEngine();
	virtual ~CViewEngine();

	virtual void Init();
	virtual void StartDisplaying();
	
	virtual void OnLeftClicked(int pos_x, int pos_y);

	virtual void Redraw();

private:
	//��Init�е��ã�ΪOpenGL����������д�Ŀ��
	void SetupRC();

};

#endif
