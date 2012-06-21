#include<iostream>
#include<fstream>
#include"COption.h"
#include "constants.h"


using std::ofstream;

COption::COption()
	: back_ground(false)
	,effect(false)
	,volume(0)
	,key(32)
	,bret(false)
{
	file_name=VW_OPTION_FILENAME;
#if(VW_LOG_CLOSED)
	log=new CLog();
#endif
}
COption::~COption()
{
	if(!bret)
	{
		SaveIntoFile();
		bret=true;
	}
}

void COption::SaveIntoFile()
{

	ofstream outfile(file_name,ofstream::binary);
	if(!outfile)
	{
#if(VW_LOG_CLOSED)
		log.Error("open option file error!");
#else
		std::cerr<<"open option file error!";
#endif
		return;
	}
	outfile<<back_ground<<endl
		<<effect<<endl
		<<volume<<endl
		<<key;
#if(VW_LOG_CLOSED)
	log.Info(back_ground+" "
		+effect+" "
		+volume+" "
		+key+" "
		+"has been saved in file"+file_name);
#else
	cout<<back_ground<<" "<<effect<<" "<<volume<<" "<<key<<" "
		<<"has been saved in file"<<file_name<<endl;
#endif
	outfile.close();
}
void COption::RestoreFromFile()
{
	ifstream infile(file_name,ifstream::binary);
	if(!infile)
	{
		bret=false;
#if(VW_LOG_CLOSED)
		log.Error("open option file for read error!");
#else
		std::cerr<<"open option file for read error!";
#endif
		return ;
	}
	infile>>back_ground
		>>effect
		>>volume
		>>key;
	infile.close();
#if(VW_LOG_CLOSED)
	log.Info(back_ground+" "
		+effect+" "
		+volume+" "
		+key+" "
		+"has been read from "+file_name);
#else
	cout<<back_ground<<" "<<effect<<" "<<volume<<" "<<(char)key<<endl;
#endif
	bret=true;
}
bool COption::IsBackgroundOn()
{
	if(bret)
	{
		if(back_ground)
		{
			std::cout<<"back_ground is on"<<endl;
			return true;
		}
	}
	else
	{
#if(VW_LOG_CLOSED)
		log.Error("not read file info yet!");
#else
		std::cerr<<"not read file info yet!";
#endif
	}

	return false;
}
void COption::SetBackgroundOn(bool on)
{
	back_ground=on;
	bret=false;
}
bool COption::IsSoundEffectOn()
{
	if(bret)
	{
		if(effect)
			return true;
	}
	else
	{
#if(VW_LOG_CLOSED)
		log.Error("not read file info yet!");
#else
		std::cerr<<"not read file info yet!";
#endif
	}
	return false;
}
void COption::SetSoundEffectOn(bool on)
{
	effect=on;
	bret=false;
}
int COption::GetSoundVolume()
{
	if(bret)
	{
		return volume;
	}
	else
	{
#if(VW_LOG_CLOSED)
		log.Error("not read file info yet!");
#else
		std::cerr<<"not read file info yet!";
#endif
	}
	return -1;
}
int COption::SetSoundVolume(int percent)
{
	if(percent>100||percent<0)
	{
		return -1;
#if(VW_LOG_CLOSED)
		log.Error("percent is out of range!");
#else
		std::cerr<<"percent is out of range!";
#endif
	}

	return percent;
}
int COption::GetFireKey()
{
	if(bret)
	{
		return key;
		cout<<(char)key;
	}
	else
	{
#if(VW_LOG_CLOSED)
		log.Error("not read file info yet!");
#else
		std::cerr<<"not read file info yet!";
#endif
	}
	return -1;
}
void COption::SetFireKey(int _key)
{
	key=_key;
	bret=false;
}