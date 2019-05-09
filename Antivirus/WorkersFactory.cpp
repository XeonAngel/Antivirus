#include "WorkersFactory.h"

ScanWorkerInterface * WorkersFactory::Create_TextWorker(MyString Job, const float Percent, MyList<MyString>* TextDB)
{
	return new TextScanWorker(Job, Percent, TextDB);
}

ScanWorkerInterface * WorkersFactory::Create_BinaryWorker(MyString Job, const float Percent, MyList<MyString>* BinaryDB)
{
	return new BinaryScanWorker(Job, Percent, BinaryDB);
}