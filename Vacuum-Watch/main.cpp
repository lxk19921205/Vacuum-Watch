#include <gl/glut.h>

#include "module_interfaces.h"
#include "factory.h"
#include "testing.h"
#include "input.h"

void DoTest()
{
	CTesting test;

//	test.TestOptions();
//	test.TestLog();
//	test.TestGameData();
	test.TestAudio();
}


int main(int argc, char** argv)
{
	DoTest();
//	return 0;

	glutInit(&argc, argv);

	IController* controller = CFactory::getController();
	controller->Init();
	controller->StartGame();

	return 0;
}
