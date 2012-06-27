#include <gl/freeglut.h>

#include "module_interfaces.h"
#include "factory.h"
#include "testing.h"

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
//	DoTest();
//	return 0;

	IController* controller = CFactory::getController();
	controller->Init(&argc, argv);
	controller->StartGame();

	return 0;
}
