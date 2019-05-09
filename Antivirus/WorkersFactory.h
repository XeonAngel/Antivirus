#pragma once

#include "ScanWorker.h"
#include "TextScanWorker.h"
#include "BinaryScanWorker.h"
#include "MyList.h"

class WorkersFactory
{
	public:
	static ScanWorkerInterface* Create_TextWorker(MyString Job, const float Percent, MyList<MyString>* TextDB);
	static ScanWorkerInterface* Create_BinaryWorker(MyString Job, const float Percent, MyList<MyString>* BinaryDB);
};