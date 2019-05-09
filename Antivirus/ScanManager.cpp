#include "ScanManager.h"


ScanManager* ScanManager::Instance = nullptr;


void ScanManager::ResetReports()
{
	try {
		ofstream LastReport("ScanReport.txt", ios::trunc);
		ofstream ExceptionReport("ExceptionReport.txt", ios::trunc);
		if (!LastReport.is_open() || !ExceptionReport.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on Report file opening!");
		}
		LastReport << "Scan Report:" << endl;
		LastReport.close();
	}
	catch(Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void ScanManager::Scan(const float Percent)
{
	ResetReports();
	
	int FilesToScan = m_Memory.m_ToScanFiles.GetMyNumberOfElements();

	int i = 0;
	while (FilesToScan)
	{
		for (int j = 0; j < m_MaxWorker && j < FilesToScan; j++)
		{
			MyString::Types Extension = m_Memory.m_ToScanFiles[i].GiveMeYourExtension();

			switch (Extension)
			{
				case MyString::Types::Txt:
					{
						CreateTextWorker(m_Memory.m_ToScanFiles[i], Percent);

						i++;
						FilesToScan--;
						break;
					}
				case MyString::Types::Exe:
					{
						CreateBinaryWorker(m_Memory.m_ToScanFiles[i], Percent);

						i++;
						FilesToScan--;
						break;
					}
				default:
					{
						try
						{
							throw new Exceptions(UnkownExtension, "Unkown Extension!");
						}
						catch (Exceptions* Excep)
						{
							Excep->PrintMessage();
						}
						FilesToScan--;
						i++;
						break;
					}
			}
		}

		for (int a = 0; a < m_WorkersList.GetMyNumberOfElements(); a++)
		{
			if ((*m_WorkersList[a]).MyType() == MyString::Types::Txt && (*m_WorkersList[a]).MyJobStatus() == false)
			{
				m_WorkersList[a]->Scan();
				m_IdleTextWorkers++;
			}
			else if ((*m_WorkersList[a]).MyType() == MyString::Types::Exe && (*m_WorkersList[a]).MyJobStatus() == false)
			{
				m_WorkersList[a]->Scan();
				m_IdleBinaryWorkers++;
			}
		}
	}

	try {
		ofstream LastReport("ScanReport.txt", ios::app);
		if (!LastReport.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on Report file opening!");
		}

		int FilesScaned = ScanWorker::GetScanedFiles();

		LastReport << "Scan summary:" << endl;
		LastReport << "TOTAL file scaned: " << FilesScaned << endl;

		int MaxUsedWorkers = (FilesScaned >= m_MaxWorker) ? m_MaxWorker : FilesScaned;

		LastReport << "Worker Used:" << MaxUsedWorkers << endl;
		LastReport.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void ScanManager::CheckIfUpdate()
{
	m_Memory.AmIUpdated();
}


void ScanManager::SetMaxWorkers(const int Workers)
{
	m_MaxWorker = Workers;
	m_LeftWorkers = Workers;
}


ScanManager::ScanManager(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate)
	: m_IdleBinaryWorkers(0), m_IdleTextWorkers(0)
{
	m_Memory.Update(Files, TextUpdate, BinaryUpdate);
}


ScanManager::~ScanManager()
{
}


void ScanManager::CreateTextWorker(MyString Job,const float Percent)
{
	try
	{
		if (m_LeftWorkers > 0)
		{
			ScanWorkerInterface* Aux = WorkersFactory::Create_TextWorker(Job, Percent, &m_Memory.m_TextMalware);
			m_WorkersList.PushBack(Aux);

			m_LeftWorkers--;
			return;
		}
		if (m_IdleTextWorkers > 0)
		{
			int i;
			for (i = 0; i < m_WorkersList.GetMyNumberOfElements(); i++)
			{
				if ((*m_WorkersList[i]).MyJobStatus() == true && (*m_WorkersList[i]).MyType() == MyString::Types::Txt)
					break;
			}
			m_WorkersList[i]->SetJob(Job);

			m_IdleTextWorkers--;
			return;
		}
		if (m_IdleBinaryWorkers > 0)
		{
			throw new Exceptions(WorkerNotAvaible, "There are not avaible workers for text. Trying to use an idle one from binary.");
		}
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();

		int i;
		for (i = 0; i < m_WorkersList.GetMyNumberOfElements(); i++)
		{
			if ((*m_WorkersList[i]).MyJobStatus() == true && (*m_WorkersList[i]).MyType() == MyString::Types::Exe)
				m_WorkersList.Delete(i);
			break;
		}
		ScanWorkerInterface* Aux = WorkersFactory::Create_TextWorker(Job, Percent, &m_Memory.m_TextMalware);
		m_WorkersList.PushBack(Aux);

		m_IdleBinaryWorkers--;
	}
}


void ScanManager::CreateBinaryWorker(MyString Job, const float Percent)
{
	try
	{
		if (m_LeftWorkers > 0)
		{
			ScanWorkerInterface* Aux = WorkersFactory::Create_BinaryWorker(Job, Percent, &m_Memory.m_BinaryMalware);
			m_WorkersList.PushBack(Aux);

			m_LeftWorkers--;
			return;
		}
		if (m_IdleBinaryWorkers > 0)
		{
			int i;
			for (i = 0; i < m_WorkersList.GetMyNumberOfElements(); i++)
			{
				if ((*m_WorkersList[i]).MyJobStatus() == true && (*m_WorkersList[i]).MyType() == MyString::Types::Exe)
					break;
			}
			m_WorkersList[i]->SetJob(Job);

			m_IdleBinaryWorkers--;
			return;
		}
		if (m_IdleTextWorkers > 0)
		{
			throw new Exceptions(WorkerNotAvaible, "There are not avaible workers for binary. Trying to use an idle one from text.");
		}
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();

		int i;
		for (i = 0; i < m_WorkersList.GetMyNumberOfElements(); i++)
		{
			if ((*m_WorkersList[i]).MyJobStatus() == true && (*m_WorkersList[i]).MyType() == MyString::Types::Txt)
				m_WorkersList.Delete(i);
			break;
		}
		ScanWorkerInterface* Aux = WorkersFactory::Create_BinaryWorker(Job, Percent, &m_Memory.m_BinaryMalware);
		m_WorkersList.PushBack(Aux);

		m_IdleTextWorkers--;
	}
}


ScanManager* ScanManager::GetInstance(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate)
{
	if (Instance == nullptr)
	{
		Instance = new ScanManager(Files,TextUpdate,BinaryUpdate);
	}

	return Instance;
}


void ScanManager::DestroyInstance()
{
	if (Instance == nullptr)
		return;
	
	delete Instance;
	Instance = nullptr;
}