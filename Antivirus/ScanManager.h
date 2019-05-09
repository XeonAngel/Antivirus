#pragma once


#include "WorkersFactory.h"
#include "DataBase.h"

class ScanManager
{
	private:


	int m_MaxWorker;
	int m_IdleTextWorkers;
	int m_IdleBinaryWorkers;
	int m_LeftWorkers;

	DataBase m_Memory;
	
	MyList<ScanWorkerInterface*> m_WorkersList;

	static ScanManager* Instance;
	ScanManager(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate);
	~ScanManager();

	void CreateTextWorker(MyString Job, const float Percent);
	void CreateBinaryWorker(MyString Job, const float Percent);

	public:

	void ResetReports();
	void Scan(const float Percent);

	void CheckIfUpdate();

	void SetMaxWorkers(const int Workers);

	static ScanManager* GetInstance(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate);
	static void DestroyInstance();


};