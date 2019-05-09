#include "ScanWorker.h"

int ScanWorker::m_UsedWorkers = 0;
int ScanWorker::m_ScanedFiles = 0;


int ScanWorker::GetScanedFiles()
{
	return m_ScanedFiles;
}


MyString::Types ScanWorker::MyType()
{
	return m_MyType;
}

bool ScanWorker::MyJobStatus() const
{
	return this->m_JobDone;
}


void ScanWorker::SetJob(const MyString& Job)
{
	m_File = Job;
	m_JobDone = false;
}


void ScanWorker::WriteReport(int VirusFound) const 
{
	try
	{
		ofstream Report("ScanReport.txt", ios::app);
		if (!Report.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on file opening!");
		}

		Report << "Woker " << m_ID << " scaned file " << m_File.GetMyString() << " and found " << VirusFound << " item(s) infected." << endl;


		Report.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
	}
}


ScanWorker::ScanWorker(MyString Job, const float Percent, MyString::Types Type)
	:m_ID(m_UsedWorkers + 1), m_File(Job), m_Percent(Percent), m_MyType(Type), m_JobDone(false)
{
	m_UsedWorkers++;
}


ScanWorker::~ScanWorker()
{
}