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

const string& CLog::GetFileName()
{
	return this->file_name;
}

void CLog::Info(string msg)
{
	// TODO
	ofstream outfile("Info.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! Info written false!";
	}
	else
		outfile<<msg<<endl;
}

void CLog::Debug(string msg)
{
	// TODO
	ofstream outfile("Debug.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! Debug written false!";
	}
	else
		outfile<<msg<<endl;
}

void CLog::Error(string msg)
{
	// TODO
	ofstream outfile("Error.txt", ios_base::app);
	if (!outfile){
		cerr<<"Sorry! Error written false!";
	}
	else
		outfile<<msg<<endl;
}
