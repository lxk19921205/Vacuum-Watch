#include <fstream>
#include <iostream>

#include "log.h"

using std::ofstream;
using std::ios_base;
using std::cerr;
using std::endl;


const string CLog::INFO_LOG_NAME = "InfoLog.txt";
const string CLog::DEBUG_LOG_NAME = "DebugLog.txt";
const string CLog::ERROR_LOG_NAME = "ErrorLog.txt";


CLog::CLog()
{

}

CLog::~CLog()
{
}

const string& CLog::GetInfoFileName()
{
	return INFO_LOG_NAME;
}

const string& CLog::GetDebugFileName()
{
	return DEBUG_LOG_NAME;
}

const string& CLog::GetErrorFileName()
{
	return ERROR_LOG_NAME;
}

void CLog::Info(const string& msg)
{
	ofstream outfile("InfoLog.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! InfoLog written false!";
	}
	else
	{
		outfile<<msg<<endl;
		outfile.close();
	}
}

void CLog::Debug(const string& msg)
{
	ofstream outfile("DebugLog.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! DebugLog written false!";
	}
	else
	{
		outfile<<msg<<endl;
		outfile.close();
	}
}

void CLog::Error(const string& msg)
{
	ofstream outfile("ErrorLog.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! ErrorLog written false!";
	}
	else
	{
		outfile<<msg<<endl;
		outfile.close();
	}
}

void CLog::ClearInfo()
{
	ofstream f("InfoLog.txt", ios_base::trunc);
	f.close();
}

void CLog::ClearDebug()
{
	ofstream f("DebugLog.txt", ios_base::trunc);
	f.close();
}

void CLog::ClearError()
{
	ofstream f("ErrorLog.txt", ios_base::trunc);
	f.close();
}
