#include "DataBase.h"


void DataBase::UpdateText(MyList <MyString>& TextMalwareToUpdate)
{
	SaveTextFile("TextDataBase.txt", m_TextMalware);
	

	for (int i = 0; i < TextMalwareToUpdate.GetMyNumberOfElements(); i++)
	{
		m_TextMalware.PushBack(TextMalwareToUpdate[i]);
	}
}


void DataBase::SaveTextFile(const char * File, MyList<MyString>& List)
{
	try {
		ifstream TextDB(File);
		if (!TextDB.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on text file opening!");
		}

		char *Words = new char[MaxLength];
		if (Words == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}

		while (TextDB >> Words)
		{
			MyString Aux(Words);
			List.PushBack(Aux);
		}

		delete[] Words;

		TextDB.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void DataBase::UpdateBinary(const char* File, MyList<MyString>& List)
{
	try {
		ifstream BinaryDB(File);
		if (!BinaryDB.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error on binary file opening!");
		}

		char *Files = new char[MaxLength];
		if (Files == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}

		while (BinaryDB >> Files)
		{
			UpdateMalwareSignature(Files, List);
		}


		delete[] Files;
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void DataBase::UpdateMalwareSignature(const char * File, MyList<MyString>& List)
{
	try
	{
		fstream SignatureDB(File, ios::in | ios::binary);
		if (!SignatureDB.is_open())
		{
			throw new Exceptions(FileOpenFailed, "Error Opening Binary Signatures!");
		}

		SignatureDB.seekg(0, ios::end);
		int FileZise = SignatureDB.tellg();

		char *MalwareSignature = new char[FileZise + 1];
		if (MalwareSignature == nullptr)
		{
			throw new Exceptions(MemAllocationFailed, "Error on memory allocation!");
		}
		SignatureDB.seekg(0, ios::beg);

		SignatureDB.read(MalwareSignature, FileZise);
		MalwareSignature[FileZise] = NULL;
		MyString MalSignatString(MalwareSignature);
		List.PushBack(MalSignatString);

		delete[] MalwareSignature;

		SignatureDB.close();
	}
	catch (Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void DataBase::StoreFiles(const MyString * Files, MyList <MyString>& List)
{
	MyString Aux = *Files;
	Aux.Devide(List);
}


void DataBase::Update(const MyString * Files, const MyString * TextUpdate, const char * BinaryUpdate)
{
	StoreFiles(Files, m_ToScanFiles);
	

	MyList <MyString> TextMalwareToUpdate;
	StoreFiles(TextUpdate, TextMalwareToUpdate);
	UpdateText(TextMalwareToUpdate);

	UpdateBinary("BinaryDataBase.txt", m_BinaryMalware);
	UpdateMalwareSignature(BinaryUpdate, m_BinaryMalware);

	try
	{
		if (m_TextMalware.GetMyNumberOfElements() == 0 && m_BinaryMalware.GetMyNumberOfElements() == 0)
			throw new Exceptions(EmptyDataBase, "Data Base is empty!");
	}
	catch(Exceptions* Excep)
	{
		Excep->PrintMessage();
		exit(0);
	}
}


void DataBase::AmIUpdated()
{
	MyList<MyString>TextLastUpdateDB;
	SaveTextFile("TextLastUpdate.txt", TextLastUpdateDB);

	MyList<MyString>BinaryLastUpdateDB;
	UpdateBinary("BinaryLastUpdate.txt",BinaryLastUpdateDB);

	if (TextLastUpdateDB == m_TextMalware )
		cout << "==============Text database contain last update=============="<<endl;
	else
		cout << "==============Text database doesn't contain last update==============" << endl;

	if (BinaryLastUpdateDB == m_BinaryMalware)
		cout << "==============Binary database contain last update==============" << endl;
	else
		cout << "==============Binary database doesn't contain last update==============" << endl;
}



DataBase::DataBase()
{
}


DataBase::~DataBase()
{
}