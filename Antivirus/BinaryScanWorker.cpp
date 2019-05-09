#include "BinaryScanWorker.h"


void BinaryScanWorker::SaveSequence()
{
	try
	{
		fstream File(m_File.GetMyString(), ios::in | ios::binary);
		if (!File.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error Opening Binary Signatures!");
		}

		File.seekg(0, ios::end);
		m_FileZise = File.tellg();

		char *MalwareSignature = new char[m_FileZise + 1];
		if (MalwareSignature == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}
		File.seekg(0, ios::beg);

		File.read(MalwareSignature, m_FileZise);
		MalwareSignature[m_FileZise] = NULL;
		m_ToScanSequence = MalwareSignature;

		File.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void BinaryScanWorker::Scan()
{
	SaveSequence();

	if (m_JobDone == false)
	{
		int VirusFound = 0;

		for (int i = 0; i < (*m_BinaryMalware).GetMyNumberOfElements(); i++)
		{
			Compare(VirusFound, i);
		}

		WriteReport(VirusFound);

		m_JobDone = true;
		m_ScanedFiles++;
	}
}


void BinaryScanWorker::Compare(int & NumberOfVirus, int i)
{
	const char* My = (*m_BinaryMalware)[i].GetMyString();
	int SignatureZise = (*m_BinaryMalware)[i].MyStrlen() - 1;
	if (m_Percent != 0)
	{
		SignatureZise = SignatureZise * m_Percent / 100;
	}

	char* PozisionPointer = m_ToScanSequence;

	for (int j = 0; j < m_FileZise - SignatureZise + 1; j++)
	{
		if (memcmp(PozisionPointer + j, My, SignatureZise) == 0)
			NumberOfVirus++;
	}
	 
}


BinaryScanWorker::BinaryScanWorker(const MyString & Job, const float Percent, MyList<MyString>* BinaryDB)
	:ScanWorker(Job, Percent, MyString::Types::Exe), m_BinaryMalware(BinaryDB)
{
}


BinaryScanWorker::~BinaryScanWorker()
{
}