/************************************************************************/
/* 第一版：邵競弘                                                       */
/* 第二版：Andriy                                                       */
/*     每次写的时候直接更新文件，在小数据量的时候OK，数据永远是最新的   */
/************************************************************************/

#include<iostream>
#include<fstream>

#include "constants.h"
#include "option.h"
#include "factory.h"

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;


const string COption::FILE_NAME = "Options.opt";


COption::COption()
	: m_bBackground(VW_OPTION_DEF_BGM)
	,m_bEffect(VW_OPTION_DEF_EFFECT)
	,m_iVolume(VW_OPTION_DEF_VOLUME)
	,m_iFireKey(VW_OPTION_DEF_FIRE_KEY)
{
	RestoreFromFile();
}

COption::~COption()
{
	SaveIntoFile();
}

bool COption::SaveIntoFile()
{
	ILog* log = CFactory::getLog();

	ofstream outfile(FILE_NAME);
	if(!outfile)
	{
		log->Error("open option file error! SaveIntoFile()");
		return false;
	}
	else
	{
		outfile<<m_bBackground<<endl
			<<m_bEffect<<endl
			<<m_iVolume<<endl
			<<m_iFireKey;
		outfile.close();

		log->Info("Option Settings have been saved into file.");
		return true;
	}
}

bool COption::RestoreFromFile()
{
	ILog* log = CFactory::getLog();

	ifstream infile(FILE_NAME);
	if(!infile)
	{
		this->ResetAll();
		log->Error("open option file for read error! RestoreFromFile()");
		return false;
	}
	else
	{
		infile>>m_bBackground
			>>m_bEffect
			>>m_iVolume
			>>m_iFireKey;
		infile.close();

		log->Info("Option Settings have been restored from file.");
		return true;
	}
}

bool COption::IsBackgroundOn()
{
	return this->m_bBackground;
}

void COption::SetBackgroundOn(bool on)
{
	this->m_bBackground=on;
	this->SaveIntoFile();
}

bool COption::IsSoundEffectOn()
{
	return this->m_bEffect;
}

void COption::SetSoundEffectOn(bool on)
{
	m_bEffect=on;
	this->SaveIntoFile();
}

int COption::GetSoundVolume()
{
	return this->m_iVolume;
}

void COption::SetSoundVolume(int percent)
{
	ILog* log = CFactory::getLog();

	if(percent>100||percent<0)
	{
		log->Error("percent is out of range! SetSoundVolume()");
	}

	this->m_iVolume = (percent %= 101);	//处理不良数据
	this->SaveIntoFile();
}

int COption::GetFireKey()
{
	return this->m_iFireKey;
}

void COption::SetFireKey(int _key)
{
	this->m_iFireKey=_key;
	this->SaveIntoFile();
}

void COption::ResetAll()
{
	this->m_bBackground = VW_OPTION_DEF_BGM;
	this->m_bEffect = VW_OPTION_DEF_EFFECT;
	this->m_iVolume = VW_OPTION_DEF_VOLUME;
	this->m_iFireKey = VW_OPTION_DEF_FIRE_KEY;
}
