#include <iostream>
//#include <gl/glut.h>
#include "COption.h"
#include "constants.h"
#include "module_interfaces.h"
#include "factory.h"

using std::cout;
using std::endl;

//
//void RenderScene()
//{
//	//用当前清除颜色清除窗口
//	glClear(GL_COLOR_BUFFER_BIT);
//	//刷新绘图命令
//	glFlush();
//}
//
//void SetupRC()
//{
//	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
//}
//
void SaveOption()
{
	COption *op=new COption();
	op->SaveIntoFile();
}
void RestoreOption()
{
	COption *op=new COption();
	op->RestoreFromFile();
}
void SetKey()
{
	COption * op=new COption();
	op->SetFireKey(65);
	op->SaveIntoFile();
}
void GetKey()
{
	COption* op=new COption();
	op->RestoreFromFile();
	cout<<op->GetFireKey();
}

int main(int argc, char** argv)
{/*
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow(VW_WINDOW_TITLE);
	glutDisplayFunc(RenderScene);

	SetupRC();
	glutMainLoop();

	return 0;*/
//	SaveOption();
	//RestoreOption();
//SetKey();
//	GetKey();
}