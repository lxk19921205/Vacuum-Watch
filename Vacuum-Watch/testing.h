#ifndef _VW_TESTING_H_
#define _VW_TESTING_H_

class CTesting
{
public:
	CTesting();
	virtual ~CTesting();

	//����Optionģ��
	void TestOptions();

	//����Logģ��
	void TestLog();

	//������Ϸ����ģ��
	void TestGameData();

	//������Чģ��
	void TestAudio();

private:
	//�ȴ�һ�����룬ֱ���������target_c��ʱ����˳�
	void WaitUntil(char target_c);
};

#endif
