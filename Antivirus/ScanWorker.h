#pragma once

#include "ScanWorkerInterface.h"

class ScanWorker:
	public ScanWorkerInterface
{
	protected:

	static int m_UsedWorkers;
	static int m_ScanedFiles;

	int m_ID;
	float m_Percent;

	MyString m_File;
	bool m_JobDone;
	MyString::Types m_MyType;


	public:

	MyString::Types MyType();
	bool MyJobStatus()const;
	void SetJob(const MyString& Job);
	void WriteReport(int VirusFound)const;

	static int GetScanedFiles();

	virtual void Scan() = 0;

	ScanWorker(MyString Job, const float Percent, MyString::Types Type);
	~ScanWorker();
};