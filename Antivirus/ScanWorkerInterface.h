#pragma once

#include "MyString.h"
#include "DataBase.h"

class ScanWorkerInterface
{

	public:
	virtual	MyString::Types MyType() = 0;
	virtual bool MyJobStatus()const = 0;
	virtual void SetJob(const MyString& Job) = 0;
	virtual void WriteReport(int VirusFound)const = 0;
	virtual void Scan() = 0;
};