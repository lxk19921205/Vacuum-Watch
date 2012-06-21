#include "log.h"
#include <fstream>
#include <iostream>

using namespace std;

CLog::CLog()
	:file_name("vw_log_file.log")
{
}

CLog::~CLog()
{

}

const string& CLog::GetInfoFileName()
{
	return "InfoLog.txt";
}

const string& CLog::GetDebugFileName()
{
	return "DebugLog.txt";
}

const string& CLog::GetErrorFileName()
{
	return "ErrorLog.txt";
}

void CLog::Info(const string& msg)
{
	// TODO
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
	// TODO
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
	// TODO
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
	ofstream f("InfoLog.txt", ios::trunc);
	f.close();
}

void CLog::ClearDebug()
{
	ofstream f("DebugLog.txt", ios::trunc);
	f.close();
}

void CLog::ClearError()
{
	ofstream f("ErrorLog.txt", ios::trunc);
	f.close();
}