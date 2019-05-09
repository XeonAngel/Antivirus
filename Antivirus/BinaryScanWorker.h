#pragma once

#include "ScanWorker.h"

class BinaryScanWorker :
	public ScanWorker
{
	MyList <MyString>* m_BinaryMalware;
	char* m_ToScanSequence;
	int m_FileZise;

	public:

	void SaveSequence();

	void Scan();
	void Compare(int &NumberOfVirus, int i);

	BinaryScanWorker(const MyString& Job, const float Percent, MyList<MyString>* BinaryDB);
	~BinaryScanWorker();
};