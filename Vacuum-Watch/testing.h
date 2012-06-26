#ifndef _VW_TESTING_H_
#define _VW_TESTING_H_

class CTesting
{
public:
	CTesting();
	virtual ~CTesting();

	//测试Option模块
	void TestOptions();

	//测试Log模块
	void TestLog();

	//测试游戏数据模块
	void TestGameData();

	//测试音效模块
	void TestAudio();

private:
	//等待一个输入，直到输入就是target_c的时候才退出
	void WaitUntil(char target_c);
};

#endif
