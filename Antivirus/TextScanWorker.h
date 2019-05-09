#pragma once

#include "ScanWorker.h"

class TextScanWorker :
	public ScanWorker
{
	MyList <MyString>* m_TextMalware;
	MyList <MyString> m_WordsToScan;

	public:

	void SaveWords();

	void Scan();
	void NormalScan(int &NumberOfVirus, int i, int j);
	void StrictScan(int &NumberOfVirus, int i, int j);


	TextScanWorker(MyString Job, const float Percent, MyList<MyString>* TextDB);
	~TextScanWorker();
};