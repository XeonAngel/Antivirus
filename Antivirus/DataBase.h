#pragma once

#include "MyString.h"


class DataBase
{
	friend class ScanManager;

	MyList <MyString> m_ToScanFiles;

	MyList <MyString> m_TextMalware;

	MyList <MyString> m_BinaryMalware;

	public:

	void UpdateText(MyList <MyString>& TextMalwareToUpdate);
	void SaveTextFile(const char* File, MyList<MyString>& List);
	void UpdateBinary(const char* File, MyList<MyString>& List);
	void UpdateMalwareSignature(const char* File, MyList<MyString>& List);
	void StoreFiles(const MyString* Files, MyList <MyString>& List);
	void Update(const MyString* Files, const MyString* TextUpdate, const char* BinaryUpdate);

	void AmIUpdated();

	DataBase();
	~DataBase();
};